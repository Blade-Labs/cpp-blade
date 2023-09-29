
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

    std::ostream& operator<<(std::ostream& os, const AccountData& account) {
        os << "{seedPhrase: \"" << account.seedPhrase << "\", ";
        os << "publicKey: \"" << account.publicKey << "\", ";
        os << "privateKey: \"" << account.privateKey << "\", ";
        os << "accountId: \"" << account.accountId << "\"}";
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const Options& options) {
        os << "{apiKey: \"" << options.apiKey << "\", ";
        os << "visitorId: \"" << options.visitorId << "\", ";
        os << "network: \"" << options.network << "\", ";
        os << "dAppCode: \"" << options.dAppCode << "\", ";
        os << "tvte: \"" << options.tvte << "\"}";
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const AccountInfoData& data) {
        os << "{accountId: \"" << data.accountId << "\", ";
        os << "evmAddress: \"" << data.evmAddress << "\", ";
        os << "publicKey: \"" << data.publicKey << "\"}";
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const TokenBalance& data) {
        os << "{token_id: \"" << data.token_id << "\", ";
        os << "balance: " << data.balance << "}";
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const AccountBalanceData& data) {
        os << "{balance: " << data.balance << ", ";
        os << "tokens: " << printItems(data.tokens) << "}";
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const PrivateKeyData& data) {
        os << "{privateKey: \"" << data.privateKey << "\", ";
        os << "publicKey: \"" << data.publicKey << "\", ";
        os << "seedPhrase: \"" << data.seedPhrase << "\", ";
        os << "accounts: " << printItems(data.accounts) << "}";

        return os;
    }

    std::ostream& operator<<(std::ostream& os, const BladeTxResponse& data) {
        os << "{transactionBytes (base64): \"" << data.transactionBytes << "\"}";
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const SignMessageData& data) {
        os << "{signedMessage: \"" << data.signedMessage << "\"}";
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const TxReceipt& data) {
        os << "{transactionId: \"" << data.transactionId << "\", ";
        os << "status: \"" << data.status << "\", ";
        os << "transactionReceipt: {Object TransactionReceipt}}";
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const Links& data) {
        os << "{next: \"" << data.next << "\"}";
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const TransfersRaw& data) {
        os << "{account: \"" << data.account << "\", ";
        os << "amount: \"" << data.amount << "\", ";
        os << "is_approval: " << data.is_approval << ", ";
        os << "token_id: \"" << data.token_id << "\"}";
        
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const TransactionHistoryNftTransfer& data) {
        os << "{receiver_account_id: \"" << data.receiver_account_id << "\", ";
        os << "sender_account_id: \"" << data.sender_account_id << "\", ";
        os << "serial_number: " << data.serial_number << ", ";
        os << "token_id: \"" << data.token_id << "\"}";
        
        return os;
    }

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

    std::ostream& operator<<(std::ostream& os, const TransferData& data) {
        os << "{amount: " << data.amount << ", ";
        os << "account: \"" << data.account << "\", ";
        os << "token_id: \"" << data.token_id << "\"}";
        return os;
    }

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

    std::ostream& operator<<(std::ostream& os, const TransactionsHistoryData& data) {
        os << "{transactions: " << printItems(data.transactions) << ", ";
        os << "nextPage: \"" << data.nextPage << "\"}";
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const TransactionsHistoryRaw& data) {
        os << "{transactions: " << printItems(data.transactions) << ", ";
        os << "links: " << data.links << "}";
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const InfoData& data) {
        os << "{dAppCode: \"" << data.dAppCode << "\", ";
        os << "network: \"" << enumToString(data.network) << "\", ";
        os << "apiKey: " << data.apiKey << ", ";
        os << "visitorId: " << data.visitorId << ", ";
        os << "sdkEnvironment: \"" << enumToString(data.sdkEnvironment) << "\", ";
        os << "sdkVersion: " << data.sdkVersion << "}";
        return os;
    }       
}
