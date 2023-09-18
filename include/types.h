namespace BladeSDK {
    struct AccountData
    {
      std::string seedPhrase;
      std::string publicKey;
      std::string privateKey;
      std::string accountId;
    };

    // Overload the << operator for AccountData
    std::ostream& operator<<(std::ostream& os, const AccountData& account)
    {
        os << "{seedPhrase: \"" << account.seedPhrase << "\", ";
        os << "publicKey: \"" << account.publicKey << "\", ";
        os << "privateKey: \"" << account.privateKey << "\", ";
        os << "accountId: \"" << account.accountId << "\"}";
        return os;
    }

    struct Options 
    {
      std::string apiKey;
      std::string visitorId;
      Network network;
      std::string dAppCode;
      std::string tvte;
    };

    std::ostream& operator<<(std::ostream& os, const Options& options)
    {
        os << "{apiKey: \"" << options.apiKey << "\", ";
        os << "visitorId: \"" << options.visitorId << "\", ";
        os << "network: \"" << options.network << "\", ";
        os << "dAppCode: \"" << options.dAppCode << "\", ";
        os << "tvte: \"" << options.tvte << "\"}";
        return os;
    }



}