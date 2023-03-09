#ifndef BLADE_SERVICE_ACCOUNT_H_
#define BLADE_SERVICE_ACCOUNT_H_

#include "Client.h"
#include "Transaction.h"
#include "TransferTransaction.h"
#include "AccountCreateTransaction.h"
#include "ChunkedTransaction.h"
#include "ECDSAsecp256k1PrivateKey.h"
#include <boost/beast/core/detail/base64.hpp>

namespace AccountService
{
	int executeUpdateAccountTransactions(
        Hedera::Client* client, 
        std::unique_ptr < Hedera::ECDSAsecp256k1PrivateKey> &privateKey,
        std::string updateAccountTransactionBytes,
        std::string transactionBytes
    );
}

#endif // BLADE_SERVICE_ACCOUNT_H_