#include "ECDSAsecp256k1PrivateKey.h"
#include "ED25519PrivateKey.h"
#include "MnemonicBIP39.h"
#include "Client.h"
#include "AccountCreateTransaction.h"
#include "TransactionReceipt.h"
#include "TransactionResponse.h"

#include <iostream>
#include <string>
#include <nlohmann/json.hpp>
#include "types.h"
#include "service/apiService.h"
#include "service/accountService.h"

using namespace Hedera;
using json = nlohmann::json;

namespace BladeSDK {
    int main(int argc, char** argv);
    void init(std::string apiKey_, std::string network_, std::string dAppCode_, std::string fingerprint_);
    AccountData createAccountBlade();
    AccountData createAccount(std::string operatorAccountId, std::string operatorPrivateKey);
    AccountData importAccount(std::string);
    std::vector<unsigned char> signMessage(std::string message, std::string signerKey);
    bool verifyMessage(std::string message, std::string signatureHex, std::string key);
    void transferHbars(std::string accountId, std::string accountPrivateKey, std::string receiverID, double amount);
    void transferTokens(std::string tokenId, std::string accountId, std::string accountPrivateKey, std::string receiverID, double amount, bool freeTransfer);

    MnemonicBIP39 getMnemonic();
    std::unique_ptr<ECDSAsecp256k1PrivateKey> getPrivateKey(MnemonicBIP39);
    void printAccount(AccountData);
    void printVec(std::vector<unsigned char> vec);
    std::string vectorToHex(const std::vector<unsigned char>& data);
    std::vector<unsigned char> hexToVector(const std::string& hexString);
    
    
}
