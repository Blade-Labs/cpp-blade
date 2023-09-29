#ifndef BLADE_SERVICE_API_H_
#define BLADE_SERVICE_API_H_

#define BOOST_NETWORK_ENABLE_HTTPS

#include "ECDSAsecp256k1PrivateKey.h"
#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/beast/ssl.hpp>
#include <nlohmann/json.hpp>
#include "model/enums.h"

using namespace Hedera;

namespace BladeSDK {

    namespace beast = boost::beast;
    namespace http = beast::http;
    namespace net = boost::asio;
    namespace ssl = net::ssl;
    using json = nlohmann::json;

    class ApiService {
        private:
            std::string apiHost;
            std::string apiKey;
            Network network;
            std::string dAppCode;
            std::string visitorId;
            std::string sdkVersion;
            SdkEnvironment sdkEnvironment;

            std::string getPath(std::string path);
            std::string getMirrorNodeHost(Network network);
            std::vector<TokenBalance> getAccountTokens(std::string accountId);
            void registerDevice();
            json makeRequestGet(std::string apiHost, std::string path, struct Options options);
            json makeRequestPost(std::string apiHost, std::string path, std::string body, struct Options options);

        public:
            ApiService(const std::string& apiKey, const Network& network, const std::string& dAppCode, const SdkEnvironment& sdkEnvironment);
            void init(std::string sdkVersion, std::string visitorId);
            json createAccount(std::shared_ptr<PublicKey> publicKey);
            BladeTxResponse freeTokenTransfer(std::string accountId, std::string recieverAccount, long long correctedAmount, std::string memo);
            BladeTxResponse signContractCallTx(const std::vector<std::byte>& parameters, std::string contractId, std::string functionName, long long gas, bool contractCallQuery);
            json GET(std::string route);
            AccountBalanceData getBalance(std::string accountId);
            TransactionsHistoryData getTransactionsFrom(std::string accountId, std::string transactionType, std::string nextPage, int transactionsLimit);
            std::vector<std::string> getAccountsFromPublicKey(std::string publicKey);
            std::string getClientId();
    };
}

#endif // BLADE_SERVICE_API_H_