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
#include "service/apiService.h"
#include "service/accountService.h"

using namespace Hedera;
using json = nlohmann::json;

void init(std::string apiKey_, std::string network_, std::string dAppCode_, std::string fingerprint_);
ApiService::AccountData createAccountBlade();
ApiService::AccountData createAccount(std::string operatorAccountId, std::string operatorPrivateKey);
MnemonicBIP39 getMnemonic();
std::unique_ptr<ECDSAsecp256k1PrivateKey> getPrivateKey(MnemonicBIP39);
void printAccount(ApiService::AccountData);
void printVec(std::vector<unsigned char> vec);
std::string vectorToHex(const std::vector<unsigned char>& data);
std::vector<unsigned char> hexToVector(const std::string& hexString);
ApiService::AccountData importAccount(std::string);
std::vector<unsigned char> signMessage(std::string message, std::string signerKey);
bool verifyMessage(std::string message, std::string signatureHex, std::string key);
int main(int argc, char** argv);
