#include "Client.h"
#include "Transaction.h"
#include "TransferTransaction.h"
#include "AccountCreateTransaction.h"
#include "ChunkedTransaction.h"

#include "accountService.cpp"

namespace AccountService
{
	int executeUpdateAccountTransactions(
        Client* client, 
        std::unique_ptr < ECDSAsecp256k1PrivateKey> &privateKey,
        std::string updateAccountTransactionBytes,
        std::string transactionBytes
    );
}