#include "main.h"


std::string apiHost = "rest.prod.bladewallet.io";
std::string apiPath = "/openapi/v7";

std::string apiKey = "";
std::string network = "";
std::string dAppCode = "";
std::string fingerprint = "";
Client client;

int main(int argc, char** argv)
{
    init("apiKey", "TESTNET", "dAppCode", "6C9781BF-6B49-4182-B584-08F5EF28B224");

    ApiService::AccountData accountData = createAccount();

    std::cout << "Account Id: " << accountData.accountId << std::endl;
    std::cout << "SeedPhrase: " << accountData.seedPhrase << std::endl;
    std::cout << "PrivateKey: " << accountData.privateKey << std::endl;
    std::cout << "Public key: " << accountData.publicKey << std::endl;


    return 0;
    

  // MNEMONIC TEST

  std::string passphrase = "";
  std::string seedPhrase = "mutual picnic upgrade spice student spoon pelican bicycle save refuse depend ring";
  if (argc > 1) { seedPhrase = argv[1]; }

  std::cout << "Mnemonic: " << seedPhrase << std::endl;
  std::cout << "Passphrase: " << passphrase << std::endl;

  MnemonicBIP39 mnemonic = MnemonicBIP39::initializeBIP39Mnemonic(seedPhrase);
  std::cout << "Input MnemonicBIP39: " << mnemonic.toString() << std::endl;

  std::unique_ptr<ECDSAsecp256k1PrivateKey> ecdsaSecp256k1PrivateKeyMy =
    mnemonic.toStandardECDSAsecp256k1PrivateKey();
    
  std::cout << std::endl  << "Generated ECDSAsecp256k1PrivateKey from input mnemonic with no passphrase: " << ecdsaSecp256k1PrivateKeyMy->toString() << std::endl;
  std::cout << "Exprcted: 877a8befeba3226516dee477c99857c1a4228941c7a16232e1850e98fd9d6c63" << std::endl;

  // std::unique_ptr<ED25519PrivateKey> ed25519PrivateKeyMy = ED25519PrivateKey::fromBIP39Mnemonic(mnemonic, "")->derive(44)->derive(3030)->derive(0)->derive(0);
  // std::cout << "Generated ED25519PrivateKey from input mnemonic with no passphrase: " << ed25519PrivateKeyMy->toString() << std::endl;

  std::cout << std::endl << std::endl;




  // SIGNING TEST

  //std::string privKeyString = "877a8befeba3226516dee477c99857c1a4228941c7a16232e1850e98fd9d6c63";
  std::string privKeyString = "6216864486b3bf242a84dd64a4a48e07791e8f186cdf9bdcc118fc6c8ce3fcb9";
  std::cout << "Private key string: " << privKeyString << std::endl;

  std::unique_ptr<ECDSAsecp256k1PrivateKey> ecdsaFromString = ECDSAsecp256k1PrivateKey::fromString(privKeyString);
  std::cout << "ECDSAsecp256k1PrivateKey from string: " << ecdsaFromString->toString() << std::endl;

  std::string toSign = "test";
  std::vector<unsigned char> vec(toSign.begin(), toSign.end());

  std::cout << "Data: ";
  for (int i = 0; i < vec.size(); ++i)
  {
    std::cout << (int)vec[i] << " ";
  }
  std::cout << std::endl;

  
  std::vector<unsigned char> signature1 = ecdsaSecp256k1PrivateKeyMy->sign(vec);
  std::vector<unsigned char> signature2 = ecdsaFromString->sign(vec);
  std::cout << "Signature1: ";
  for (int i = 0; i < signature1.size(); ++i)
  {
    std::cout << (int)signature1[i] << " ";
  }


  std::cout << std::endl << "Signature2: ";
  for (int i = 0; i < signature2.size(); ++i)
  {
    std::cout << (int)signature2[i] << " ";
  }
  std::cout << std::endl;

  std::shared_ptr<PublicKey> publicKey = ecdsaSecp256k1PrivateKeyMy->getPublicKey();
  
  std::cout << "Verify sig1: " << ecdsaSecp256k1PrivateKeyMy->getPublicKey()->verifySignature(signature1, vec)
            << std::endl;
  std::cout << "Verify sig2: " << ecdsaFromString->getPublicKey()->verifySignature(signature2, vec)
            << std::endl;


  return 0;
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

ApiService::AccountData createAccount()
{
  MnemonicBIP39 seedPhrase = MnemonicBIP39::generate12WordBIP39Mnemonic();
  std::unique_ptr<ECDSAsecp256k1PrivateKey> privateKey = seedPhrase.toStandardECDSAsecp256k1PrivateKey();
  std::shared_ptr<PublicKey> publicKey = privateKey->getPublicKey();

  
  // generate json
  // parse json
  // updateAccountTransactionBytes
  // calc evmAddress
  // return result

  // sign data with newly created account
  // verify signature by data and publicKey

  json account = ApiService::createAccount(publicKey, apiHost, apiKey, fingerprint, dAppCode, network);

  
  AccountService::executeUpdateAccountTransactions(
    &client, 
    privateKey, 
    account.value("updateAccountTransactionBytes", ""), 
    account.value("transactionBytes", "")
  );
  


  //std::cout << "createAccountApi(): " << account.dump(20) << std::endl;

          // id, transactionBytes, updateAccountTransactionBytes, transactionId

  // executeUpdateAccountTransactions(this.getClient(), privateKey, updateAccountTransactionBytes, transactionBytes);

  // const evmAddress = hethers.utils.computeAddress(`0x $ { privateKey.publicKey.toStringRaw() }`);
  
  return {
    .seedPhrase = seedPhrase.toString(),
    .publicKey = account.value("publicKey", ""),
    .privateKey = privateKey->toString(),
    .accountId = account.value("id", ""),
  };


//  json account = json::parse(res);
  //auto account = nlohmann::json::parse(boost::beast::buffers_to_string(res.body().data()));


  //std::cout << account.dump(4) << std::endl;
}
