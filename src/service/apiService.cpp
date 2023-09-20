#include "../../include/service/apiService.h"

using namespace Hedera;
namespace BladeSDK {

    using tcp = boost::asio::ip::tcp;
    using json = nlohmann::json;
    namespace beast = boost::beast;
    namespace http = beast::http;
    namespace net = boost::asio;
    namespace ssl = boost::asio::ssl;


    ApiService::ApiService(const std::string& apiKey, const Network& network, const std::string& dAppCode, const SdkEnvironment& sdkEnvironment, const std::string& sdkVersion) {
        this->apiKey = apiKey;
        this->network = network;
        this->dAppCode = dAppCode;
        this->sdkEnvironment = sdkEnvironment;
        this->sdkVersion = sdkVersion;

        if (sdkEnvironment == SdkEnvironment::CI) {
            this->apiHost = "api.bld-dev.bladewallet.io";
        } else if (sdkEnvironment == SdkEnvironment::Prod) {
            this->apiHost = "rest.prod.bladewallet.io";
        }        
    }

    json ApiService::createAccount(std::shared_ptr<PublicKey> publicKey) {
        std::string tvte = SecurityService::getTvte(sdkVersion, apiKey);

        struct Options options = {
          .apiKey = apiKey, .visitorId = visitorId, .network = this->network, .dAppCode = dAppCode, .tvte = tvte
        };
        json body = {
          {"publicKey", publicKey->toStringDer()}
        };
        json result = makeRequestPost(apiHost, getPath("/accounts"), body.dump(), options);
        return result;
    }

    FreeTokenTransferResponse ApiService::freeTokenTransfer(std::string accountId, std::string recieverAccount, long long correctedAmount, std::string memo) {
        std::string tvte = SecurityService::getTvte(sdkVersion, apiKey);

        struct Options options = {
          .apiKey = apiKey, .visitorId = visitorId, .network = this->network, .dAppCode = dAppCode, .tvte = tvte
        };
        json body = {
          {"receiverAccountId", recieverAccount},
          {"senderAccountId", accountId},
          {"amount", correctedAmount},
          {"memo", memo},
        };

        json result = makeRequestPost(apiHost, getPath("/tokens/transfers"), body.dump(), options);
        
        std::string transactionBytes = result.value("transactionBytes", "");
        return {
          .transactionBytes = transactionBytes,
          .bytes = UtilService::base64ToVector(transactionBytes),
        };
    }

    void ApiService::setVisitorId(std::string visitorId) {
      this->visitorId = visitorId;
    }

    // Helper function to generate the HTTP request
    http::request<http::string_body> make_request(
        const std::string& host, 
        const std::string& target, 
        const std::string& body,
        struct Options options
    ) {
        http::request<http::string_body> req{ http::verb::post, target, 11 };
        req.set(http::field::host, host);
        req.set(http::field::user_agent, "CPP-Blade");
        req.set(http::field::content_type, "application/json");
        req.set("X-NETWORK", enumToString(options.network));
        req.set("X-VISITOR-ID", options.visitorId);
        req.set("X-DAPP-CODE", options.dAppCode);
        req.set("X-SDK-TVTE-API", options.tvte);
        // req.set(http::field::custom_header, "custom_value"); // Add custom header
        req.body() = body;
        req.prepare_payload();
        return req;
    }

    // Helper function to generate the HTTP request
    http::request<http::string_body> make_request_get(
        const std::string& host, 
        const std::string& target
    ) {
        http::request<http::string_body> req{ http::verb::get, target, 11 };
        req.set(http::field::host, host);
        req.set(http::field::user_agent, "CPP-Blade");
        req.set(http::field::content_type, "application/json");
        // req.body() = body;
        req.prepare_payload();
        return req;
    }


    json makeRequestPost(std::string apiHost, std::string path, std::string body, struct Options options) {
        try {
            net::io_context ioc;
            // Create the SSL context and configure it
            ssl::context ctx(ssl::context::sslv23_client);

            ctx.set_default_verify_paths();
            // ctx.set_verify_mode(boost::asio::ssl::verify_peer);

            // Create the SSL stream and connect to the server
            ssl::stream<tcp::socket> stream(ioc, ctx);
            tcp::resolver resolver(ioc);

            if (!SSL_set_tlsext_host_name(stream.native_handle(), apiHost.c_str())) {
                boost::system::error_code ec{static_cast<int>(::ERR_get_error()), net::error::get_ssl_category()};
                throw boost::system::system_error{ec};
            }
            auto results = resolver.resolve(apiHost, "https");
            net::connect(stream.next_layer(), results.begin(), results.end());
            stream.handshake(ssl::stream_base::client);

            // Make the HTTP request
            http::request<http::string_body> req = make_request(apiHost, path, body, options);
            http::write(stream, req);

            // Receive the HTTP response
            boost::beast::flat_buffer buffer;
            http::response<http::dynamic_body> res;
            http::read(stream, buffer, res);

            //std::cout << "HTTP response: " << res.result_int() << std::endl;
            //std::cout << "HTTP message: " << res << std::endl;

            if (res.result_int() != 200)
            {
              std::cout << "HTTP response: " << res.result_int() << std::endl;
              std::cout << "HTTP message: " << res << std::endl;
              throw;
            }

            json result = nlohmann::json::parse(boost::beast::buffers_to_string(res.body().data()));
            return result;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            throw e;
        }
    }


    json makeRequestGet(std::string apiHost, std::string path) {
        net::io_context ioc;
        ssl::context ctx(ssl::context::sslv23_client);
        ctx.set_default_verify_paths();

        // Create the SSL stream and connect to the server
        ssl::stream<tcp::socket> stream(ioc, ctx);
        tcp::resolver resolver(ioc);

        if (!SSL_set_tlsext_host_name(stream.native_handle(), apiHost.c_str())) {
            boost::system::error_code ec{static_cast<int>(::ERR_get_error()), net::error::get_ssl_category()};
            throw boost::system::system_error{ec};
        }

        auto results = resolver.resolve(apiHost, "https");
        net::connect(stream.next_layer(), results.begin(), results.end());

        stream.handshake(ssl::stream_base::client);

        // Make the HTTP request
        http::request<http::string_body> req = make_request_get(apiHost, path);
        http::write(stream, req);

        // Receive the HTTP response
        boost::beast::flat_buffer buffer;
        http::response<http::dynamic_body> res;
        http::read(stream, buffer, res);

        if (res.result_int() != 200)
        {
          std::cout << "HTTP response: " << res.result_int() << std::endl;
          std::cout << "HTTP message: " << res << std::endl;
          throw;
        }

        json result = nlohmann::json::parse(boost::beast::buffers_to_string(res.body().data()));
        return result;
    }



    json ApiService::GET(std::string route) {
      std::string apiHost = getMirrorNodeHost(network);
      // std::cout << getMirrorNodeHost(network) << route << std::endl;
      return makeRequestGet(getMirrorNodeHost(network), route);
    }

    AccountBalanceData ApiService::getBalance(std::string accountId) {
      json accountData = GET("/api/v1/accounts/" + accountId);  
      long long balance = accountData["balance"]["balance"].get<long long>();
      std::vector<TokenBalance> tokens = getAccountTokens(accountId);            
      AccountBalanceData accountBalance(balance, tokens);
      return accountBalance;
    }

    std::vector<TokenBalance> ApiService::getAccountTokens(std::string accountId) {
      std::vector<TokenBalance> result = {};
      std::string nextPage = "/api/v1/accounts/" + accountId + "/tokens?limit=2";
  
      while (nextPage != "") {
        json response = GET(nextPage);

        if (response.contains("tokens") && response["tokens"].is_array()) {
            // Iterate over the "tokens" array
            for (const auto& record : response["tokens"]) {
              std::string token_id = record["token_id"].get<std::string>();
              long long balance = record["balance"].get<long long>();
            
              TokenBalance token(token_id, balance);
              result.push_back(token);
            }
        } else {
            std::cout << "\"tokens\" not found or not an array." << std::endl;
        }

        if (!response["links"]["next"].is_null()) {
            nextPage = response["links"].value("next", "");
        } else {
            nextPage = "";
        }
      }
      return result;
    }
    

    std::string ApiService::getFingerprintApiKey() {    
      // TODO use in future

      json resoponse = makeRequestGet(apiHost, this->getPath("/sdk/config"));
      return resoponse.value("fpAp11iKey", "default api keys fallabck");
    }

    std::vector<std::string> ApiService::getAccountsFromPublicKey(std::string publicKey) {
      std::vector<std::string> result = {};
      json resoponse = GET("/api/v1/accounts?account.publickey=" + publicKey);
      for (int i = 0; i < resoponse["accounts"].size(); i++) {
        result.push_back(resoponse["accounts"][i].value("account", ""));
      }
      return result;
    }


    std::string ApiService::getPath(std::string path) {
      return "/openapi/v7" + path;
    }

    std::string ApiService::getMirrorNodeHost(Network network) {
      if (network == Network::Testnet) {
        return "testnet.mirrornode.hedera.com";
      } else if (network == Network::Mainnet) {
        return "mainnet-public.mirrornode.hedera.com";
      }
      return "";
    }

}