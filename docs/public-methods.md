# Public methods 📢

## contructor `Blade()`

Creates new instance of Blade and initialize shared parameters. On this step library got unique deviceId (hashed, none specific information shared).

### Parameters:

* `const std::string& apiKey`
* `const Network& network`
* `const std::string& dAppCode`
* `const SdkEnvironment& sdkEnvironment`

### Example:

```cpp
std::string apiKey = "GgsRv5PWfQaRQkykgSDRR3JzXN6kVRwv8RWGIes6SnH2vbSnxWMrf5AAxGbQdYbv";
BladeSDK::Network network = BladeSDK::Network::Testnet;
std::string dAppCode = "unitysdktest";
BladeSDK::SdkEnvironment sdkEnvironment = BladeSDK::SdkEnvironment::CI;
    
BladeSDK::Blade blade = BladeSDK::Blade(apiKey, network, dAppCode, sdkEnvironment);
std::cout << "Blade init: " << blade << std::endl;
```



// TODO

            InfoData getInfo();
            AccountData createAccountBlade();
            AccountInfoData getAccountInfo(std::string accountId);
            AccountBalanceData getBalance(std::string accountId);
            PrivateKeyData importAccount(std::string seedPhrase, bool lookupAccounts);
            TxReceipt transferHbars(std::string accountId, std::string accountPrivateKey, std::string recieverAccount, std::string amount, std::string memo);
            TxReceipt transferTokens(std::string tokenId, std::string accountId, std::string accountPrivateKey, std::string receiverId, std::string amount, std::string memo, bool freeTransfer);
            SignMessageData sign(std::string message, std::string signerKey, std::string encoding);
            bool signVerify(std::string message, std::string signatureHex, std::string key, std::string encoding);
            TxReceipt contractCallFunction(std::string contractId, std::string functionName, ContractFunctionParameters parameters, std::string accountId, std::string accountPrivateKey, long long gas, bool bladePayFee);
            ContractFunctionResult contractCallQueryFunction(std::string contractId, std::string functionName, ContractFunctionParameters parameters, std::string accountId, std::string accountPrivateKey, long long gas, double maxQueryPayment, std::vector<std::string> returnTypes);
            TxReceipt deleteAccount(std::string deleteAccountId, std::string deletePrivateKey, std::string transferAccountId, std::string operatorAccountId, std::string operatorPrivateKey);
            std::string getC14url(std::string asset, std::string account, std::string amount);
            TransactionsHistoryData getTransactions(std::string accountId, std::string transactionType, std::string nextPage, int transactionsLimit);
