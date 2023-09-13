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

std::string apiKey = "Rww3x27z3Q9rrIvRQ6qGgIRppxz5e5HHPWdARyxnMXpe77WD5MW39REBXXvRZsZE";
std::string network = "";
std::string dAppCode = "unitysdktest";
std::string fingerprint = "BC238E19-6B3D-5CFC-A26A-21499FF7C25E";
std::string sdkVersion = "Unity@0.6.4";
Client client;

using namespace Hedera;


int main(int argc, char** argv) {
  std::cout << "Blade-SDK inside namespace:" << std::endl;

  BladeSDK::BladeClient bladeClient("TESTNET");
  bladeClient.createAccountBlade();


}
//   BladeSDK::init("ygUgCzRrsvhWmb3dsLcDpGnJpSZ4tk8hACmZqg9WngpuQYKdnD5m8FjfPV3XVUeB", "TESTNET", "unitysdktest", "O9LAocV5ISChRrBCtvpY");
//   // std::cout << "createAccountBlade(): " <<  std::endl;
//   // BladeSDK::AccountData accountData = BladeSDK::createAccountBlade();
  
//   std::cout << "SecurityService::encrypt(): " << BladeSDK::SecurityService::encrypt("O9LAocV5ISChRrBCtvpY", "ygUgCzRrsvhWmb3dsLcDpGnJpSZ4tk8hACmZqg9WngpuQYKdnD5m8FjfPV3XVUeB") <<  std::endl;
//   // std::cout << "expected: MDAwMDAwMDAwMDAw1DMp/gSyfTBo5CYe+6CwQQU1wN0Mdu1mPkhy8YU/64SVaerk" <<  std::endl;
//   // std::cout << "expected: MDAwMDAwMDAwMDAw1DMp/gSyfTBo5CYe+6CwQQU1wN0=" <<  std::endl;
  


//   // if (argc > 1) {
//   //   std::string action = argv[1];
//   //   // if (action == "createAccount") {
//   //   //   AccountData accountData = createAccount(argv[2], argv[3]);
//   //   //   printAccount(accountData);
//   //   // } else 
//   //   if (action == "createAccountBlade") {
//   //     BladeSDK::AccountData accountData = BladeSDK::createAccountBlade();
//   //     printAccount(accountData);
//   //   } else if (action == "import") {
//   //     BladeSDK::AccountData accountData = BladeSDK::importAccount(argv[2]);
//   //     printAccount(accountData);
//   //   } else if (action == "fpApiKey") {
//   //     std::string fingerprint = BladeSDK::getFingerprintApiKey();
//   //     std::cout << "Fingerprint: " << fingerprint << std::endl;
    
//   //   // } else if (action == "sign") {
//   //   //   std::vector<unsigned char> signature = signMessage(argv[2], argv[3]);
//   //   // } else if (action == "verify") {
//   //   //   bool valid = verifyMessage(argv[2], argv[3], argv[4]);
//   //   //   std::cout << "Valid signature: " << std::to_string(valid) << std::endl;
//   //   } else {
//   //     std::cout << "Unknown action: '" << argv[1] << "'" <<  std::endl;
//   //   }
//   // } else {
//   //   std::cout << "Blade-SDK CPP Demo. Checkout README.md for examples:" << std::endl;
//   // }


//     // hash deviceId sha256
//     // std::string input = "550e8400-e29b-41d4-a716-446655440000";

//     // unsigned char hash[SHA256_DIGEST_LENGTH];
//     // SHA256_CTX sha256;
//     // SHA256_Init(&sha256);
//     // SHA256_Update(&sha256, input.c_str(), input.size());
//     // SHA256_Final(hash, &sha256);

//     // char hexHash[2 * SHA256_DIGEST_LENGTH + 1];
//     // for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
//     //     sprintf(hexHash + (i * 2), "%02x", hash[i]);
//     // }

//     // std::cout << std::string(hexHash) << std::endl;



//   return 0;  

// }

namespace BladeSDK {


  BladeClient::BladeClient(const std::string& network_) {
      network = network_;

      if (network == "TESTNET") {
        client = Client::forTestnet();
      } else if (network == "MAINNET") {
        // still not implemented in hedera-sdk-cpp
        // client = Client::forMainnet();
      } else {
        std::cerr << "Unknown network. Use TESTNET or MAINNET" << std::endl;
        throw;
      }
    }

    AccountData BladeClient::createAccountBlade() {
      MnemonicBIP39 seedPhrase = getMnemonic();
      std::unique_ptr<PrivateKey> privateKey = getPrivateKey(seedPhrase);
      std::shared_ptr<PublicKey> publicKey = privateKey->getPublicKey();

      std::string tvte = SecurityService::getTvte(sdkVersion, apiKey);

      std::cout << "tvte: " << tvte << std::endl;
      


      json account = ApiService::createAccount(publicKey, apiHost, apiKey, fingerprint, dAppCode, network, tvte);

      std::cout << "account: " << account << std::endl;

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
  












  void init(std::string apiKey_, std::string network_, std::string dAppCode_, std::string fingerprint_) {
    apiKey = apiKey_;
    network = network_;
    dAppCode = dAppCode_;
    fingerprint = fingerprint_;
    if (network == "TESTNET")
    {
      client = Client::forTestnet();
    }
    else if (network == "MAINNET")
    {
        // still not implemented in hedera-sdk-cpp
        // client = Client::forMainnet();
    }
    else
    {
      std::cerr << "Unknown network. Use TESTNET or MAINNET" << std::endl;
      throw;
    }
  }

  std::string getFingerprintApiKey() {
    return ApiService::getFingerprintApiKey();
  }

  AccountData createAccountBlade()
  {
    MnemonicBIP39 seedPhrase = getMnemonic();
    std::unique_ptr<PrivateKey> privateKey = getPrivateKey(seedPhrase);
    std::shared_ptr<PublicKey> publicKey = privateKey->getPublicKey(); 

    json account = ApiService::createAccount(publicKey, apiHost, apiKey, fingerprint, dAppCode, network, "tvte header here");

    // TODO  
    // updateAccountTransactionBytes
    // calc evmAddress
    // sign data with newly created account
    // verify signature by data and publicKey

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

  AccountData importAccount(std::string seedPhrase) {
    std::string passphrase = "";
    MnemonicBIP39 mnemonic = MnemonicBIP39::initializeBIP39Mnemonic(seedPhrase);
    std::unique_ptr<PrivateKey> privateKey = getPrivateKey(mnemonic);
    std::string accountId = ApiService::getAccountsFromPublicKey(privateKey->getPublicKey(), network);
    
    return {
      .seedPhrase = mnemonic.toString(),
      .publicKey = privateKey->getPublicKey()->toStringDer(),
      .privateKey = privateKey->toStringDer(),
      .accountId = accountId,
    };
  }


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
  ///////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////

  MnemonicBIP39 getMnemonic() {
    // TODO implement https://github.com/Blade-Labs/blade-sdk.js/pull/9/files
    
    MnemonicBIP39 seedPhrase = MnemonicBIP39::generate12WordBIP39Mnemonic();
    return seedPhrase;
  }

  std::unique_ptr<PrivateKey> getPrivateKey(MnemonicBIP39 mnemonic) {
    return mnemonic.toStandardECDSAsecp256k1PrivateKey();
    // return ECDSAsecp256k1PrivateKey::fromSeed(mnemonic.toSeed())->derive(44)->derive(3030)->derive(0)->derive(0);
  }

  void printAccount(AccountData accountData) {
    std::cout << "Account Id: " << accountData.accountId << std::endl;
    std::cout << "SeedPhrase: " << accountData.seedPhrase << std::endl;
    std::cout << "PrivateKey: " << accountData.privateKey << std::endl;
    std::cout << "Public key: " << accountData.publicKey << std::endl;
  }

  void printVec(std::vector<unsigned char> vec) {
    for (int i = 0; i < vec.size(); ++i)
    {
      std::cout << (int)vec[i] << " ";
    }
    std::cout << std::endl;  
  }

  std::string vectorToHex(const std::vector<unsigned char>& data) {
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

