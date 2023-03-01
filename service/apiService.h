#define BOOST_NETWORK_ENABLE_HTTPS

#include "ECDSAsecp256k1PrivateKey.h"
#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/beast/ssl.hpp>
#include <nlohmann/json.hpp>
#include "apiService.cpp"

namespace ApiService
{
//     struct Options;
//     struct AccountData;
    
    json createAccount(
        std::shared_ptr<PublicKey> publicKey,
        std::string apiHost,
        std::string apiKey,
        std::string fingerprint,
        std::string dAppCode,
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

