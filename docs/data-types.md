# Data types

## SdkEnvironment

```cpp
enum class SdkEnvironment { 
    CI, 
    Prod
};
```

## Network

```cpp
enum class Network {
    Testnet,
    Mainnet
};
```

## AccountData

```cpp
struct AccountData {
    std::string seedPhrase;
    std::string publicKey;
    std::string privateKey;
    std::string accountId;
};
```

## Options

```cpp
struct Options {
    std::string apiKey;
    std::string visitorId;
    Network network;
    std::string dAppCode;
    std::string tvte;
};
```

## AccountInfoData

```cpp
struct AccountInfoData {
    std::string accountId;
    std::string evmAddress;
    std::string publicKey;
};
```

## TokenBalance

```cpp
struct TokenBalance {
    std::string token_id;
    unsigned long long balance;

    TokenBalance(const std::string& tokenId, unsigned long long bal)
        : token_id(tokenId), balance(bal) {}
};
```

## AccountBalanceData

```cpp
struct AccountBalanceData {
    long long balance;
    std::vector<TokenBalance> tokens;

    AccountBalanceData(long long bal, const std::vector<TokenBalance>& tkns) 
        : balance(bal), tokens(tkns) {}
};
```

## PrivateKeyData

```cpp
struct PrivateKeyData {
    std::string privateKey;
    std::string publicKey;
    std::string seedPhrase;
    std::vector<std::string> accounts;
};
```

## BladeTxResponse

```cpp
struct BladeTxResponse {
    std::string transactionBytes;
    std::vector<std::byte> bytes;
};
```

## SignMessageData

```cpp
struct SignMessageData {
    std::string signedMessage;
    std::vector<std::byte> bytes;
};
```

## TxReceipt

```cpp
struct TxReceipt {
    std::string transactionId;
    std::string status;
    TransactionReceipt transactionReceipt;
};
```

## Links

```cpp
struct Links {
    std::string next;
};
```

## TransfersRaw

```cpp
struct TransfersRaw {
    std::string account;
    long long amount;
    bool is_approval;
    std::string token_id;
};
```

## TransactionHistoryNftTransfer

```cpp
struct TransactionHistoryNftTransfer {
    std::string receiver_account_id;
    std::string sender_account_id;
    uint serial_number;
    std::string token_id;
};
```

## TransactionRaw

```cpp
struct TransactionRaw {
    long long charged_tx_fee;
    std::string consensus_timestamp;
    std::string max_fee;
    std::string memo_base64;
    std::string name;
    std::vector<TransactionHistoryNftTransfer> nft_transfers;
    std::string node;
    long long nonce;
    std::string result;
    bool scheduled;
    std::vector<TransfersRaw> token_transfers;
    std::string transaction_hash;
    std::string transaction_id;
    std::vector<TransfersRaw> transfers;
    std::string valid_duration_seconds;
    std::string valid_start_timestamp;
};
```

## TransferData

```cpp
struct TransferData {
    long long amount;
    std::string account;
    std::string token_id;
};
```

## TransactionData

```cpp
struct TransactionData {
    std::string transactionId;
    std::string type;
    std::vector<TransferData> transfers;
    std::vector<TransactionHistoryNftTransfer> nftTransfers;
    std::string memo;
    long long fee;
    bool showDetailed;
    std::string consensusTimestamp;
};
```

## TransactionsHistoryData

```cpp
struct TransactionsHistoryData {
    std::vector<TransactionData> transactions;
    std::string nextPage;
};
```

## TransactionsHistoryRaw

```cpp
struct TransactionsHistoryRaw {
    std::vector<TransactionRaw> transactions;
    Links links;
};
```

## InfoData

```cpp
struct InfoData {
    std::string apiKey;
    std::string dAppCode;
    Network network;
    std::string visitorId;
    SdkEnvironment sdkEnvironment;
    std::string sdkVersion;
};
```