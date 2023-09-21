#include "../../include/service/accountService.h"

using namespace Hedera;

namespace BladeSDK {
namespace AccountService {
	int executeUpdateAccountTransactions(
        Client* client, 
        std::unique_ptr<PrivateKey> &privateKey,
        std::string updateAccountTransactionBytes,
        std::string transactionBytes
  ) {
    if (updateAccountTransactionBytes != "")
    {
      // TODO
      std::cout <<std::endl<<std::endl<< "TODO execute: updateAccountTransactionBytes: " << updateAccountTransactionBytes << std::endl;

      // std::vector<std::byte> bytes = UtilService::base64ToVector(updateAccountTransactionBytes);
      // Transaction<TransferTransaction>::fromBytes(bytes);
      
      // auto [index, variant] = Transaction<AccountCreateTransaction>::fromBytes(bytes);
                  
      // std::cout << "INDEX: " << index << std::endl;
      // std::cout << "variant: " << variant << std::endl;
    }

    if (transactionBytes != "") {
        std::vector<std::byte> bytes = UtilService::base64ToVector(transactionBytes);
        const WrappedTransaction tx = Transaction<TokenAssociateTransaction>::fromBytes(bytes);

        switch (tx.getTransactionType()) {

            case TransactionType::TOKEN_ASSOCIATE_TRANSACTION: {
                TokenAssociateTransaction tokenAssociateTransaction = *tx.getTransaction<TokenAssociateTransaction>();
                TransactionResponse txResp = tokenAssociateTransaction
                    .freezeWith(client)
                    .sign(privateKey.get())
                    .execute(*client)
                ;
                break;
            }
            default: {
              break;
            }
        }
    }

    return 0;
  }
}}
