#ifndef BLADE_SERVICE_SECURITY_H_
#define BLADE_SERVICE_SECURITY_H_

#include <iostream>
#include <string>
#include <vector>
#include <random>
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
    std::string generateRandomString(int length);
    std::string base64Encode(std::string binaryData);
}}

#endif // BLADE_SERVICE_SECURITY_H_