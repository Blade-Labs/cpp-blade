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
#include "enum/Enums.h"
#include "types.h"
#include "service/apiService.h"
#include "service/accountService.h"
#include "service/securityService.h"

using namespace Hedera;
using json = nlohmann::json;

namespace BladeSDK {

    class Blade {
        private:
            ApiService apiService;
            std::string apiKey = "Rww3x27z3Q9rrIvRQ6qGgIRppxz5e5HHPWdARyxnMXpe77WD5MW39REBXXvRZsZE";
            Network network = Network::Testnet;
            std::string dAppCode = "unitysdktest";
            std::string visitorId = "BC238E19-6B3D-5CFC-A26A-21499FF7C25E";
            std::string sdkVersion = "Unity@0.6.4";
            SdkEnvironment sdkEnvironment = SdkEnvironment::CI; // "CI";
            
            Client getClient();
            MnemonicBIP39 getMnemonic();
            std::unique_ptr<PrivateKey> getPrivateKey(MnemonicBIP39);

        public:
            Blade(const std::string& apiKey, const Network& network, const std::string& dAppCode, const SdkEnvironment& sdkEnvironment);
            AccountData createAccountBlade();
            AccountInfoData getAccountInfo(std::string accountId);
            AccountBalanceData getBalance(std::string accountId);
            PrivateKeyData importAccount(std::string seedPhrase, bool lookupAccounts);
            TransactionReceipt transferHbars(std::string accountId, std::string accountPrivateKey, std::string recieverAccount, std::string amount, std::string memo);
            TransactionReceipt transferTokens(std::string tokenId, std::string accountId, std::string accountPrivateKey, std::string receiverId, std::string amount, std::string memo, bool freeTransfer);



    };



    int main(int argc, char** argv);
    
    // AccountData createAccount(std::string operatorAccountId, std::string operatorPrivateKey);
    // AccountData importAccount(std::string);
    // std::vector<unsigned char> signMessage(std::string message, std::string signerKey);
    // bool verifyMessage(std::string message, std::string signatureHex, std::string key);
    // void transferHbars(std::string accountId, std::string accountPrivateKey, std::string receiverID, double amount);
    // void transferTokens(std::string tokenId, std::string accountId, std::string accountPrivateKey, std::string receiverID, double amount, bool freeTransfer);

    // std::string getFingerprintApiKey();

    
    
    void printAccount(AccountData);
    void printVec(std::vector<unsigned char> vec);
    // std::string vectorToHex(const std::vector<unsigned char>& data);
    std::string vectorToHex(const std::vector<std::byte>& data);

    std::vector<unsigned char> hexToVector(const std::string& hexString);
    
    
}
