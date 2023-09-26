#ifndef BLADE_SERVICE_UTIL_H_
#define BLADE_SERVICE_UTIL_H_

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <ctime>
#include "TransactionReceipt.h"
#include <boost/beast/core/detail/base64.hpp>

using namespace Hedera;

namespace BladeSDK {
namespace UtilService {
    std::string stringToBase64(std::string binaryData);
    std::vector<std::byte> base64ToVector(std::string encoded);
    std::string vectorToBase64(const std::vector<std::byte>& input);
    std::string vectorToHex(const std::vector<std::byte>& data);
    std::vector<std::byte> hexToVector(const std::string& hexString);
    std::vector<std::byte> stringToVector(const std::string& str);
    TxReceipt formatReceipt(TransactionReceipt receipt);
    std::tuple<int, int, int> splitIdToIntTuple(const std::string& input);
    std::string toUpperCase(const std::string& str);
    bool isUUID(const std::string& str);
}}

#endif // BLADE_SERVICE_UTIL_H_