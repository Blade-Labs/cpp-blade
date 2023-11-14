#include "../include/BladeSDK.h"

#include "ECDSAsecp256k1PrivateKey.h"
#include "ED25519PrivateKey.h"
#include "MnemonicBIP39.h"
#include "Client.h"
#include "AccountCreateTransaction.h"
#include "TransactionReceipt.h"
#include "TransactionResponse.h"
#include "TransactionRecord.h"
#include "ContractExecuteTransaction.h"

#include <iostream>
#include <string>
#include <nlohmann/json.hpp>
#include "model/enums.cpp"
#include "model/types.cpp"
#include "service/apiService.cpp"
#include "service/accountService.cpp"
#include "service/securityService.cpp"
#include "service/utilService.cpp"
#include "service/fingerprintService.cpp"

using namespace Hedera;


namespace BladeSDK {
  Blade::Blade(const std::string& apiKey, const Network& network, const std::string& dAppCode, const SdkEnvironment& sdkEnvironment)
    : apiService(apiKey, network, dAppCode, sdkEnvironment)
  {
    this->network = network;
    this->apiKey = apiKey;
    this->dAppCode = dAppCode;
    this->sdkEnvironment = sdkEnvironment;
    FingerprintService fingerprintService = FingerprintService();
    this->visitorId = fingerprintService.getVisitorId();
    apiService.init(this->sdkVersion, this->visitorId);
  }

  InfoData Blade::getInfo() {
    return {
      .apiKey = this->apiKey,
      .dAppCode = this->dAppCode,
      .network = this->network,
      .visitorId = this->visitorId,
      .sdkEnvironment = this->sdkEnvironment,
      .sdkVersion = this->sdkVersion,
    };
  }

  AccountData Blade::createAccountBlade() {
    MnemonicBIP39 seedPhrase = getMnemonic();
    std::shared_ptr<PrivateKey> privateKey = getPrivateKey(seedPhrase);
    std::shared_ptr<PublicKey> publicKey = privateKey->getPublicKey();

    json account = apiService.createAccount(publicKey);

    Client client = this->getClient();

    AccountService::executeUpdateAccountTransactions(
        &client,
        privateKey,
        account.value("updateAccountTransactionBytes", ""),
        account.value("transactionBytes", "")
    );

    return {
        .seedPhrase = seedPhrase.toString(),
        .publicKey = account.value("publicKey", ""),
        .privateKey = privateKey->toStringDer(),
        .accountId = account.value("id", ""),
    };
  }

  AccountInfoData Blade::getAccountInfo(std::string accountId) {
    json result = apiService.GET("/api/v1/accounts/" + accountId);

    return {
      .accountId = result.value("account", ""),
      .evmAddress = result.value("evm_address", ""),
      .publicKey = result["key"].value("key", ""),
    };
  }

  AccountBalanceData Blade::getBalance(std::string accountId) {
    return apiService.getBalance(accountId);
  }
  
  PrivateKeyData Blade::importAccount(std::string seedPhrase, bool lookupAccounts) {
    MnemonicBIP39 mnemonic = MnemonicBIP39::initializeBIP39Mnemonic(seedPhrase);
    std::shared_ptr<PrivateKey> privateKey = getPrivateKey(mnemonic);
    std::vector<std::string> accountIds = apiService.getAccountsFromPublicKey(privateKey->getPublicKey()->toStringRaw());

    return {
      .privateKey = privateKey->toStringDer(),
      .publicKey = privateKey->getPublicKey()->toStringDer(),
      .seedPhrase = mnemonic.toString(),
      .accounts = accountIds,
    };
  }  

  TxReceipt Blade::transferHbars(std::string accountId, std::string accountPrivateKey, std::string recieverAccount, std::string amount, std::string memo) {
      Client client = this->getClient();
      client.setOperator(AccountId::fromString(accountId), ECDSAsecp256k1PrivateKey::fromString(accountPrivateKey));
      const Hbar amountHbar(std::stoull(amount), HbarUnit::HBAR());

      TransactionResponse txResponse = TransferTransaction()
                                     .addHbarTransfer(AccountId::fromString(accountId), amountHbar.negated())
                                     .addHbarTransfer(AccountId::fromString(recieverAccount), amountHbar)
                                     .setTransactionMemo(memo)
                                     .execute(client);

      TransactionReceipt receipt = txResponse.getReceipt(client);

      return UtilService::formatReceipt(receipt);
  }

  TxReceipt Blade::transferTokens(std::string tokenId, std::string accountId, std::string accountPrivateKey, std::string receiverId, std::string amount, std::string memo, bool freeTransfer) {
    const std::shared_ptr<PrivateKey> privateKey = ECDSAsecp256k1PrivateKey::fromString(accountPrivateKey);

    Client client = this->getClient();
    client.setOperator(AccountId::fromString(accountId), privateKey);
    json tokenMeta = apiService.GET("/api/v1/tokens/" + tokenId);
    std::string decimals = tokenMeta.value("decimals", "0");
    long long correctedAmount = std::stoull(amount) * std::pow(10, std::stoi(decimals));

    if (freeTransfer) {
      BladeTxResponse response = apiService.freeTokenTransfer(accountId, receiverId, correctedAmount, memo);
      std::cout << "response.transactionBytes: " << response.transactionBytes << std::endl;
      const WrappedTransaction tx = Transaction<TransferTransaction>::fromBytes(response.bytes);
      if (tx.getTransactionType() == TransactionType::TRANSFER_TRANSACTION) {
        TransferTransaction transferTransaction = *tx.getTransaction<TransferTransaction>();
        TransactionResponse txResp = transferTransaction
          .freezeWith(&client)
          .sign(privateKey)
          .execute(client)
        ;
        TransactionReceipt receipt = txResp.getReceipt(client);

        // std::cout << "AccountId: " << txReceipt.mAccountId.value().toString() << std::endl;

        return UtilService::formatReceipt(receipt);
      }
      throw std::runtime_error("Failed create TransferTransaction");
    } else {
      TokenId token = TokenId::fromString(tokenId);

      TransactionResponse txResponse = TransferTransaction()
                                      .addTokenTransfer(token, AccountId::fromString(accountId), -correctedAmount)
                                      .addTokenTransfer(token, AccountId::fromString(receiverId), correctedAmount)
                                      .setTransactionMemo(memo)
                                      .freezeWith(&client)
                                      .execute(client);
        
        TransactionReceipt receipt = txResponse.getReceipt(client);
        return UtilService::formatReceipt(receipt);
    }
  } 

  SignMessageData Blade::sign(std::string message, std::string signerKey, std::string encoding /* hex|base64|string */) {
    std::unique_ptr<PrivateKey> privateKey = ECDSAsecp256k1PrivateKey::fromString(signerKey);

    std::vector<std::byte> bytes;
    if (encoding == "hex") {
      bytes = UtilService::hexToVector(message);
    } else if (encoding == "base64") {
      bytes = UtilService::base64ToVector(message);
    } else {
      bytes = UtilService::stringToVector(message);
    }

    std::vector<std::byte> signature = privateKey->sign(bytes);
      
    return {
      .signedMessage = UtilService::vectorToHex(signature),
      .bytes = signature,
    };
  }

  bool Blade::signVerify(std::string message, std::string signatureHex, std::string key, std::string encoding /* hex|base64|string */) {    
    std::vector<std::byte> bytes;
    if (encoding == "hex") {
      bytes = UtilService::hexToVector(message);
    } else if (encoding == "base64") {
      bytes = UtilService::base64ToVector(message);
    } else {
      bytes = UtilService::stringToVector(message);
    }
    
    std::vector<std::byte> signature = UtilService::hexToVector(signatureHex);
    std::unique_ptr<PublicKey> publicKey = ECDSAsecp256k1PublicKey::fromString(key);

    return publicKey->verifySignature(signature, bytes);
  }

  TxReceipt Blade::contractCallFunction(std::string contractId, std::string functionName, ContractFunctionParameters parameters, std::string accountId, std::string accountPrivateKey, long long gas, bool bladePayFee) {
    const std::shared_ptr<PrivateKey> privateKey = ECDSAsecp256k1PrivateKey::fromString(accountPrivateKey);
    Client client = this->getClient();
    client.setOperator(AccountId::fromString(accountId), privateKey);
    
    if (bladePayFee) {
      BladeTxResponse bladeTxResponse = apiService.signContractCallTx(parameters.toBytes(functionName), contractId, functionName, gas, false);
      const WrappedTransaction tx = Transaction<TransferTransaction>::fromBytes(bladeTxResponse.bytes);

      if (tx.getTransactionType() == TransactionType::CONTRACT_EXECUTE_TRANSACTION) {
        ContractExecuteTransaction transaction = *tx.getTransaction<ContractExecuteTransaction>();

        TransactionResponse txResp = transaction
          .sign(privateKey)
          .execute(client);

        std::cout << "executed." << std::endl;

        TransactionReceipt receipt = txResp.getReceipt(client);

        return UtilService::formatReceipt(receipt);
      }
      throw std::runtime_error("Failed create ContractExecuteTransaction");
    } else {
      auto id = UtilService::splitIdToIntTuple(contractId);

      TransactionResponse txResp = ContractExecuteTransaction()
        .setContractId(ContractId(std::get<0>(id), std::get<1>(id), std::get<2>(id)))
        .setGas(gas)
        .setFunction(functionName, parameters)
        .execute(client);
        
      std::cout << "executed." << std::endl;

      TransactionReceipt receipt = txResp.getReceipt(client);

      return UtilService::formatReceipt(receipt);
    }
  }

  ContractFunctionResult Blade::contractCallQueryFunction(std::string contractId, std::string functionName, ContractFunctionParameters parameters, std::string accountId, std::string accountPrivateKey, long long gas, double maxQueryPayment, std::vector<std::string> returnTypes) {
    auto id = UtilService::splitIdToIntTuple(contractId);
    ContractId contract = ContractId(std::get<0>(id), std::get<1>(id), std::get<2>(id));
    
    Client client = this->getClient();
    client.setOperator(AccountId::fromString(accountId), ECDSAsecp256k1PrivateKey::fromString(accountPrivateKey));

    ContractFunctionResult result = ContractCallQuery()
      .setContractId(contract)
      .setGas(gas)
      .setMaxQueryPayment(Hbar(maxQueryPayment, HbarUnit::HBAR()))
      .setFunction(functionName, parameters)
      .execute(client);

    return result;
  }

  TxReceipt Blade::deleteAccount(std::string deleteAccountId, std::string deletePrivateKey, std::string transferAccountId, std::string operatorAccountId, std::string operatorPrivateKey) {
    const std::shared_ptr<PrivateKey> deleteAccountKey = ECDSAsecp256k1PrivateKey::fromString(deletePrivateKey);
    const std::shared_ptr<PrivateKey> operatorAccountKey = ECDSAsecp256k1PrivateKey::fromString(operatorPrivateKey);
    Client client = this->getClient();
    client.setOperator(AccountId::fromString(operatorAccountId), operatorAccountKey);

    TransactionResponse txResp = AccountDeleteTransaction()
      .setDeleteAccountId(AccountId::fromString(deleteAccountId))
      .setTransferAccountId(AccountId::fromString(transferAccountId))
      .freezeWith(&client)
      .sign(deleteAccountKey)
      .execute(client);

    std::cout << "executed." << std::endl;

    TransactionReceipt receipt = txResp.getReceipt(client);

    return UtilService::formatReceipt(receipt);
  }

  std::string Blade::getC14url(std::string asset, std::string account, std::string amount) {
    std::string clientId = apiService.getClientId();
    asset = UtilService::toUpperCase(asset);
    std::vector<std::string> params = {"clientId=" + clientId};
    
    std::string targetAssetId = "";
    if (asset == "USDC") {
      targetAssetId = "b0694345-1eb4-4bc4-b340-f389a58ee4f3";
    } else if (asset == "HBAR") {
      targetAssetId = "d9b45743-e712-4088-8a31-65ee6f371022";
    } else if (asset == "KARATE") {
      targetAssetId = "057d6b35-1af5-4827-bee2-c12842faa49e";
    } else if (UtilService::isUUID(asset)) {
      targetAssetId = asset;
    }
    if (targetAssetId != "") {
      params.push_back("targetAssetId=" + targetAssetId);
      params.push_back("targetAssetIdLock=true");
    }


    if (amount != "") {
      params.push_back("sourceAmount=" + amount);
      params.push_back("quoteAmountLock=true");
    }

    if (account != "") {
      params.push_back("targetAddress=" + account);
      params.push_back("targetAddressLock=true");
    }

    std::string url = "https://pay.c14.money/?";
    for (auto it = params.begin(); it != params.end(); ++it) {
      const std::string& param = *it;
      url += param;

      if (std::next(it) != params.end()) {
        url += "&";
      }
    }

    return url;
  }

  TransactionsHistoryData Blade::getTransactions(std::string accountId, std::string transactionType, std::string nextPage, int transactionsLimit) {
    return apiService.getTransactionsFrom(accountId, transactionType, nextPage, transactionsLimit);
  }



  ///////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////
  /////     P R I V A T E                                              //////
  ///////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////

  MnemonicBIP39 Blade::getMnemonic() {
    // TODO implement https://github.com/Blade-Labs/blade-sdk.js/pull/9/files

    // TODO check if menemonic is valid
    
    MnemonicBIP39 seedPhrase = MnemonicBIP39::generate12WordBIP39Mnemonic();
    return seedPhrase;
  }

  std::shared_ptr<PrivateKey> Blade::getPrivateKey(MnemonicBIP39 mnemonic) {
    // return mnemonic.toStandardECDSAsecp256k1PrivateKey();
    return ECDSAsecp256k1PrivateKey::fromSeed(mnemonic.toSeed())->derive(44)->derive(3030)->derive(0)->derive(0);
  }

  Client Blade::getClient() {
    if (this->network == Network::Mainnet) {
      return Client::forMainnet();
    } else {
      return Client::forTestnet();
    }
  }

  std::ostream& operator<<(std::ostream& os, Blade& blade) {
    InfoData info = blade.getInfo();
    os << info;
    
    return os;
  }
}

