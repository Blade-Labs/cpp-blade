#include "../../include/service/apiService.h"

using namespace Hedera;
namespace BladeSDK {
namespace ApiService {
    using tcp = boost::asio::ip::tcp;
    using json = nlohmann::json;
    namespace beast = boost::beast;
    namespace http = beast::http;
    namespace net = boost::asio;
    namespace ssl = boost::asio::ssl;

    std::string apiHost = "api.bld-dev.bladewallet.io";
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
        req.set("X-NETWORK", options.network);
        req.set("X-VISITOR-ID", options.fingerprint);
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

    json createAccount(std::shared_ptr<PublicKey> publicKey,
                      std::string apiHost,
                      std::string apiKey,
                      std::string fingerprint,
                      std::string dAppCode,
                      std::string network,
                      std::string tvte)
    {
        struct Options options = {
          .apiKey = apiKey, .fingerprint = fingerprint, .network = network, .dAppCode = dAppCode, .tvte = tvte
        };
        json body = {
          {"publicKey", publicKey->toStringDer()}
        };
        json result = makeRequestPost(apiHost, apiPath + "/accounts", body.dump(), options);

        //std::cout << "ApiService::JSON RAW: " << result.dump(10) << std::endl;

        return result;
    }

    std::string getFingerprintApiKey() {
      std::cout << apiHost << apiPath + "/sdk/config" << std::endl;


      json resoponse = makeRequestGet("api.bld-dev.bladewallet.io", "/openapi/v7/sdk/config");
      return resoponse.value("fpAp11iKey", "default api keys fallabck");
    }

    std::string getAccountsFromPublicKey(std::shared_ptr<PublicKey> publicKey, std::string network) {
      std::string apiHost;
      if (network == "TESTNET") {
        apiHost = "testnet.mirrornode.hedera.com";
      } else if (network == "MAINNET") {
        apiHost = "mainnet-public.mirrornode.hedera.com";
      }

      std::string apiPath = "/api/v1/accounts?account.publickey=" + publicKey->toStringDer();
      json resoponse = makeRequestGet(apiHost, apiPath);
          

      // TODO add support of multiple accounts id
      nlohmann::json accounts = resoponse["accounts"];

      for (int i = 0; i < accounts.size(); i++) {
        return accounts[i].value("account", "");
      }
      return "";
    }
}}