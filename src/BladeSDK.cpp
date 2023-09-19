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

std::string apiHost = "api.bld-dev.bladewallet.io";
std::string apiPath = "/openapi/v7";

using namespace Hedera;


int main(int argc, char** argv) {
  std::cout << "Blade-SDK inside namespace:" << std::endl;

  BladeSDK::Blade blade("Rww3x27z3Q9rrIvRQ6qGgIRppxz5e5HHPWdARyxnMXpe77WD5MW39REBXXvRZsZE", BladeSDK::Network::Testnet, "unitysdktest", BladeSDK::SdkEnvironment::CI);
  // WIP
  // std::cout << "createAccountBlade: " << blade.createAccountBlade() << std::endl;
  
  // std::cout << "getAccountInfo: " << blade.getAccountInfo("0.0.346533") << std::endl;

  // std::cout << "getBalance: " << blade.getBalance("0.0.346533") << std::endl;

  // std::cout << "importAccount: " << blade.importAccount("best soccer little verify love ladder else kick depth mesh silly desert", true) << std::endl; // ECDSA, 0.0.2018696

  // WIP
  // // std::cout << "transferHbars: " << blade.transferHbars("0.0.346533", "3030020100300706052b8104000a04220420ebccecef769bb5597d0009123a0fd96d2cdbe041c2a2da937aaf8bdc8731799b", "0.0.346530", "15", "cpp-sdk-test") << std::endl;
  // blade.transferHbars("0.0.346533", "3030020100300706052b8104000a04220420ebccecef769bb5597d0009123a0fd96d2cdbe041c2a2da937aaf8bdc8731799b", "0.0.346530", "15", "cpp-sdk-test");

            // transfer tokens
            // Debug.Log(
            //     await bladeSdk.transferTokens(
            //         "0.0.433870",
            //         "0.0.346533",
            //         "3030020100300706052b8104000a04220420ebccecef769bb5597d0009123a0fd96d2cdbe041c2a2da937aaf8bdc8731799b",
            //         "0.0.346530",
            //          "1",
            //         "unity-sdk-paid-token-transfer",
            //         false
            //     )
            // );

            // free transfer tokens
            // Debug.Log(
            //     await bladeSdk.transferTokens(
            //         "0.0.433870", /// token id assigned on server side for dAppCode
            //         "0.0.346533",
            //         "3030020100300706052b8104000a04220420ebccecef769bb5597d0009123a0fd96d2cdbe041c2a2da937aaf8bdc8731799b",
            //         "0.0.346530",
            //          "1",
            //         "unity-sdk-free-token-transfer",
            //         true
            //     )
            // );



    // delete account
            // CreateAccountData accountOperator = new CreateAccountData {accountId = "0.0.346533", privateKey = "3030020100300706052b8104000a04220420ebccecef769bb5597d0009123a0fd96d2cdbe041c2a2da937aaf8bdc8731799b"};
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
            //         "3030020100300706052b8104000a04220420ebccecef769bb5597d0009123a0fd96d2cdbe041c2a2da937aaf8bdc8731799b", 
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
            //         "3030020100300706052b8104000a04220420ebccecef769bb5597d0009123a0fd96d2cdbe041c2a2da937aaf8bdc8731799b", 
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
            //         "3030020100300706052b8104000a04220420ebccecef769bb5597d0009123a0fd96d2cdbe041c2a2da937aaf8bdc8731799b", 
            //         150000, // gas
            //         70000000, // tinybars
            //         new List<string> {"string", "int32"}
            //     )
            // );

            // C14 url
            // Debug.Log(
            //     await bladeSdk.getC14url("karate", "0.0.123456", "1234")
            // );
            
            // sign
            // Debug.Log(
            //     // await bladeSdk.sign("aGVsbG8=", "3030020100300706052b8104000a04220420ebccecef769bb5597d0009123a0fd96d2cdbe041c2a2da937aaf8bdc8731799b", "base64")
            //     await bladeSdk.sign("hello", "3030020100300706052b8104000a04220420ebccecef769bb5597d0009123a0fd96d2cdbe041c2a2da937aaf8bdc8731799b", "utf8")
            // );
            // Debug.Log("signedMessage: '27cb9d51434cf1e76d7ac515b19442c619f641e6fccddbf4a3756b14466becb6992dc1d2a82268018147141fc8d66ff9ade43b7f78c176d070a66372d655f942'");


            // sign verify
            // Debug.Log(await bladeSdk.signVerify("hello", "27cb9d51434cf1e76d7ac515b19442c619f641e6fccddbf4a3756b14466becb6992dc1d2a82268018147141fc8d66ff9ade43b7f78c176d070a66372d655f942", "302d300706052b8104000a032200029dc73991b0d9cdbb59b2cd0a97a0eaff6de801726cb39804ea9461df6be2dd30", "utf8"));
            // Debug.Log(await bladeSdk.signVerify("aGVsbG8=", "27cb9d51434cf1e76d7ac515b19442c619f641e6fccddbf4a3756b14466becb6992dc1d2a82268018147141fc8d66ff9ade43b7f78c176d070a66372d655f942", "302d300706052b8104000a032200029dc73991b0d9cdbb59b2cd0a97a0eaff6de801726cb39804ea9461df6be2dd30", "base64"));
            // Debug.Log(await bladeSdk.signVerify("signature will not match", "27cb9d51434cf1e76d7ac515b19442c619f641e6fccddbf4a3756b14466becb6992dc1d2a82268018147141fc8d66ff9ade43b7f78c176d070a66372d655f942", "302d300706052b8104000a032200029dc73991b0d9cdbb59b2cd0a97a0eaff6de801726cb39804ea9461df6be2dd30", "utf8"));

            // hethersSign
            // Debug.Log(await bladeSdk.hethersSign("hello", "3030020100300706052b8104000a04220420ebccecef769bb5597d0009123a0fd96d2cdbe041c2a2da937aaf8bdc8731799b", "utf8"));
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
            // Debug.Log(await bladeSdk.getParamsSignature(parameters, "3030020100300706052b8104000a04220420ebccecef769bb5597d0009123a0fd96d2cdbe041c2a2da937aaf8bdc8731799b"));
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

      TransactionReceipt txReceipt = txResponse.getReceipt(client);
      return txReceipt;
  }


  // AccountData createAccount(std::string operatorAccountId, std::string operatorPrivateKey)
  // {
  //   MnemonicBIP39 seedPhrase = getMnemonic();
  //   std::unique_ptr<ECDSAsecp256k1PrivateKey> privateKey = getPrivateKey(seedPhrase);
  //   std::shared_ptr<PublicKey> publicKey = privateKey->getPublicKey();
    
  //   client.setOperator(AccountId::fromString(operatorAccountId), ED25519PrivateKey::fromString(operatorPrivateKey));

  //   TransactionResponse txResp = AccountCreateTransaction()
  //       .setKey(publicKey)
  //       // .setInitialBalance(Hbar(1000ULL, HbarUnit::TINYBAR()))
  //       .execute(client);

  //   TransactionReceipt txReceipt = txResp.getReceipt(client);
    
  //   return {
  //     .seedPhrase = seedPhrase.toString(),
  //     .publicKey = publicKey->toStringDer(),
  //     .privateKey = privateKey->toStringDer(),
  //     .accountId = txReceipt.mAccountId.value().toString(),
  //   };
  // }

  // AccountData importAccount(std::string seedPhrase) {
  //   std::string passphrase = "";
  //   MnemonicBIP39 mnemonic = MnemonicBIP39::initializeBIP39Mnemonic(seedPhrase);
  //   std::unique_ptr<PrivateKey> privateKey = getPrivateKey(mnemonic);
  //   std::string accountId = ApiService::getAccountsFromPublicKey(privateKey->getPublicKey(), "TESTNET"); // TODO TODO TODO TODO TODO TODO TODO 
    
  //   return {
  //     .seedPhrase = mnemonic.toString(),
  //     .publicKey = privateKey->getPublicKey()->toStringDer(),
  //     .privateKey = privateKey->toStringDer(),
  //     .accountId = accountId,
  //   };
  // }


  // std::vector<unsigned char> signMessage(std::string message, std::string signerKey) {
  //       // std::shared_ptr<ECDSAsecp256k1PublicKey> publicKey = ECDSAsecp256k1PublicKey::fromString(signerKey);
  //       std::unique_ptr<ED25519PrivateKey> privateKey = ED25519PrivateKey::fromString(signerKey);

  //       std::vector<unsigned char> vec(message.begin(), message.end());
  //       // std::string hexString = vectorToHex(vec);
  //       // std::cout << "Message data (hex): " << hexString << std::endl;

  //       std::vector<unsigned char> signature = privateKey->sign(vec);

  //       // std::cout << "Signature: ";
  //       // printVec(signature);
  //       // std::cout << "Signature (hex): " << vectorToHex(signature) << std::endl;


  //       // std::shared_ptr<PublicKey> publicKey = ecdsaSecp256k1PrivateKeyMy->getPublicKey();
        
  //       // std::cout << "Verify sig1: " << ecdsaSecp256k1PrivateKeyMy->getPublicKey()->verifySignature(signature1, vec)
  //       //           << std::endl;
  //       // std::cout << "Verify sig2: " << ecdsaFromString->getPublicKey()->verifySignature(signature2, vec)
  //       //           << std::endl;
  //       return signature;
  // }


  // bool verifyMessage(std::string message, std::string signatureHex, std::string key) {
    
  //       std::vector<unsigned char> signature = hexToVector(signatureHex);
  //       std::vector<unsigned char> vec(message.begin(), message.end());

  //       // std::shared_ptr<ECDSAsecp256k1PublicKey> publicKey = ECDSAsecp256k1PublicKey::fromString(key);
  //       std::shared_ptr<ED25519PublicKey> publicKey = ED25519PublicKey::fromString(key);

  //       // std::cout << "message: " << message << std::endl;
  //       // std::cout << "signatureHex: " << signatureHex << std::endl;
  //       // std::cout << "publicKey: " << publicKey->toString() << std::endl;

  //       return publicKey->verifySignature(signature, vec);
  // }


  // // TODO response type
  // void transferHbars(std::string accountId, std::string accountPrivateKey, std::string receiverID, double amountHbars) {
  //   const AccountId operatorId = AccountId::fromString(accountId);
  //   client.setOperator(operatorId, ED25519PrivateKey::fromString(accountPrivateKey));
  //   // client.setOperator(operatorId, ECDSAsecp256k1PrivateKey::fromString(accountPrivateKey));

  //   const auto recipientId = AccountId::fromString(receiverID);
  //   const Hbar amount(amountHbars * 100000000, HbarUnit::TINYBAR());

  //   TransactionResponse txResponse = TransferTransaction()
  //                                   .addHbarTransfer(operatorId, amount.negated())
  //                                   .addHbarTransfer(recipientId, amount)
  //                                   .setTransactionMemo("transfer test")
  //                                   .execute(client);

  //   // TransactionRecord txRecord = txResponse.getRecord(client);

  //   // std::cout << "Transferred " << amount.toTinybars() / 100000000 << HbarUnit::HBAR().getSymbol() << std::endl;
  // }

  // // TODO response type
  // void transferTokens(std::string token_id, std::string account_id, std::string account_private_key, std::string receiver_id, double amount_tokens, bool free_transfer) {
  //   const AccountId operatorId = AccountId::fromString(account_id);
  //   client.setOperator(operatorId, ED25519PrivateKey::fromString(account_private_key));
  //   const TokenId tokenId = TokenId::fromString(token_id);
  //   const AccountId recipientId = AccountId::fromString(receiver_id);

  //   const int64_t amount = 1LL;

  //   TransactionResponse txResponse = TransferTransaction()
  //                                     .addTokenTransfer(tokenId, operatorId, -amount)
  //                                     .addTokenTransfer(tokenId, recipientId, amount)
  //                                     .execute(client);
  // }



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





  void printAccount(AccountData accountData) {
    std::cout << "Account Id: " << accountData.accountId << std::endl;
    std::cout << "SeedPhrase: " << accountData.seedPhrase << std::endl;
    std::cout << "PrivateKey: " << accountData.privateKey << std::endl;
    std::cout << "Public key: " << accountData.publicKey << std::endl;
  }

  void printVec(std::vector<std::byte> vec) {
    for (int i = 0; i < vec.size(); ++i)
    {
      std::cout << (int)vec[i] << " ";
    }
    std::cout << std::endl;  
  }

  std::string vectorToHex(const std::vector<std::byte>& data) {
      std::ostringstream oss;
      oss << std::hex << std::setfill('0');
      for (auto byte : data) {
          oss << std::setw(2) << static_cast<int>(byte);
      }
      return oss.str();
  }

  std::vector<unsigned char> hexToVector(const std::string& hexString) {
      std::vector<unsigned char> result;
      result.reserve(hexString.size() / 2);
      for (std::string::size_type i = 0; i < hexString.size(); i += 2) {
          unsigned int byteValue;
          std::stringstream ss;
          ss << std::hex << hexString.substr(i, 2);
          ss >> byteValue;
          result.push_back(static_cast<unsigned char>(byteValue));
      }
      return result;
  }

}

