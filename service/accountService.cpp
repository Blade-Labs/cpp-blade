#include "Client.h"
#include "Transaction.h"

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
            // std::vector<unsigned char> bytes();
            // Transaction transaction = Transaction::fromBytes(bytes);

          // const std::string serialized = txBody.SerializeAsString();


          // std::string base64_decoded = boost::algorithm::unbase64(updateAccountTransactionBytes);

          // std::string base64_decoded;
          // boost::beast::detail::base64::decode(updateAccountTransactionBytes, base64_decoded);
// boost::beast::detail::base64::decoded_size()

          // std::string base64_encoded = "SGVsbG8gV29ybGQh";
          // std::vector<unsigned char> output;
          // boost::beast::detail::base64::decode(*void, base64_encoded, output);

          // for (unsigned char byte : output) {
          //     std::cout << static_cast<int>(byte) << " ";
          // }


          // // std::cout << "transactionBytes DECODED: " << base64_decoded << std::endl;


          // const auto [index, txVariant] = Transaction<AccountCreateTransaction>::fromBytes({ updateAccountTransactionBytes.cbegin(), updateAccountTransactionBytes.cend() });





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
