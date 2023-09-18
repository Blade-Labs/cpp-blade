#ifndef BLADE_SERVICE_API_H_
#define BLADE_SERVICE_API_H_

#define BOOST_NETWORK_ENABLE_HTTPS

#include "ECDSAsecp256k1PrivateKey.h"
#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/beast/ssl.hpp>
#include <nlohmann/json.hpp>
#include "enum/Enums.h"

using namespace Hedera;

namespace BladeSDK {

    namespace beast = boost::beast;
    namespace http = beast::http;
    namespace net = boost::asio;
    namespace ssl = net::ssl;
    using json = nlohmann::json;
    

    class ApiService {
        private:
            std::string apiHost = "api.bld-dev.bladewallet.io";
            std::string apiKey = "";
            Network network;
            std::string dAppCode = "";
            std::string visitorId = "";
            std::string sdkVersion = "";
            SdkEnvironment sdkEnvironment;

            std::string getPath(std::string path);
            std::string getMirrorNodeHost(Network network);
            std::vector<TokenBalance> getAccountTokens(std::string accountId);

        public:
            ApiService(const std::string& apiKey, const Network& network, const std::string& dAppCode, const SdkEnvironment& sdkEnvironment, const std::string& sdkVersion);
            void setVisitorId(std::string visitorId);
            json createAccount(std::shared_ptr<PublicKey> publicKey);
            json GET(std::string route);
            AccountBalanceData getBalance(std::string accountId);
            std::vector<std::string> getAccountsFromPublicKey(std::string publicKey);
            std::string getFingerprintApiKey();
    };
    

    void performHttpsGetRequest(const std::string& host, const std::string& target);

    std::string getAccountsFromPublicKey(
        std::shared_ptr<PublicKey> publicKey,
        std::string network
    );

    json makeRequestPost(
        std::string apiHost,
        std::string path,
        std::string body,
        struct Options options
    );

    // Helper function to generate the HTTP request
    http::request<http::string_body> make_request(
        const std::string& host, 
        const std::string& target, 
        const std::string& body,
        struct Options options
    );

}

#endif // BLADE_SERVICE_API_H_