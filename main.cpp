#include "MnemonicBIP39.h"

#include <iostream>
#include <string>

using namespace Hedera;

int main(int argc, char** argv)
{
  std::cout << "Hello, Blade!" << std::endl;
  // MNEMONIC TEST

  std::string passphrase = "";
  std::string seedPhrase = "mutual picnic upgrade spice student spoon pelican bicycle save refuse depend ring";

//  MnemonicBIP39 mnemonic = MnemonicBIP39::initializeBIP39Mnemonic(seedPhrase);
  MnemonicBIP39 mnemonic = MnemonicBIP39::generate12WordBIP39Mnemonic();
  std::cout << "Input MnemonicBIP39: " << mnemonic.toString() << std::endl;

  return 0;
}

