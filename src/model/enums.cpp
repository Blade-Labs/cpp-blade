#include "../../include/model/enums.h"

namespace BladeSDK {
    template <typename T>
    std::string enumToString(T item) {
        std::ostringstream oss;
        oss << item;
        return oss.str();
    }

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

