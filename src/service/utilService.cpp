#include "../../include/service/utilService.h"

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
    
}}
