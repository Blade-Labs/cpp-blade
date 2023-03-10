#include "../../include/service/apiService.h"

using namespace Hedera;
namespace BladeSDK {
namespace ApiService {
    
    namespace net = boost::asio;
    using tcp = boost::asio::ip::tcp;
    namespace http = boost::beast::http;
    using json = nlohmann::json;

    std::string apiHost = "rest.prod.bladewallet.io";
    std::string apiPath = "/openapi/v7";


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
        req.set("X-SDK-TOKEN", options.apiKey);
        req.set("X-FINGERPRINT", options.fingerprint);
        req.set("X-NETWORK", options.network);
        req.set("X-DAPP-CODE", options.dAppCode);
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


    json makeRequestPost(std::string apiHost, std::string path, std::string body, struct Options options)
        {
        net::io_context ioc;

        // Create the SSL context and configure it
        boost::asio::ssl::context ctx(boost::asio::ssl::context::sslv23);
        ctx.set_default_verify_paths();
        ctx.set_verify_mode(boost::asio::ssl::verify_peer);

        // Create the SSL stream and connect to the server
        boost::asio::ssl::stream<tcp::socket> stream(ioc, ctx);
        tcp::resolver resolver(ioc);

        auto const results = resolver.resolve(apiHost, "443");

        net::connect(stream.next_layer(), results.begin(), results.end());
        stream.handshake(boost::asio::ssl::stream_base::client);


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



        //  json account = json::parse(res);
        json result = nlohmann::json::parse(boost::beast::buffers_to_string(res.body().data()));
        // json result = nlohmann::json::parse("{}");

        //std::cout << result.dump(4) << std::endl;


        return result;
        //return boost::beast::buffers_to_string(res.body().data());
    }


    json makeRequestGet(std::string apiHost, std::string path)
        {
        net::io_context ioc;

        // Create the SSL context and configure it
        boost::asio::ssl::context ctx(boost::asio::ssl::context::sslv23);
        ctx.set_default_verify_paths();
        ctx.set_verify_mode(boost::asio::ssl::verify_peer);

        // Create the SSL stream and connect to the server
        boost::asio::ssl::stream<tcp::socket> stream(ioc, ctx);
        tcp::resolver resolver(ioc);

        auto const results = resolver.resolve(apiHost, "443");

        net::connect(stream.next_layer(), results.begin(), results.end());
        stream.handshake(boost::asio::ssl::stream_base::client);


        // Make the HTTP request
        http::request<http::string_body> req = make_request_get(apiHost, path);
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

        // std::cout << result.dump(4) << std::endl;

        return result;
    }

    json createAccount(std::shared_ptr<PublicKey> publicKey,
                      std::string apiHost,
                      std::string apiKey,
                      std::string fingerprint,
                      std::string dAppCode,
                      std::string network)
    {
        struct Options options = {
          .apiKey = apiKey, .fingerprint = fingerprint, .network = network, .dAppCode = dAppCode 
        };
        json body = {
          {"publicKey", "302d300706052b8104000a032200" + publicKey->toString()}
        };
        json result = makeRequestPost(apiHost, apiPath + "/accounts", body.dump(), options);

        //std::cout << "ApiService::JSON RAW: " << result.dump(10) << std::endl;

        return result;
    }

    std::string getAccountsFromPublicKey(std::shared_ptr<PublicKey> publicKey, std::string network) {
      std::string apiHost;
      if (network == "TESTNET") {
        apiHost = "testnet.mirrornode.hedera.com";
      } else if (network == "MAINNET") {
        apiHost = "mainnet-public.mirrornode.hedera.com";
      }

      std::string apiPath = "/api/v1/accounts?account.publickey=" + publicKey->toString();
      json resoponse = makeRequestGet(apiHost, apiPath);
          

      // TODO add support of multiple accounts id
      nlohmann::json accounts = resoponse["accounts"];

      for (int i = 0; i < accounts.size(); i++) {
        return accounts[i].value("account", "");
      }
      return "";
    }
}}