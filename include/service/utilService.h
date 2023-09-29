#ifndef BLADE_SERVICE_UTIL_H_
#define BLADE_SERVICE_UTIL_H_

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <ctime>
#include <stdexcept>
#include "TransactionReceipt.h"
#include <boost/beast/core/detail/base64.hpp>

using namespace Hedera;

namespace BladeSDK {
namespace UtilService {
    std::string stringToBase64(std::string binaryData);
    std::string base64ToString(const std::string& base64Data);
    std::vector<std::byte> base64ToVector(std::string encoded);
    std::string vectorToBase64(const std::vector<std::byte>& input);
    std::string vectorToHex(const std::vector<std::byte>& data);
    std::vector<std::byte> hexToVector(const std::string& hexString);
    std::vector<std::byte> stringToVector(const std::string& str);
    TxReceipt formatReceipt(TransactionReceipt receipt);
    std::tuple<int, int, int> splitIdToIntTuple(const std::string& input);
    std::string toUpperCase(const std::string& str);
    bool isUUID(const std::string& str);
    std::vector<TransactionData> formatTransactionData(nlohmann::json transactionsHistory, std::string accountId);
    std::vector<TransactionData> filterAndFormatTransactions(std::vector<TransactionData> transactions, std::string transactionType);
    template <typename T> std::vector<T> slice(const std::vector<T>& input, std::size_t start, std::size_t end);
    std::vector<std::string> splitString(const std::string& input, char delimiter);
}}

#endif // BLADE_SERVICE_UTIL_H_