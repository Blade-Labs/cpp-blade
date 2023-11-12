#include "../../include/service/utilService.h"
#include "TransactionReceipt.h"
#include <regex>

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

    std::string base64ToString(const std::string& base64Data) {
        // Convert base64-encoded string to a vector of bytes
        std::vector<std::byte> binaryData = base64ToVector(base64Data);

        // Create a string from the vector of bytes
        std::string result(reinterpret_cast<const char*>(binaryData.data()), binaryData.size());

        return result;
    }

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

    std::string toUpperCase(const std::string& str) {
        std::string result = str;
        std::transform(result.begin(), result.end(), result.begin(), ::toupper);
        return result;
    }

    bool isUUID(const std::string& str) {
        // Regular expression for a UUID pattern
        std::regex uuidPattern("^[0-9a-fA-F]{8}-[0-9a-fA-F]{4}-[0-9a-fA-F]{4}-[0-9a-fA-F]{4}-[0-9a-fA-F]{12}$");

        // Use std::regex_match to check if the string matches the pattern
        return std::regex_match(str, uuidPattern);
    }


    std::vector<TransactionData> formatTransactionData(json transactionsHistory, std::string accountId) {
        std::vector<TransactionData> result = {};

        if (transactionsHistory.contains("transactions") && transactionsHistory["transactions"].is_array()) {
            for (const auto& record : transactionsHistory["transactions"]) {

                std::vector<TransferData> transfers = {};
                std::vector<TransactionHistoryNftTransfer> nftTransfers;

                if (record.contains("transfers") && record["transfers"].is_array()) {
                    for (const auto& transfer : record["transfers"]) {
                        TransferData transferData = TransferData {
                            .amount = transfer["amount"].get<long long>(),
                            .account = transfer["account"].get<std::string>(),
                        };
                        transfers.push_back(transferData);
                    }
                }

                if (record.contains("token_transfers") && record["token_transfers"].is_array()) {
                    for (const auto& transfer : record["token_transfers"]) {
                        TransferData transferData = TransferData {
                            .amount = transfer["amount"].get<long long>(),
                            .account = transfer["account"].get<std::string>(),
                            .token_id = transfer["token_id"].get<std::string>()
                        };
                        transfers.push_back(transferData);
                    }
                }

                if (record.contains("nftTransfers") && record["nftTransfers"].is_array()) {
                    for (const auto& transfer : record["nftTransfers"]) {
                        TransactionHistoryNftTransfer transferData = TransactionHistoryNftTransfer {
                            .receiver_account_id = transfer["receiver_account_id"].get<std::string>(),
                            .sender_account_id = transfer["sender_account_id"].get<std::string>(),
                            .serial_number = transfer["serial_number"].get<uint>(),
                            .token_id = transfer["token_id"].get<std::string>(),
                        };
                        nftTransfers.push_back(transferData);
                    }
                }

                TransactionData transaction = TransactionData {
                    .transactionId = record["transaction_id"].get<std::string>(),
                    .type = record["name"].get<std::string>(),
                    .transfers = transfers,
                    .nftTransfers  = nftTransfers,
                    .memo = base64ToString(record["memo_base64"].get<std::string>()),
                    .fee = record["charged_tx_fee"].get<long long>(),
                    .showDetailed = false,
                    .consensusTimestamp = record["consensus_timestamp"].get<std::string>()
                };
                result.push_back(transaction);
                
            }
        } else {
            std::cout << "\"transactions\" not found or not an array." << std::endl;
        }
        return result;
    }

    std::vector<TransactionData> filterAndFormatTransactions(std::vector<TransactionData> transactions, std::string transactionType) {
        if (transactionType == "") {
            return transactions;
        }

        std::vector<TransactionData> result = {};
        for (const auto& tx : transactions) {
            if (tx.type == transactionType) {
                result.push_back(tx);
            }
        }

        return result;
    }

    template <typename T>
    std::vector<T> slice(const std::vector<T>& input, std::size_t start, std::size_t end) {
        if (start >= input.size()) {
            return std::vector<T>(); // Return an empty vector if start is out of range
        }

        if (end > input.size()) {
            end = input.size(); // Adjust end to avoid going out of range
        }

        return std::vector<T>(input.begin() + start, input.begin() + end);
    }

    std::vector<std::string> splitString(const std::string& input, char delimiter) {
        std::vector<std::string> parts;
        std::string part;

        for (char c : input) {
            if (c == delimiter) {
                parts.push_back(part);
                part.clear();
            } else {
                part += c;
            }
        }
        parts.push_back(part);
        return parts;
    }


}}
