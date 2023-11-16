# Public methods 📢

## contructor `Blade()`

Creates new instance of Blade and initialize shared parameters. On this step library got unique deviceId (hashed, none specific information shared).

### Parameters

* `const std::string& apiKey` - key for API provided by Blade team. Unique per network and sdkEnvironment.
* `const Network& network` - network `BladeSDK::Network::Testnet` or `BladeSDK::Network::Mainnet`
* `const std::string& dAppCode` - your dAppCode - request specific one by contacting us
* `const SdkEnvironment& sdkEnvironment` - BladeApi environment - `BladeSDK::SdkEnvironment::CI` or `BladeSDK::SdkEnvironment::Prod`

### Example

```cpp
std::string apiKey = "GgsRv5PWfQaRQkykgSDRR3JzXN6kVRwv8RWGIes6SnH2vbSnxWMrf5AAxGbQdYbv";
BladeSDK::Network network = BladeSDK::Network::Testnet;
std::string dAppCode = "unitysdktest";
BladeSDK::SdkEnvironment sdkEnvironment = BladeSDK::SdkEnvironment::CI;
    
BladeSDK::Blade blade = BladeSDK::Blade(apiKey, network, dAppCode, sdkEnvironment);
std::cout << "Blade init: " << blade << std::endl;
```

## InfoData getInfo()

Returns blade instance shared params (apiKey, dAppCode, network, visitorId, sdkEnvironment, sdkVersion)

### Example 

```cpp
std::cout << "Get Blade info: " << blade.getInfo() << std::endl;
```

Output: 

```
Get Blade info: {dAppCode: "unitysdktest", network: "TESTNET", apiKey: GgsRv5PWfQaRQkykgSDRR3JzXN6kVRwv8RWGIes6SnH2vbSnxWMrf5AAxGbQdYbv, visitorId: 26b127c2fb4cf57625a3ae627ac903e4c2e0b604e6863632122cb15615c844ed, sdkEnvironment: "CI", sdkVersion: Cpp@0.6.4}
```


## AccountData createAccount()

Create Hedera account (ECDSA). Only for configured dApps. Depending on dApp config Blade create account, associate tokens, etc. In case of not using pre-created accounts pool and network high load, this method can return transactionId and no accountId. In that case account creation added to queue, and you should wait some time and call getPendingAccount() method.

### Example

```cpp
std::cout << "Create Hedera account: " << blade.createAccount() << std::endl;
```

Output:

```
Create Hedera account: {seedPhrase: "easily forward forward river bachelor task endorse sea inherit bonus polar sport", publicKey: "", privateKey: "3030020100300706052B8104000A0422042085FE29B639291C2534487D0663E15BADEAF5197ED6770FFDAF7FFF1EEEA27406", accountId: "0.0.5895062"}
```

## TxReceipt deleteAccount(std::string deleteAccountId, std::string deletePrivateKey, std::string transferAccountId, std::string operatorAccountId, std::string operatorPrivateKey)

Delete Hedera account

### Parameters

* `std::string deleteAccountId` - account id of account to delete (0.0.xxxxx)
* `std::string deletePrivateKey` - account private key ECDSA (DER encoded hex string)
* `std::string transferAccountId` - funds receiver account id. If any funds left on account, they will be transferred to this account (0.0.xxxxx)
* `std::string operatorAccountId` - operator account id (0.0.xxxxx). Used for fee
* `std::string operatorPrivateKey` - operator's account private key ECDSA (DER encoded hex string)

### Example

```cpp
std::cout << "Delete account: " << blade.deleteAccount("0.0.5895062", "3030020100300706052B8104000A0422042085FE29B639291C2534487D0663E15BADEAF5197ED6770FFDAF7FFF1EEEA27406", "0.0.346533", "0.0.346533", "3030020100300706052b8104000a04220420ebccecef769bb5597d0009123a0fd96d2cdbe041c2a2da937aaf8bdc8731799b") << std::endl;
```

Output:

```
Delete account: {transactionId: "0.0.346533@1700131320.242081000", status: "SUCCESS", transactionReceipt: {Object TransactionReceipt}}
```

## AccountInfoData getAccountInfo(std::string accountId)

Get account info. EvmAddress is address of Hedera account if exists. Else accountId will be converted to solidity address. CalculatedEvmAddress is calculated from account public key. May be different from evmAddress.

### Parameters

* `std::string accountId` - Hedera account id (0.0.xxxxx)

### Example

```cpp
std::cout << "Get account info: " << blade.getAccountInfo("0.0.346533") << std::endl;
```

Output:

```
Get account info: {accountId: "0.0.346533", evmAddress: "0x11f8d856ff2af6700ccda4999845b2ed4502d8fb", publicKey: "029dc73991b0d9cdbb59b2cd0a97a0eaff6de801726cb39804ea9461df6be2dd30"}
```

## AccountBalanceData getBalance(std::string accountId)

Get hbar and token balances for specific account.

### Parameters

* `std::string accountId` - Hedera account id (0.0.xxxxx)

### Example

```cpp
std::cout << "Account balance: " << blade.getBalance(accountId) << std::endl;
```

Output:

```
Account balance: {balance: 1000000000000, tokens: [{token_id: "0.0.59042", balance: 0}, {token_id: "0.0.61266", balance: 0}, {token_id: "0.0.416406", balance: 1000000000}, {token_id: "0.0.416458", balance: 1000000000}, {token_id: "0.0.416487", balance: 99849591049227}, {token_id: "0.0.433870", balance: 9816}, {token_id: "0.0.447892", balance: 20000000}, {token_id: "0.0.652199", balance: 999999952}]}
```

## PrivateKeyData importAccount(std::string seedPhrase, bool lookupAccounts)

Get ECDSA private key from mnemonic. Also try to find accountIds based on public key if `lookupAccounts` is true. Returned keys with DER header. EvmAddress computed from Public key.

### Parameters

* `std::string seedPhrase` - BIP39 mnemonic
* `bool lookupAccounts` - if true, get accountIds from mirror node by public key

### Example

```cpp
std::cout << "Import account: " << blade.importAccount("best soccer little verify love ladder else kick depth mesh silly desert", true) << std::endl;
```

Output:

```
Import account: {privateKey: "3030020100300706052B8104000A04220420A7E529D9C0EA996FF62F9E41D5BE81FD67489E28B62CE22420BE130626D0EF40", publicKey: "302D300706052B8104000A0322000283529A9F1353613201042305827FB38110E94C3FD559E3CF9B5645DBE0E38368", seedPhrase: "best soccer little verify love ladder else kick depth mesh silly desert", accounts: [0.0.2018696]}
```

## TxReceipt transferHbars(std::string accountId, std::string accountPrivateKey, std::string recieverAccount, std::string amount, std::string memo)

Send hbars to specific account.

### Parameters

* `std::string accountId` - sender account id (0.0.xxxxx)
* `std::string accountPrivateKey` - sender's hex-encoded private key with DER-header (302e020100300506032b657004220420...) ECDSA
* `std::string recieverAccount` - receiver account id (0.0.xxxxx)
* `std::string amount` - amout of hbars to send
* `std::string memo` - transaction memo

### Example

```cpp
std::cout << "Transfer hbars: " << blade.transferHbars("0.0.346533", "3030020100300706052b8104000a04220420ebccecef769bb5597d0009123a0fd96d2cdbe041c2a2da937aaf8bdc8731799b", "0.0.346530", "1.5", "cpp-sdk-test") << std::endl;
```

Output:

```
Transfer hbars: {transactionId: "0.0.346533@1700129947.125393000", status: "SUCCESS", transactionReceipt: {Object TransactionReceipt}}
```

## TxReceipt transferTokens(std::string tokenId, std::string accountId, std::string accountPrivateKey, std::string receiverId, std::string amount, std::string memo, bool freeTransfer)

Send token to specific account.

### Parameters

* `std::string tokenId` - token id to send (0.0.xxxxx)
* `std::string accountId` - sender account id (0.0.xxxxx)
* `std::string accountPrivateKey` - sender's hex-encoded private key with DER-header (302e020100300506032b657004220420...). ECDSA
* `std::string receiverId` - receiver account id (0.0.xxxxx)
* `std::string amount` - amount of tokens to send 
* `std::string memo` - transaction memo
* `bool freeTransfer` - if true, Blade will pay fee transaction. Only for single dApp configured token. In that case tokenId not used

### Example

```cpp
std::cout << "Transfer tokens (paid): " <<  blade.transferTokens("0.0.433870", "0.0.346533", "3030020100300706052b8104000a04220420ebccecef769bb5597d0009123a0fd96d2cdbe041c2a2da937aaf8bdc8731799b", "0.0.346530", "1", "cpp-sdk-paid-token-transfer", false) << std::endl;
```

Output:

```
Transfer tokens (paid): {transactionId: "0.0.346533@1700130243.724897000", status: "SUCCESS", transactionReceipt: {Object TransactionReceipt}}
```

## SignMessageData sign(std::string message, std::string signerKey, std::string encoding)

Sign message with private key. Returns hex-encoded signature.

### Parameters

* `std::string message` - hex/base64/string message to sign
* `std::string signerKey` - ECDSA hex-encoded private key with DER header
* `std::string encoding` - message encoding: `hex`, `base64` or `string`

### Example

```cpp
std::string message = "hello";
std::string messageBase64 = BladeSDK::UtilService::stringToBase64(message);
std::string messageHex = BladeSDK::UtilService::vectorToHex(BladeSDK::UtilService::stringToVector(message));

std::cout << "Sign str (" << message << "): " << blade.sign(message, privateKeyHex, "string") << std::endl;
std::cout << "Sign base64 (" << messageBase64 << "): " << blade.sign(messageBase64, privateKeyHex, "base64") << std::endl;
std::cout << "Sign hex (" << messageHex << "): " << blade.sign(messageHex, privateKeyHex, "hex") << std::endl;
```

Output:

```
Sign str (hello): {signedMessage: "7df5b75438e479540a6852b1cb2146de2b0e7e998cb947d2d52a83841afeed6d8d48585887b9c7acae5019d8bce3d97dad06cee0f2aad9d313c03dbdc07b848e"}
Sign base64 (aGVsbG8=): {signedMessage: "41cb875722cc5f6c03989bbf4c49fa9fda3d69b4911864513347fe388c0b93270fa0d7a4385d31d4feec19750e118f101a3ab9c9033748782be01336b007847c"}
Sign hex (68656c6c6f): {signedMessage: "350b2f5e5a182f55cbad6bd03a3fa5cfb05a3da52af7db94161ff7a51fa531e81d035979125cef242ac72b8d3b54c8898245bdf23df14b9df4f06f161f0d9d1d"}
```

## bool signVerify(std::string message, std::string signatureHex, std::string key, std::string encoding)

Verify message signature by public key.

### Parameters

* `std::string message` - hex/base64/string message to sign
* `std::string signatureHex` - hex-encoded signature
* `std::string key` - ECDSA hex-encoded public key with DER header
* `std::string encoding` - message encoding: `hex`, `base64` or `string`

### Example

```cpp
std::string message = "hello";
std::string messageBase64 = BladeSDK::UtilService::stringToBase64(message);
std::string messageHex = BladeSDK::UtilService::vectorToHex(BladeSDK::UtilService::stringToVector(message));

BladeSDK::SignMessageData signature = blade.sign(message, privateKeyHex, "string");
std::cout << "Sign str (" << message << "): " << signature << std::endl;
std::cout << "Valid?: " << blade.signVerify(message, signature.signedMessage, publicKeyHex, "string") << std::endl;  

signature = blade.sign(messageBase64, privateKeyHex, "base64");
std::cout << "Sign base64 (" << messageBase64 << "): " << signature << std::endl;
std::cout << "Valid?: " << blade.signVerify(messageBase64, signature.signedMessage, publicKeyHex, "base64") << std::endl;

signature = blade.sign(messageHex, privateKeyHex, "hex");
std::cout << "Sign hex (" << messageHex << "): " << signature << std::endl;
std::cout << "Valid?: " << blade.signVerify(messageHex, signature.signedMessage, publicKeyHex, "hex") << std::endl;
```

Output:

```
Sign str (hello): {signedMessage: "57a43fe4c9b46b7c3455558845d835830462efdd685d4397806cb34730ed206764f1c53cbefc69ade98a04998f5518ef5365dfde38c80eee86663e6f366157ec"}
Valid?: 1
Sign base64 (aGVsbG8=): {signedMessage: "4b8c25583e9aa7081bb22299319a0c19c233bfa6b4e2cf1d4cf603c49c8ef51308be68b6586f3bbb31e595d9f0cf452e77667dbcc1bb8a9a3449600e786d6b3d"}
Valid?: 1
Sign hex (68656c6c6f): {signedMessage: "1f83a26c1fee4a04789e1c327180fb03e6ff85ec115fa94d845e501c22c9d1e1467b7adda0d3858b3c707adf2e360f400f7e526517e66f86e9479a343423a632"}
Valid?: 1
```

## TxReceipt contractCallFunction(std::string contractId, std::string functionName, ContractFunctionParameters parameters, std::string accountId, std::string accountPrivateKey, long long gas, bool bladePayFee)

Call contract function. Directly or via Blade Payer account (fee will be paid by Blade), depending on your dApp configuration.

### Parameters

* `std::string contractId` - contract id (0.0.xxxxx)
* `std::string functionName` - name of the contract function to call
* `ContractFunctionParameters parameters` - function arguments. Can be generated with ContractFunctionParameters object
* `std::string accountId` - operator account id (0.0.xxxxx)
* `std::string accountPrivateKey` - operator's hex-encoded private key with DER-header, ECDSA
* `long long gas` - gas limit for the transaction
* `bool bladePayFee` - if true, fee will be paid by Blade (note: msg.sender inside the contract will be Blade Payer account)

### Example

```cpp
ContractFunctionParameters params = ContractFunctionParameters().addString("cpp-sdk-test [self pay]");
std::cout << "Contract call: " << blade.contractCallFunction("0.0.416245", "set_message", params, "0.0.346533", "3030020100300706052b8104000a04220420ebccecef769bb5597d0009123a0fd96d2cdbe041c2a2da937aaf8bdc8731799b", 150000, false) << std::endl;
```

Output:

```
Contract call: {transactionId: "0.0.346533@1700133017.81407000", status: "SUCCESS", transactionReceipt: {Object TransactionReceipt}}
```

## ContractFunctionResult contractCallQueryFunction(std::string contractId, std::string functionName, ContractFunctionParameters parameters, std::string accountId, std::string accountPrivateKey, long long gas, double maxQueryPayment, std::vector<std::string> returnTypes)

Call query on contract function. Similar to contractCallFunction can be called directly only.

### Parameters

* `std::string contractId` - contract id (0.0.xxxxx)
* `std::string functionName` - name of the contract function to call
* `ContractFunctionParameters parameters` - function argument. Can be generated with ContractFunctionParameters object
* `std::string accountId` - operator account id (0.0.xxxxx)
* `std::string accountPrivateKey` - operator's hex-encoded private key with DER-header, ECDSA
* `long long gas` - gas limit for the transaction
* `double maxQueryPayment` - max query payment amount
* `std::vector<std::string> returnTypes` - array of result types

### Example

```cpp
ContractFunctionParameters params = ContractFunctionParameters();
ContractFunctionResult res = blade.contractCallQueryFunction("0.0.416245", "get_message", params, "0.0.346533", "3030020100300706052b8104000a04220420ebccecef769bb5597d0009123a0fd96d2cdbe041c2a2da937aaf8bdc8731799b", 50000, 1.5, {"string", "int32"});
std::cout << "Contract call query. string: " << res.getString(0) << ", int32: " << std::to_string(res.getInt32(1)) << std::endl;
```

Output:

```
Contract call query. string: cpp-sdk-test [self pay], int32: 23
```

## std::string getC14url(std::string asset, std::string account, std::string amount)

Get configured url for C14 integration (iframe or popup)

### Parameters

* `std::string asset` - name (USDC, HBAR, etc)
* `std::string account` - receiver account id (0.0.xxxxx)
* `std::string amount` - preset amount. May be overwritten if out of range (min/max)

### Example

```cpp
std::cout << "Get c14 url: " << blade.getC14url("karate", "0.0.123456", "1234") << std::endl;
```

Output:

```
Get c14 url: https://pay.c14.money/?clientId=00ce2e0a-ee66-4971-a0e9-b9d627d106b0&targetAssetId=057d6b35-1af5-4827-bee2-c12842faa49e&targetAssetIdLock=true&sourceAmount=1234&quoteAmountLock=true&targetAddress=0.0.123456&targetAddressLock=true
```

## TransactionsHistoryData getTransactions(std::string accountId, std::string transactionType, std::string nextPage, int transactionsLimit)

Get transactions history for account. Can be filtered by transaction type. Transaction requested from mirror node. Every transaction requested for child transactions. Result are flattened. If transaction type is not provided, all transactions will be returned.

### Parameters

* `std::string accountId` - account id to get transactions for (0.0.xxxxx)
* `std::string transactionType` - one of enum  (`CRYPTOTRANSFER`, `CONTRACTCALL`, etc...)
* `std::string nextPage` - link to next page of transactions from previous request
* `int transactionsLimit` - number of transactions to return. Speed of request depends on this value if transactionType is set.

### Example

```cpp
BladeSDK::TransactionsHistoryData history = blade.getTransactions(accountId, "CRYPTODELETE", "", 2);
std::cout << "getTransactions (CRYPTODELETE)[" << history.transactions.size() << "]: " << history << std::endl << std::endl;

history = blade.getTransactions(accountId, "CRYPTODELETE", "/api/v1/transactions?account.id=0.0.346533&limit=25&timestamp=lt:1700131206.544183003", 2);
std::cout << "getTransactions (CRYPTODELETE)[" << history.transactions.size() << "]: " << history << std::endl;

```

Output:

```
etTransactions (CRYPTODELETE)[2]: {transactions: [{transactionId: "0.0.346533-1700131320-242081000", type: "CRYPTODELETE", transfers: [{amount: 415840, account: "0.0.6", token_id: ""}, {amount: 11391169, account: "0.0.98", token_id: ""}, {amount: 1265685, account: "0.0.800", token_id: ""}, {amount: -13072694, account: "0.0.346533", token_id: ""}], nftTransfers: [], memo: "", fee: 13072694, showDetailed: 0, consensusTimestamp: "1700131320.931657486"}, {transactionId: "0.0.346533-1700131205-926001000", type: "CRYPTODELETE", transfers: [{amount: 415840, account: "0.0.3", token_id: ""}, {amount: 11391169, account: "0.0.98", token_id: ""}, {amount: 1265685, account: "0.0.800", token_id: ""}, {amount: -13072694, account: "0.0.346533", token_id: ""}], nftTransfers: [], memo: "", fee: 13072694, showDetailed: 0, consensusTimestamp: "1700131206.544183003"}], nextPage: "/api/v1/transactions?account.id=0.0.346533&limit=25&timestamp=lt:1700131206.544183003"}

getTransactions (CRYPTODELETE)[2]: {transactions: [{transactionId: "0.0.346533-1700131152-542465000", type: "CRYPTODELETE", transfers: [{amount: 415840, account: "0.0.9", token_id: ""}, {amount: 11391169, account: "0.0.98", token_id: ""}, {amount: 1265685, account: "0.0.800", token_id: ""}, {amount: -13072694, account: "0.0.346533", token_id: ""}], nftTransfers: [], memo: "", fee: 13072694, showDetailed: 0, consensusTimestamp: "1700131153.029236922"}, {transactionId: "0.0.346533-1700131107-295252000", type: "CRYPTODELETE", transfers: [{amount: 415840, account: "0.0.6", token_id: ""}, {amount: 11391169, account: "0.0.98", token_id: ""}, {amount: 1265685, account: "0.0.800", token_id: ""}, {amount: -13072694, account: "0.0.346533", token_id: ""}], nftTransfers: [], memo: "", fee: 13072694, showDetailed: 0, consensusTimestamp: "1700131108.024235003"}], nextPage: "/api/v1/transactions?account.id=0.0.346533&limit=25&timestamp=lt:1700131108.024235003"}
```
