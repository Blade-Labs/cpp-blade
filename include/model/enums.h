#include <sstream> 

#ifndef BLADE_ENUMS_H_
#define BLADE_ENUMS_H_

namespace BladeSDK {
    template <typename T>
    std::string enumToString(T item);

    enum class SdkEnvironment { 
        CI, 
        Prod
    };

    std::ostream& operator<<(std::ostream& os, SdkEnvironment environment);

    enum class Network {
        Testnet,
        Mainnet
    };

    
    std::ostream& operator<<(std::ostream& os, Network network);

    enum class EncryptedType {
        tvte,
        vte
    };

    std::ostream& operator<<(std::ostream& os, EncryptedType encryptedType);
}

#endif //BLADE_ENUMS_H_