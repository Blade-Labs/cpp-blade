#include "../../include/service/utilService.h"
#include "TransactionReceipt.h"

using namespace Hedera;

namespace BladeSDK {
namespace UtilService {
    std::string stringToBase64(std::string binaryData) {
        std::vector<char> encodedBuffer(boost::beast::detail::base64::encoded_size(binaryData.size()));

        boost::beast::detail::base64::encode(
            encodedBuffer.data(),
            binaryData.data(),
            binaryData.size()
        );

        std::string encodedData(encodedBuffer.begin(), encodedBuffer.end());
        return encodedData;
    }

    // todo base64ToString

    std::vector<std::byte> base64ToVector(std::string encoded) {
        std::string decoded;

        decoded.resize(boost::beast::detail::base64::decoded_size(encoded.size()));
        std::pair<std::size_t, std::size_t> decodedInfo = boost::beast::detail::base64::decode(&decoded[0], encoded.data(), encoded.size());
        
        std::vector<std::byte> output(decodedInfo.first);
        for (std::size_t i = 0; i < decodedInfo.first; i++) {
            output[i] = static_cast<std::byte>(decoded[i]);
        }
        
        return output;
    }

    std::string vectorToBase64(const std::vector<std::byte>& input) {
        std::string inputString;
        inputString.resize(input.size());

        for (std::size_t i = 0; i < input.size(); i++) {
            inputString[i] = static_cast<char>(input[i]);
        }
        std::string encoded;
        encoded.resize(boost::beast::detail::base64::encoded_size(inputString.size()));

        std::size_t encodedSize = boost::beast::detail::base64::encode(&encoded[0], inputString.c_str(), inputString.size());
        encoded.resize(encodedSize);
        return encoded;
    }

    std::string vectorToHex(const std::vector<std::byte>& data) {
        std::ostringstream oss;
        oss << std::hex << std::setfill('0');
        for (auto byte : data) {
            oss << std::setw(2) << static_cast<int>(byte);
        }
        return oss.str();
    }


    std::vector<std::byte> hexToVector(const std::string& hexString) {
        std::vector<std::byte> result;
        result.reserve(hexString.size() / 2);
        for (std::string::size_type i = 0; i < hexString.size(); i += 2) {
            unsigned int byteValue;
            std::stringstream ss;
            ss << std::hex << hexString.substr(i, 2);
            ss >> byteValue;
            result.push_back(static_cast<std::byte>(byteValue));
        }
        return result;
    }

    std::vector<std::byte> stringToVector(const std::string& str) {
        std::vector<std::byte> byteVector;
        for (char c : str) {
            byteVector.push_back(static_cast<std::byte>(c));
        }
        return byteVector;
    }

    TxReceipt formatReceipt(TransactionReceipt receipt) {
        // std::cout << receipt.mTransactionId.toString() << std::endl;
 
        return {
            .transactionId = receipt.mTransactionId.toString(),
            .status = std::string(gStatusToString.at(receipt.mStatus)),
            .transactionReceipt = receipt
        };
    }


    std::tuple<int, int, int> splitIdToIntTuple(const std::string& input) {
    int part1 = 0, part2 = 0, part3 = 0;

    size_t firstDot = input.find('.');
    if (firstDot != std::string::npos) {
        part1 = std::stoi(input.substr(0, firstDot));

        size_t secondDot = input.find('.', firstDot + 1);
        if (secondDot != std::string::npos) {
            part2 = std::stoi(input.substr(firstDot + 1, secondDot - firstDot - 1));
            part3 = std::stoi(input.substr(secondDot + 1));
        } else {
            part2 = std::stoi(input.substr(firstDot + 1));
        }
    } else {
        part1 = std::stoi(input);
    }

    return std::make_tuple(part1, part2, part3);
}

}}
