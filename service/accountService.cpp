#include "Client.h"
#include "Transaction.h"
#include "TransferTransaction.h"
#include "AccountCreateTransaction.h"
#include "ChunkedTransaction.h"

namespace AccountService
{
	using namespace Hedera;
  
	int executeUpdateAccountTransactions(
        Client* client, 
        std::unique_ptr < ECDSAsecp256k1PrivateKey> &privateKey,
        std::string updateAccountTransactionBytes,
        std::string transactionBytes
    ) {

        std::cout << "executeUpdateAccountTransactions" << std::endl;
        std::cout << "PrivateKey (helper): " << privateKey->toString() << std::endl;
        std::cout << "updateAccountTransactionBytes: " << updateAccountTransactionBytes << std::endl;
        std::cout << "transactionBytes: " << transactionBytes << std::endl;

        //Hedera::Transaction<> transaction;

          if (updateAccountTransactionBytes != "")
          {
            //const buffer = Buffer.from(updateAccountTransactionBytes, "base64");
            //const transaction = await Transaction.fromBytes(buffer).sign(privateKey);
            //await transaction.execute(client);
          }

          if (transactionBytes != "")
          {
            //const buffer = Buffer.from(transactionBytes, "base64");
            //const transaction = await Transaction.fromBytes(buffer).sign(privateKey);
            //await transaction.execute(client);
          }

          return 0;
        }
 }
