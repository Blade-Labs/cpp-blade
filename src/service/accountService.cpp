#include "../../include/service/accountService.h"

using namespace Hedera;

namespace BladeSDK {
namespace AccountService {
	int executeUpdateAccountTransactions(
        Client* client, 
        std::shared_ptr<PrivateKey> &privateKey,
        std::string updateAccountTransactionBytes,
        std::string transactionBytes
  ) {
    if (updateAccountTransactionBytes != "") {
      std::vector<std::byte> bytes = UtilService::base64ToVector(updateAccountTransactionBytes);
        const WrappedTransaction tx = Transaction<AccountUpdateTransaction>::fromBytes(bytes);

        switch (tx.getTransactionType()) {
            case TransactionType::ACCOUNT_UPDATE_TRANSACTION: {
                AccountUpdateTransaction accountUpdateTransaction = *tx.getTransaction<AccountUpdateTransaction>();
                TransactionResponse txResp = accountUpdateTransaction
                    .freezeWith(client)
                    .sign(privateKey)
                    .execute(*client);
                break;
            }
            default: {
              throw std::runtime_error("Unexpected transaction type at executeUpdateAccountTransactions() in updateAccountTransactionBytes");
            }
        }
    }

    if (transactionBytes != "") {
        std::vector<std::byte> bytes = UtilService::base64ToVector(transactionBytes);
        const WrappedTransaction tx = Transaction<TokenAssociateTransaction>::fromBytes(bytes);

        switch (tx.getTransactionType()) {

            case TransactionType::TOKEN_ASSOCIATE_TRANSACTION: {
                TokenAssociateTransaction tokenAssociateTransaction = *tx.getTransaction<TokenAssociateTransaction>();
                TransactionResponse txResp = tokenAssociateTransaction
                    .freezeWith(client)
                    .sign(privateKey)
                    .execute(*client)
                ;
                break;
            }
            default: {
              throw std::runtime_error("Unexpected transaction type at executeUpdateAccountTransactions() in transactionBytes");
            }
        }
    }

    return 0;
  }
}}
