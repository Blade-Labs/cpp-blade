#ifndef BLADE_SERVICE_FINGERPRINT_H_
#define BLADE_SERVICE_FINGERPRINT_H_

#include <string>
#include <openssl/sha.h>

namespace BladeSDK {
    class FingerprintService {
    public:
        FingerprintService();
        std::string getVisitorId();
    private:
        std::string calculateHash(const std::string& input);
        std::string getSystemInfo();
        std::string getSystemInfoWin();
        std::string getSystemInfoLinux();
        std::string getSystemInfoMac();
        std::string readFile(const std::string& filename);
    };
}
#endif // BLADE_SERVICE_FINGERPRINT_H_