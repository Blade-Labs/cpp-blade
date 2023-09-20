#include "../include/BladeSDK.h"

#include "ECDSAsecp256k1PrivateKey.h"
#include "ED25519PrivateKey.h"
#include "MnemonicBIP39.h"



#include "Client.h"
#include "AccountCreateTransaction.h"
#include "TransactionReceipt.h"
#include "TransactionResponse.h"
#include "TransactionRecord.h"

#include <iostream>
#include <string>
#include <nlohmann/json.hpp>
#include "service/apiService.cpp"
#include "service/accountService.cpp"
#include "service/securityService.cpp"
#include "service/utilService.cpp"

std::string apiHost = "api.bld-dev.bladewallet.io";
std::string apiPath = "/openapi/v7";

using namespace Hedera;


int main(int argc, char** argv) {
  std::cout << "Blade-SDK inside namespace:" << std::endl;

  std::string privateKeyHex = "3030020100300706052b8104000a04220420ebccecef769bb5597d0009123a0fd96d2cdbe041c2a2da937aaf8bdc8731799b";
  std::string publicKeyHex = "302d300706052b8104000a032200029dc73991b0d9cdbb59b2cd0a97a0eaff6de801726cb39804ea9461df6be2dd30";
  std::string dAppCode = "unitysdktest";
  std::string apiKey = "Rww3x27z3Q9rrIvRQ6qGgIRppxz5e5HHPWdARyxnMXpe77WD5MW39REBXXvRZsZE";


  BladeSDK::Blade blade(apiKey, BladeSDK::Network::Testnet, dAppCode, BladeSDK::SdkEnvironment::CI);
  // WIP
  // std::cout << "createAccountBlade: " << blade.createAccountBlade() << std::endl;
  
  // std::cout << "getAccountInfo: " << blade.getAccountInfo("0.0.346533") << std::endl;

  // std::cout << "getBalance: " << blade.getBalance("0.0.346533") << std::endl;

  // std::cout << "importAccount: " << blade.importAccount("best soccer little verify love ladder else kick depth mesh silly desert", true) << std::endl; // ECDSA, 0.0.2018696

  // WIP
  // // std::cout << "transferHbars: " << blade.transferHbars("0.0.346533", privateKeyHex, "0.0.346530", "15", "cpp-sdk-test") << std::endl;
  blade.transferHbars("0.0.346533", privateKeyHex, "0.0.346530", "15", "cpp-sdk-test");

  // WIP
  // blade.transferTokens("0.0.433870", "0.0.346533", privateKeyHex, "0.0.346530", "1", "cpp-sdk-paid-token-transfer", false);

  // WIP
  // blade.transferTokens("0.0.433870", "0.0.346533", privateKeyHex, "0.0.346530", "1", "cpp-sdk-free-token-transfer", true);

  // // sign + verify
  // std::string message = "hello";
  // std::string messageBase64 = BladeSDK::UtilService::stringToBase64(message);
  // std::string messageHex = BladeSDK::UtilService::vectorToHex(BladeSDK::UtilService::stringToVector(message));

  // BladeSDK::SignMessageData signature = blade.sign(message, privateKeyHex, "string");
  // std::cout << "Sign str (" << message << "): " << signature << std::endl;
  // std::cout << "Valid?: " << blade.signVerify(message, signature.signedMessage, publicKeyHex, "string") << std::endl;  

  // signature = blade.sign(messageBase64, privateKeyHex, "base64");
  // std::cout << "Sign base64 (" << messageBase64 << "): " << signature << std::endl;
  // std::cout << "Valid?: " << blade.signVerify(messageBase64, signature.signedMessage, publicKeyHex, "base64") << std::endl;

  // signature = blade.sign(messageHex, privateKeyHex, "hex");
  // std::cout << "Sign hex (" << messageHex << "): " << signature << std::endl;
  // std::cout << "Valid?: " << blade.signVerify(messageHex, signature.signedMessage, publicKeyHex, "hex") << std::endl;




    // delete account
            // CreateAccountData accountOperator = new CreateAccountData {accountId = "0.0.346533", privateKey = privateKeyHex};
            // CreateAccountData accountToDelete = new CreateAccountData {accountId = "0.0.486856", privateKey = "3030020100300706052b8104000a04220420ff3ee87eac8651f1aca58570b7aa33b1809bd956f13734d29767e97385cb9f15"};

            // Debug.Log(
            //     await bladeSdk.deleteAccount(
            //         accountToDelete.accountId,
            //         accountToDelete.privateKey,
            //         accountOperator.accountId, // transferAccountId
            //         accountOperator.accountId,
            //         accountOperator.privateKey
            //     )
            // );



    // contract call
            // ContractFunctionParameters parameters = new ContractFunctionParameters();
            // parameters.addString("Hello Unity SDK [self pay]");
            // Debug.Log(
            //     await bladeSdk.contractCallFunction(
            //         "0.0.416245", 
            //         "set_message", 
            //         parameters, 
            //         "0.0.346533", 
            //         privateKeyHex, 
            //         150000,
            //         false
            //     )
            // );


            // contract call (Blade pay fee)
            // ContractFunctionParameters parameters = new ContractFunctionParameters();
            // parameters.addString("Hello Unity SDK [Blade pay]");
            // Debug.Log(
            //     await bladeSdk.contractCallFunction(
            //         "0.0.416245", 
            //         "set_message", 
            //         parameters, 
            //         "0.0.346533", 
            //         privateKeyHex, 
            //         150000,
            //         true
            //     )
            // );


            // contract call query (self pay)
            // Debug.Log(
            //     await bladeSdk.contractCallQueryFunction(
            //         "0.0.416245", 
            //         "get_message", 
            //         new ContractFunctionParameters(), 
            //         "0.0.346533", 
            //         privateKeyHex, 
            //         150000, // gas
            //         70000000, // tinybars
            //         new List<string> {"string", "int32"}
            //     )
            // );

            // C14 url
            // Debug.Log(
            //     await bladeSdk.getC14url("karate", "0.0.123456", "1234")
            // );
            
           
            // hethersSign
            // Debug.Log(await bladeSdk.hethersSign("hello", privateKeyHex, "utf8"));
            // Debug.Log("0x25de7c26ecfa4f28d8b96a95cf58ea7088a72a66b311c796090cb4c7d58c11217b4a7b174b4c31b90c3babb00958b2120274380404c4f1196abe3614df3741561b");

            // splitSignature
            // Debug.Log(await bladeSdk.splitSignature("0x25de7c26ecfa4f28d8b96a95cf58ea7088a72a66b311c796090cb4c7d58c11217b4a7b174b4c31b90c3babb00958b2120274380404c4f1196abe3614df3741561b"));
            // Debug.Log("v: 27, r: '0x25de7c26ecfa4f28d8b96a95cf58ea7088a72a66b311c796090cb4c7d58c1121', s: '0x7b4a7b174b4c31b90c3babb00958b2120274380404c4f1196abe3614df374156'");
  

            // getParamsSignature
            // ContractFunctionParameters parameters = new ContractFunctionParameters();
            // parameters
            //     .addAddress("0.0.346533")
            //     .addUInt64Array(new List<ulong> {300000, 300000})
            //     .addUInt64Array(new List<ulong> {6})
            //     .addUInt64Array(new List<ulong> {2})
            // ;
            // Debug.Log(await bladeSdk.getParamsSignature(parameters, privateKeyHex));
            // Debug.Log("v: 28, r: '0xe5e662d0564828fd18b2b5b228ade288ad063fadca76812f7902f56cae3e678e', s: '0x61b7ceb82dc6695872289b697a1bca73b81c494288abda29fa022bb7b80c84b5'");

            //get transaction history
            // Debug.Log(await bladeSdk.getTransactions("0.0.346533", "CRYPTOTRANSFER", "", 5));
            // Debug.Log(await bladeSdk.getTransactions("0.0.346533", "CRYPTOCREATEACCOUNT", "", 20));
            // Debug.Log(await bladeSdk.getTransactions("0.0.346533", "", nextPage, 5));
          



}

namespace BladeSDK {
  Blade::Blade(const std::string& apiKey, const Network& network, const std::string& dAppCode, const SdkEnvironment& sdkEnvironment)
    : apiService(apiKey, network, dAppCode, sdkEnvironment, sdkVersion)
  {
    this->network = network;
    this->apiKey = apiKey;
    this->dAppCode = dAppCode;
    this->sdkEnvironment = sdkEnvironment;

    // TODO get visitorId from fingerprint
    // TODO register device
    apiService.setVisitorId(this->visitorId);
  }

  AccountData Blade::createAccountBlade() {
    MnemonicBIP39 seedPhrase = getMnemonic();
    std::unique_ptr<PrivateKey> privateKey = getPrivateKey(seedPhrase);
    std::shared_ptr<PublicKey> publicKey = privateKey->getPublicKey();

    json account = apiService.createAccount(publicKey);
    std::cout << "account: " << account.dump(4) << std::endl;

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
      .publicKey = result["key"].value("key", ""),
      .evmAddress = result.value("evm_address", ""),
    };
  }

  AccountBalanceData Blade::getBalance(std::string accountId) {
    return apiService.getBalance(accountId);
  }
  
  PrivateKeyData Blade::importAccount(std::string seedPhrase, bool lookupAccounts) {
    MnemonicBIP39 mnemonic = MnemonicBIP39::initializeBIP39Mnemonic(seedPhrase);
    std::unique_ptr<PrivateKey> privateKey = getPrivateKey(mnemonic);
    std::vector<std::string> accountIds = apiService.getAccountsFromPublicKey(privateKey->getPublicKey()->toStringRaw());

    return {
      .privateKey = privateKey->toStringDer(),
      .publicKey = privateKey->getPublicKey()->toStringDer(),
      .seedPhrase = mnemonic.toString(),
      .accounts = accountIds,
    };
  }  

  TransactionReceipt Blade::transferHbars(std::string accountId, std::string accountPrivateKey, std::string recieverAccount, std::string amount, std::string memo) {
      Client client = this->getClient();
      client.setOperator(AccountId::fromString(accountId), ECDSAsecp256k1PrivateKey::fromString(accountPrivateKey).get());
      const Hbar amountHbar(std::stoull(amount), HbarUnit::HBAR());

      TransactionResponse txResponse = TransferTransaction()
                                     .addHbarTransfer(AccountId::fromString(accountId), amountHbar.negated())
                                     .addHbarTransfer(AccountId::fromString(recieverAccount), amountHbar)
                                     .setTransactionMemo(memo)
                                     .execute(client);

      std::cout << "executed" << std::endl;

      return txResponse.getReceipt(client);
  }

  TransactionReceipt Blade::transferTokens(std::string tokenId, std::string accountId, std::string accountPrivateKey, std::string receiverId, std::string amount, std::string memo, bool freeTransfer) {
    std::unique_ptr<PrivateKey> privateKey = ECDSAsecp256k1PrivateKey::fromString(accountPrivateKey);

    Client client = this->getClient();
    client.setOperator(AccountId::fromString(accountId), privateKey.get());
    json tokenMeta = apiService.GET("/api/v1/tokens/" + tokenId);
    std::string decimals = tokenMeta.value("decimals", "0");
    long long correctedAmount = std::stoull(amount) * std::pow(10, std::stoi(decimals));

    if (freeTransfer) {
      FreeTokenTransferResponse response = apiService.freeTokenTransfer(accountId, receiverId, correctedAmount, memo);
      
      const WrappedTransaction tx = Transaction<TokenAssociateTransaction>::fromBytes(response.bytes);
      if (tx.getTransactionType() == TransactionType::TRANSFER_TRANSACTION) {
        TransferTransaction transferTransaction = *tx.getTransaction<TransferTransaction>();
        TransactionResponse txResp = transferTransaction
          .freezeWith(&client)
          .sign(privateKey.get())
          .execute(client)
        ;
        std::cout << "executed" << std::endl;
        TransactionReceipt txReceipt = txResp.getReceipt(client);

        std::cout << "AccountId: " << txReceipt.mAccountId.value().toString() << std::endl;
        return txReceipt;
      }
    } else {
      TokenId token = TokenId::fromString(tokenId);

      TransactionResponse txResponse = TransferTransaction()
                                      .addTokenTransfer(token, AccountId::fromString(accountId), -correctedAmount)
                                      .addTokenTransfer(token, AccountId::fromString(receiverId), correctedAmount)
                                      .freezeWith(&client)
                                      .execute(client);
        
        std::cout << "executed" << std::endl;

        return txResponse.getReceipt(client);
    }

    throw std::runtime_error("Transaction type not supported");
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

  std::unique_ptr<PrivateKey> Blade::getPrivateKey(MnemonicBIP39 mnemonic) {
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





  // void printVec(std::vector<std::byte> vec) {
  //   for (int i = 0; i < vec.size(); ++i)
  //   {
  //     std::cout << (int)vec[i] << " ";
  //   }
  //   std::cout << std::endl;  
  // }

}

