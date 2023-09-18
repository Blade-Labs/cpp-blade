#include <sstream> 

#ifndef BLADE_ENUMS_H_
#define BLADE_ENUMS_H_

namespace BladeSDK {
    template <typename T>
    std::string enumToString(T item) {
        std::ostringstream oss;
        oss << item;
        return oss.str();
    }

    enum class SdkEnvironment { 
        CI, 
        Prod
    };

    std::ostream& operator<<(std::ostream& os, SdkEnvironment environment) {
        switch (environment) {
            case SdkEnvironment::CI:
                os << "CI";
                break;
            case SdkEnvironment::Prod:
                os << "Prod";
                break;
        }
        return os;
    }

    enum class Network {
        Testnet,
        Mainnet
    };

    // Overload operator<< for Network enum
    std::ostream& operator<<(std::ostream& os, Network network) {
        switch (network) {
            case Network::Testnet:
                os << "TESTNET";
                break;
            case Network::Mainnet:
                os << "MAINNET";
                break;
            default:
                os << "[Unknown]";
                break;
        }
        return os;
    }

    enum class EncryptedType {
        tvte,
        vte
    };

    std::ostream& operator<<(std::ostream& os, EncryptedType encryptedType) {
        switch (encryptedType) {
            case EncryptedType::tvte:
                os << "tvte";
                break;
            case EncryptedType::vte:
                os << "vte";
                break;
        }
        return os;
    }
}

#endif //BLADE_ENUMS_H_