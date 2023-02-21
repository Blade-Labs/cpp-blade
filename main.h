#include "ECDSAsecp256k1PrivateKey.h"
#include "ED25519PrivateKey.h"
#include "MnemonicBIP39.h"
#include "Client.h"

#include <iostream>
#include <string>
#include <nlohmann/json.hpp>
#include "service/apiService.h"
#include "service/accountService.h"

using namespace Hedera;
using json = nlohmann::json;

void init(std::string apiKey_, std::string network_, std::string dAppCode_, std::string fingerprint_);
ApiService::AccountData createAccount();
int main(int argc, char** argv);
