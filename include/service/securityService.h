#ifndef BLADE_SERVICE_SECURITY_H_
#define BLADE_SERVICE_SECURITY_H_

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <ctime>
#include <openssl/aes.h>
#include <openssl/rand.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/sha.h>
#include <openssl/hmac.h>
#include <openssl/err.h>
#include <boost/beast/core/detail/base64.hpp>

namespace BladeSDK {
namespace SecurityService {
	std::string encrypt(const std::string& data, const std::string& token);
    std::string getTvte(const std::string& sdkVersion, const std::string& token);
    std::string getVte(const std::string& visitorId, const std::string& token);
    std::string generateRandomString(int length);
}}

#endif // BLADE_SERVICE_SECURITY_H_