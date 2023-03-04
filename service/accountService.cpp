#include "Client.h"
#include "Transaction.h"
#include <boost/beast/core/detail/base64.hpp>

namespace AccountService
{
	using namespace Hedera;
  
  std::vector<unsigned char> base64ToVector(std::string encoded) {
    std::string decoded;
    decoded.resize(boost::beast::detail::base64::decoded_size(encoded.size()));
    boost::beast::detail::base64::decode(&decoded[0], encoded.data(), encoded.size());
    // std::cout << "Bytes:" << std::endl;

    std::vector<unsigned char> output(decoded.begin(), decoded.end() - 1);
    return output;
  }

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
            std::vector<unsigned char> bytes = base64ToVector(updateAccountTransactionBytes);
            Transaction<TransferTransaction>::fromBytes(bytes);
            
            // auto [index, variant] = Transaction<AccountCreateTransaction>::fromBytes(bytes);
                        
            // std::cout << "INDEX: " << index << std::endl;
            // std::cout << "variant: " << variant << std::endl;
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
