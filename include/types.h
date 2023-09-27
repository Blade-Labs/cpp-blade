#include "TransactionReceipt.h"

using namespace Hedera;

namespace BladeSDK {
    template <typename T>
    std::string printItems(const std::vector<T> items) {
        std::ostringstream os;
        
        os << "[";
        for (auto it = items.begin(); it != items.end(); ++it) {
            os << *it;

            if (std::next(it) != items.end()) {
                os << ", ";
            }
        }
        os << "]";

        return os.str();
    }


    struct AccountData {
      std::string seedPhrase;
      std::string publicKey;
      std::string privateKey;
      std::string accountId;
    };

    // Overload the << operator for AccountData
    std::ostream& operator<<(std::ostream& os, const AccountData& account) {
        os << "{seedPhrase: \"" << account.seedPhrase << "\", ";
        os << "publicKey: \"" << account.publicKey << "\", ";
        os << "privateKey: \"" << account.privateKey << "\", ";
        os << "accountId: \"" << account.accountId << "\"}";
        return os;
    }


    struct Options {
      std::string apiKey;
      std::string visitorId;
      Network network;
      std::string dAppCode;
      std::string tvte;
    };

    std::ostream& operator<<(std::ostream& os, const Options& options) {
        os << "{apiKey: \"" << options.apiKey << "\", ";
        os << "visitorId: \"" << options.visitorId << "\", ";
        os << "network: \"" << options.network << "\", ";
        os << "dAppCode: \"" << options.dAppCode << "\", ";
        os << "tvte: \"" << options.tvte << "\"}";
        return os;
    }


    struct AccountInfoData {
        std::string accountId;
        std::string evmAddress;
        std::string publicKey;
    };

    std::ostream& operator<<(std::ostream& os, const AccountInfoData& data) {
        os << "{accountId: \"" << data.accountId << "\", ";
        os << "evmAddress: \"" << data.evmAddress << "\", ";
        os << "publicKey: \"" << data.publicKey << "\"}";
        return os;
    }


    struct TokenBalance {
        std::string token_id;
        unsigned long long balance; // Use 'unsigned long long' to match C#'s ulong

        TokenBalance(const std::string& tokenId, unsigned long long bal)
            : token_id(tokenId), balance(bal) {}
    };

    std::ostream& operator<<(std::ostream& os, const TokenBalance& data) {
        os << "{token_id: \"" << data.token_id << "\", ";
        os << "balance: " << data.balance << "}";
        return os;
    }


    struct AccountBalanceData {
        long long balance; // Use 'long long' to match C#'s long
        std::vector<TokenBalance> tokens;

        // Constructor for AccountBalanceData
        AccountBalanceData(long long bal, const std::vector<TokenBalance>& tkns) 
            : balance(bal), tokens(tkns) {}
    };

    std::ostream& operator<<(std::ostream& os, const AccountBalanceData& data) {
        os << "{balance: " << data.balance << ", ";
        os << "tokens: " << printItems(data.tokens) << "}";
        return os;
    }


    struct PrivateKeyData {
      std::string privateKey;
      std::string publicKey;
      std::string seedPhrase;
      std::vector<std::string> accounts;
    };

    std::ostream& operator<<(std::ostream& os, const PrivateKeyData& data) {
        os << "{privateKey: \"" << data.privateKey << "\", ";
        os << "publicKey: \"" << data.publicKey << "\", ";
        os << "seedPhrase: \"" << data.seedPhrase << "\", ";
        os << "accounts: " << printItems(data.accounts) << "}";

        return os;
    }


    struct BladeTxResponse {
        std::string transactionBytes;
        std::vector<std::byte> bytes;
    };

    std::ostream& operator<<(std::ostream& os, const BladeTxResponse& data) {
        os << "{transactionBytes (base64): \"" << data.transactionBytes << "\"}";
        return os;
    }


    struct SignMessageData {
        std::string signedMessage;
        std::vector<std::byte> bytes;
    };

    std::ostream& operator<<(std::ostream& os, const SignMessageData& data) {
        os << "{signedMessage: \"" << data.signedMessage << "\"}";
        return os;
    }


    struct TxReceipt {
        std::string transactionId;
        std::string status;
        TransactionReceipt transactionReceipt;
    };

    std::ostream& operator<<(std::ostream& os, const TxReceipt& data) {
        os << "{transactionId: \"" << data.transactionId << "\", ";
        os << "status: \"" << data.status << "\", ";
        os << "transactionReceipt: {Object TransactionReceipt}}";
        return os;
    }


    struct Links {
        std::string next;
    };

    std::ostream& operator<<(std::ostream& os, const Links& data) {
        os << "{next: \"" << data.next << "\"}";
        return os;
    }


    struct TransfersRaw {
        std::string account; //"0.0.3"
        long long amount; //6777,
        bool is_approval; //false
        std::string token_id;
    };
 
    std::ostream& operator<<(std::ostream& os, const TransfersRaw& data) {
        os << "{account: \"" << data.account << "\", ";
        os << "amount: \"" << data.amount << "\", ";
        os << "is_approval: " << data.is_approval << ", ";
        os << "token_id: \"" << data.token_id << "\"}";
        
        return os;
    }


    struct TransactionHistoryNftTransfer {
        std::string receiver_account_id;
        std::string sender_account_id;
        uint serial_number;
        std::string token_id;
    };

    std::ostream& operator<<(std::ostream& os, const TransactionHistoryNftTransfer& data) {
        os << "{receiver_account_id: \"" << data.receiver_account_id << "\", ";
        os << "sender_account_id: \"" << data.sender_account_id << "\", ";
        os << "serial_number: " << data.serial_number << ", ";
        os << "token_id: \"" << data.token_id << "\"}";
        
        return os;
    }


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

    std::ostream& operator<<(std::ostream& os, const TransactionRaw& data) {
        os << "{charged_tx_fee: " << data.charged_tx_fee << ", ";
        os << "consensus_timestamp: \"" << data.consensus_timestamp << "\", ";
        os << "max_fee: " << data.max_fee << ", ";
        os << "memo_base64: \"" << data.memo_base64 << "\", ";
        os << "name: \"" << data.name << "\", ";
        os << "nft_transfers: " << printItems(data.nft_transfers) << ", ";
        os << "node: \"" << data.node << "\", ";
        os << "nonce: \"" << data.nonce << "\", ";
        os << "result: \"" << data.result << "\", ";
        os << "scheduled: " << data.scheduled << ", ";
        os << "token_transfers: \"" << printItems(data.token_transfers) << "\", ";
        os << "transaction_hash: \"" << data.transaction_hash << "\", ";
        os << "transaction_id: \"" << data.transaction_id << "\", ";
        os << "transfers: \"" << printItems(data.transfers) << "\", ";
        os << "valid_duration_seconds: \"" << data.valid_duration_seconds << "\", ";
        os << "valid_start_timestamp: \"" << data.valid_start_timestamp << "\"}";  
        return os;
    }

   
    struct TransferData {
        long long amount;
        std::string account;
        std::string token_id;
    };

    std::ostream& operator<<(std::ostream& os, const TransferData& data) {
        os << "{amount: " << data.amount << ", ";
        os << "account: \"" << data.account << "\", ";
        os << "token_id: \"" << data.token_id << "\"}";
        return os;
    }


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

    std::ostream& operator<<(std::ostream& os, const TransactionData& data) {
        os << "{transactionId: \"" << data.transactionId << "\", ";
        os << "type: \"" << data.type << "\", ";
        os << "transfers: " << printItems(data.transfers) << ", ";
        os << "nftTransfers: " << printItems(data.nftTransfers) << ", ";
        os << "memo: \"" << data.memo << "\", ";
        os << "fee: " << data.fee << ", ";
        os << "showDetailed: " << data.showDetailed << ", ";
        // os << "plainData: " << data.plainData << ", ";
        os << "consensusTimestamp: \"" << data.consensusTimestamp << "\"}";
        return os;
    }


    struct TransactionsHistoryData {
        std::vector<TransactionData> transactions;
        std::string nextPage;
    };

    std::ostream& operator<<(std::ostream& os, const TransactionsHistoryData& data) {
        os << "{transactions: " << printItems(data.transactions) << ", ";
        os << "nextPage: \"" << data.nextPage << "\"}";
        return os;
    }


    struct TransactionsHistoryRaw {
        std::vector<TransactionRaw> transactions;
        Links links;
    };

    std::ostream& operator<<(std::ostream& os, const TransactionsHistoryRaw& data) {
        os << "{transactions: " << printItems(data.transactions) << ", ";
        os << "links: " << data.links << "}";
        return os;
    }    
}