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

    if (argc > 1) {
      std::string action = argv[1];
      if (action == "createAccount") {
        ApiService::AccountData accountData = createAccount(argv[2], argv[3]);
        printAccount(accountData);
      } else if (action == "createAccountBlade") {
        ApiService::AccountData accountData = createAccountBlade();
        printAccount(accountData);
      } else if (action == "import") {
        ApiService::AccountData accountData = importAccount(argv[2]);
        printAccount(accountData);
      } else if (action == "sign") {
        std::vector<unsigned char> signature = signMessage(argv[2], argv[3]);
      } else if (action == "verify") {
        bool valid = verifyMessage(argv[2], argv[3], argv[4]);
        std::cout << "Valid signature: " << std::to_string(valid) << std::endl;
      } else {
        std::cout << "Unknown action: '" << argv[1] << "'" <<  std::endl;
      }
    } else {
      std::cout << "Blade-SDK CPP Demo. Checkout README.md for examples:" << std::endl;
    }
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

ApiService::AccountData createAccountBlade()
{
  MnemonicBIP39 seedPhrase = getMnemonic();
  std::unique_ptr<ECDSAsecp256k1PrivateKey> privateKey = getPrivateKey(seedPhrase);
  std::shared_ptr<PublicKey> publicKey = privateKey->getPublicKey(); 

  json account = ApiService::createAccount(publicKey, apiHost, apiKey, fingerprint, dAppCode, network);

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
    .privateKey = privateKey->toString(),
    .accountId = account.value("id", ""),
  };
}

ApiService::AccountData createAccount(std::string operatorAccountId, std::string operatorPrivateKey)
{
  MnemonicBIP39 seedPhrase = getMnemonic();
  std::unique_ptr<ECDSAsecp256k1PrivateKey> privateKey = getPrivateKey(seedPhrase);
  std::shared_ptr<PublicKey> publicKey = privateKey->getPublicKey();
  
  client.setOperator(AccountId::fromString(operatorAccountId), ED25519PrivateKey::fromString(operatorPrivateKey));

  TransactionResponse txResp = AccountCreateTransaction()
      .setKey(publicKey)
      // .setInitialBalance(Hbar(1000ULL, HbarUnit::TINYBAR()))
      .execute(client);

  TransactionReceipt txReceipt = txResp.getReceipt(client);
  
  return {
    .seedPhrase = seedPhrase.toString(),
    .publicKey = publicKey->toString(),
    .privateKey = privateKey->toString(),
    .accountId = txReceipt.getAccountId().value().toString(),
  };
}

ApiService::AccountData importAccount(std::string seedPhrase) {
  std::string passphrase = "";
  MnemonicBIP39 mnemonic = MnemonicBIP39::initializeBIP39Mnemonic(seedPhrase);
  std::unique_ptr<ECDSAsecp256k1PrivateKey> privateKey = getPrivateKey(mnemonic);
  std::string accountId = ApiService::getAccountsFromPublicKey(privateKey->getPublicKey(), network);
  
  return {
    .seedPhrase = mnemonic.toString(),
    .publicKey = privateKey->getPublicKey()->toString(),
    .privateKey = privateKey->toString(),
    .accountId = accountId,
  };
}


std::vector<unsigned char> signMessage(std::string message, std::string signerKey) {
      std::cout << "Message: " << message << std::endl;
      std::cout << "signerKey: " << signerKey << std::endl;
      
      std::unique_ptr<ECDSAsecp256k1PrivateKey> privateKey = ECDSAsecp256k1PrivateKey::fromString(signerKey);

      std::vector<unsigned char> vec(message.begin(), message.end());

      std::cout << "Message data: ";
      printVec(vec);

      std::string hexString = vectorToHex(vec);
      std::cout << "Message data (hex): " << hexString << std::endl;
      // printVec(hexToVector(hexString));

      std::vector<unsigned char> signature = privateKey->sign(vec);

      std::cout << "Signature: ";
      printVec(signature);
      std::cout << "Signature (hex): " << vectorToHex(signature) << std::endl;


      // std::shared_ptr<PublicKey> publicKey = ecdsaSecp256k1PrivateKeyMy->getPublicKey();
      
      // std::cout << "Verify sig1: " << ecdsaSecp256k1PrivateKeyMy->getPublicKey()->verifySignature(signature1, vec)
      //           << std::endl;
      // std::cout << "Verify sig2: " << ecdsaFromString->getPublicKey()->verifySignature(signature2, vec)
      //           << std::endl;
      return signature;
}


bool verifyMessage(std::string message, std::string signatureHex, std::string key) {
  
      std::vector<unsigned char> signature = hexToVector(signatureHex);
      std::vector<unsigned char> vec(message.begin(), message.end());

      std::shared_ptr<ECDSAsecp256k1PublicKey> publicKey = ECDSAsecp256k1PublicKey::fromString(key);

      // std::cout << "message: " << message << std::endl;
      // std::cout << "signatureHex: " << signatureHex << std::endl;
      // std::cout << "publicKey: " << publicKey->toString() << std::endl;

      return publicKey->verifySignature(signature, vec);
}



MnemonicBIP39 getMnemonic() {
  // TODO implement https://github.com/Blade-Labs/blade-sdk.js/pull/9/files
  
  MnemonicBIP39 seedPhrase = MnemonicBIP39::generate12WordBIP39Mnemonic();
  return seedPhrase;
}

std::unique_ptr<ECDSAsecp256k1PrivateKey> getPrivateKey(MnemonicBIP39 mnemonic) {
  return ECDSAsecp256k1PrivateKey::fromSeed(mnemonic.toSeed())->derive(44)->derive(3030)->derive(0)->derive(0);
}

void printAccount(ApiService::AccountData accountData) {
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