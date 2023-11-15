# Initialization

Before call any method of Blade object you need to call initialize. It creates invisible web-view, and attach all required handlers to interact. Also it will init fingerprintjs and retrieve visitorId, which is required for BladeAPI.

Example:

```
#include <iostream>
#include <BladeSDK.h>

using namespace BladeSDK;

int main(int argc, char *argv[]) {
    std::string apiKey = "GgsRv5PWfQaRQkykgSDRR3JzXN6kVRwv8RWGIes6SnH2vbSnxWMrf5AAxGbQdYbv";
    Network network = Network::Testnet;
    std::string dAppCode = "unitysdktest";
    SdkEnvironment sdkEnvironment = SdkEnvironment::CI;

    Blade blade = Blade(apiKey, network, dAppCode, sdkEnvironment);
    std::cout << "Blade init: " << blade << std::endl;
}
```

Output:

```
Blade init: {dAppCode: "unitysdktest", network: "TESTNET", apiKey: GgsRv5PWfQaRQkykgSDRR3JzXN6kVRwv8RWGIes6SnH2vbSnxWMrf5AAxGbQdYbv, visitorId: 26b127c2fb4cf57625a3ae627ac903e4c2e0b604e6863632122cb15615c844ed, sdkEnvironment: "CI", sdkVersion: Cpp@0.6.4}
```