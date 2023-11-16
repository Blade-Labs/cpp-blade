#include "ECDSAsecp256k1PrivateKey.h"
#include "ECDSAsecp256k1PublicKey.h"
#include "ED25519PrivateKey.h"
#include "PrivateKey.h"
#include "MnemonicBIP39.h"
#include "Client.h"
#include "AccountCreateTransaction.h"
#include "TransferTransaction.h"
#include "TransactionReceipt.h"
#include "TransactionResponse.h"
#include "ContractCallQuery.h"
#include "ContractFunctionResult.h"

#include <iostream>
#include <string>
#include <nlohmann/json.hpp>
#include "model/enums.h"
#include "model/types.h"
#include "service/utilService.h"
#include "service/apiService.h"
#include "service/accountService.h"
#include "service/securityService.h"
#include "service/fingerprintService.h"

using namespace Hedera;
using json = nlohmann::json;

namespace BladeSDK {

    class Blade {
        private:
            ApiService apiService;
            std::string apiKey;
            Network network;
            std::string dAppCode;
            std::string visitorId;
            std::string sdkVersion = "Cpp@0.6.4";
            SdkEnvironment sdkEnvironment;
            
            Client getClient();
            MnemonicBIP39 getMnemonic();
            std::shared_ptr<PrivateKey> getPrivateKey(MnemonicBIP39);

        public:
            Blade(const std::string& apiKey, const Network& network, const std::string& dAppCode, const SdkEnvironment& sdkEnvironment);
            InfoData getInfo();
            AccountData createAccount();
            AccountInfoData getAccountInfo(std::string accountId);
            AccountBalanceData getBalance(std::string accountId);
            PrivateKeyData importAccount(std::string seedPhrase, bool lookupAccounts);
            TxReceipt transferHbars(std::string accountId, std::string accountPrivateKey, std::string recieverAccount, std::string amount, std::string memo);
            TxReceipt transferTokens(std::string tokenId, std::string accountId, std::string accountPrivateKey, std::string receiverId, std::string amount, std::string memo, bool freeTransfer);
            SignMessageData sign(std::string message, std::string signerKey, std::string encoding);
            bool signVerify(std::string message, std::string signatureHex, std::string key, std::string encoding);
            TxReceipt contractCallFunction(std::string contractId, std::string functionName, ContractFunctionParameters parameters, std::string accountId, std::string accountPrivateKey, long long gas, bool bladePayFee);
            ContractFunctionResult contractCallQueryFunction(std::string contractId, std::string functionName, ContractFunctionParameters parameters, std::string accountId, std::string accountPrivateKey, long long gas, double maxQueryPayment, std::vector<std::string> returnTypes);
            TxReceipt deleteAccount(std::string deleteAccountId, std::string deletePrivateKey, std::string transferAccountId, std::string operatorAccountId, std::string operatorPrivateKey);
            std::string getC14url(std::string asset, std::string account, std::string amount);
            TransactionsHistoryData getTransactions(std::string accountId, std::string transactionType, std::string nextPage, int transactionsLimit);

            
    };

    std::ostream& operator<<(std::ostream& os,  Blade& blade);

    // int main(int argc, char** argv);
}
