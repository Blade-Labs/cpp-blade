#ifndef BLADE_TYPES_H_
#define BLADE_TYPES_H_

#include "TransactionReceipt.h"

using namespace Hedera;

namespace BladeSDK {
    template <typename T>
    std::string printItems(const std::vector<T> items);

    struct AccountData {
      std::string seedPhrase;
      std::string publicKey;
      std::string privateKey;
      std::string accountId;
    };

    std::ostream& operator<<(std::ostream& os, const AccountData& account);


    struct Options {
      std::string apiKey;
      std::string visitorId;
      Network network;
      std::string dAppCode;
      std::string tvte;
    };

    std::ostream& operator<<(std::ostream& os, const Options& options);


    struct AccountInfoData {
        std::string accountId;
        std::string evmAddress;
        std::string publicKey;
    };

    std::ostream& operator<<(std::ostream& os, const AccountInfoData& data);


    struct TokenBalance {
        std::string token_id;
        unsigned long long balance; // Use 'unsigned long long' to match C#'s ulong

        TokenBalance(const std::string& tokenId, unsigned long long bal)
            : token_id(tokenId), balance(bal) {}
    };

    std::ostream& operator<<(std::ostream& os, const TokenBalance& data);


    struct AccountBalanceData {
        long long balance; // Use 'long long' to match C#'s long
        std::vector<TokenBalance> tokens;

        // Constructor for AccountBalanceData
        AccountBalanceData(long long bal, const std::vector<TokenBalance>& tkns) 
            : balance(bal), tokens(tkns) {}
    };

    std::ostream& operator<<(std::ostream& os, const AccountBalanceData& data);


    struct PrivateKeyData {
      std::string privateKey;
      std::string publicKey;
      std::string seedPhrase;
      std::vector<std::string> accounts;
    };

    std::ostream& operator<<(std::ostream& os, const PrivateKeyData& data);


    struct BladeTxResponse {
        std::string transactionBytes;
        std::vector<std::byte> bytes;
    };

    std::ostream& operator<<(std::ostream& os, const BladeTxResponse& data);


    struct SignMessageData {
        std::string signedMessage;
        std::vector<std::byte> bytes;
    };

    std::ostream& operator<<(std::ostream& os, const SignMessageData& data);


    struct TxReceipt {
        std::string transactionId;
        std::string status;
        TransactionReceipt transactionReceipt;
    };

    std::ostream& operator<<(std::ostream& os, const TxReceipt& data);


    struct Links {
        std::string next;
    };

    std::ostream& operator<<(std::ostream& os, const Links& data);


    struct TransfersRaw {
        std::string account; //"0.0.3"
        long long amount; //6777,
        bool is_approval; //false
        std::string token_id;
    };
 
    std::ostream& operator<<(std::ostream& os, const TransfersRaw& data);


    struct TransactionHistoryNftTransfer {
        std::string receiver_account_id;
        std::string sender_account_id;
        uint serial_number;
        std::string token_id;
    };

    std::ostream& operator<<(std::ostream& os, const TransactionHistoryNftTransfer& data);


    struct TransactionRaw {
        // "bytes":null,
        long long charged_tx_fee;
        std::string consensus_timestamp;
        // "entity_id":null,
        std::string max_fee;
        std::string memo_base64;
        std::string name;
        std::vector<TransactionHistoryNftTransfer> nft_transfers; // TODO describe valid model
        std::string node;
        long long nonce;
        // "parent_consensus_timestamp":null,
        std::string result;
        bool scheduled;
        // "staking_reward_transfers":[],
        std::vector<TransfersRaw> token_transfers;
        std::string transaction_hash;
        std::string transaction_id;
        std::vector<TransfersRaw> transfers;
        std::string valid_duration_seconds;
        std::string valid_start_timestamp;
    };

    std::ostream& operator<<(std::ostream& os, const TransactionRaw& data);
   

    struct TransferData {
        long long amount;
        std::string account;
        std::string token_id;
    };

    std::ostream& operator<<(std::ostream& os, const TransferData& data);


    struct TransactionData {
        std::string transactionId;
        std::string type;
        std::vector<TransferData> transfers;
        std::vector<TransactionHistoryNftTransfer> nftTransfers;
        std::string memo;
        long long fee;
        bool showDetailed;
        // TransactionPlainData plainData;
        std::string consensusTimestamp;
    };

    std::ostream& operator<<(std::ostream& os, const TransactionData& data);


    struct TransactionsHistoryData {
        std::vector<TransactionData> transactions;
        std::string nextPage;
    };

    std::ostream& operator<<(std::ostream& os, const TransactionsHistoryData& data);


    struct TransactionsHistoryRaw {
        std::vector<TransactionRaw> transactions;
        Links links;
    };

    std::ostream& operator<<(std::ostream& os, const TransactionsHistoryRaw& data);

    struct InfoData {
        std::string apiKey;
        std::string dAppCode;
        Network network;
        std::string visitorId;
        SdkEnvironment sdkEnvironment;
        std::string sdkVersion;
    };

    std::ostream& operator<<(std::ostream& os, const InfoData& data);


}

#endif // BLADE_TYPES_H_