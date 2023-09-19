namespace BladeSDK {
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
        os << "tokens: [";

        for (auto it = data.tokens.begin(); it != data.tokens.end(); ++it) {
            const TokenBalance& token = *it;
            os << token;

            if (std::next(it) != data.tokens.end()) {
                os << ", ";
            }
        }

        os << "]}";
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
        os << "accounts: [";

        for (auto it = data.accounts.begin(); it != data.accounts.end(); ++it) {
            const std::string& account = *it;
            os << "\"" << account << "\"";

            if (std::next(it) != data.accounts.end()) {
                os << ", ";
            }
        }

        os << "]}";
        return os;
    }

}