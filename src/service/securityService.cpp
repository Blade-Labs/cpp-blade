#include "../../include/service/securityService.h"

using namespace Hedera;

namespace BladeSDK {
namespace SecurityService {
	
    const int CIPHER_IV_LENGTH = 12;
    const int CIPHER_KEY_LENGTH = 32;
    const int MAGIC_IV_INDEX = 3;

    std::string getTvte(const std::string& sdkVersion, const std::string& token) {
        std::vector<std::string> parts = UtilService::splitString(sdkVersion, '@');
        if (parts.size() != 2) {
            std::cerr << "Invalid sdkVersion: " << sdkVersion << std::endl;
            return "";
        }

        std::string platform = parts[0];
        std::string version = parts[1];
        std::time_t timestamp = std::time(nullptr);
        return platform + "@" + encrypt(version + "@" + std::to_string(timestamp * 1000), token);
    }

    std::string getVte(const std::string& visitorId, const std::string& token) {
        std::time_t timestamp = std::time(nullptr);
        return encrypt(visitorId + "@" + std::to_string(timestamp * 1000), token);
    }
    
    std::string encrypt(const std::string& data, const std::string& token) {
        std::string ivStr = generateRandomString(CIPHER_IV_LENGTH);
        std::vector<unsigned char> iv(ivStr.begin(), ivStr.end());

        int tokenIdx = iv[MAGIC_IV_INDEX];
        std::vector<unsigned char> rawKey(CIPHER_KEY_LENGTH, 0);
        for (int i = 0; i < CIPHER_KEY_LENGTH; i++) {
            rawKey[i] = token[(i + tokenIdx) % token.length()];
        }

        EVP_CIPHER_CTX *ctx;
        ctx = EVP_CIPHER_CTX_new();

        if (EVP_EncryptInit_ex(ctx, EVP_aes_256_gcm(), NULL, &rawKey[0], &iv[0]) != 1) {
            std::cerr << "EVP_EncryptInit_ex failed" << std::endl;
            EVP_CIPHER_CTX_free(ctx);
            return "";
        }

        std::vector<unsigned char> encoded(data.begin(), data.end());
        std::vector<unsigned char> cipher(encoded.size() + AES_BLOCK_SIZE);
        int len;

        if (EVP_EncryptUpdate(ctx, &cipher[0], &len, &encoded[0], encoded.size()) != 1) {
            std::cerr << "EVP_EncryptUpdate failed" << std::endl;
            EVP_CIPHER_CTX_free(ctx);
            return "";
        }

        int ciphertext_len = len;

        if (EVP_EncryptFinal_ex(ctx, &cipher[len], &len) != 1) {
            std::cerr << "EVP_EncryptFinal_ex failed" << std::endl;
            EVP_CIPHER_CTX_free(ctx);
            return "";
        }

        ciphertext_len += len;

        // Get the authentication tag
        unsigned char tag[AES_BLOCK_SIZE];
        if (EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_GET_TAG, AES_BLOCK_SIZE, tag) != 1) {
            std::cerr << "EVP_CIPHER_CTX_ctrl failed" << std::endl;
            EVP_CIPHER_CTX_free(ctx);
            return "";
        }

        EVP_CIPHER_CTX_free(ctx);
        
        std::string result(ivStr);
        result.append(cipher.begin(), cipher.begin() + ciphertext_len);
        result.append(tag, tag + AES_BLOCK_SIZE);

        return UtilService::stringToBase64(result);
    }

    std::string generateRandomString(int length) {
        static const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<> dist(0, sizeof(charset) - 2);

        std::string result(length, '\0');
        for (int i = 0; i < length; ++i) {
            result[i] = charset[dist(gen)];
        }
        return result;
    }

}}
