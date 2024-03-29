# Introduction

## Welcome to CPP Blade SDK

As Blade-cpp SDK using https://github.com/hashgraph/hedera-sdk-cpp, which still in development there are limited functionality now. 
Please use ECDSA keys only.

### Requirements



### Supported platforms

- Windows
- Linux
- MacOS

### Example app 

Also there is example app using this SDK, please check: https://github.com/Blade-Labs/cpp-blade-demoapp

[<img src="./docs/demo.gif" width="70%">](https://www.youtube.com/watch?v=RIiEelrwWCA "Demo video")

### Install

Check example app [CMakeLists.txt](https://github.com/Blade-Labs/cpp-blade-demoapp/blob/main/CMakeLists.txt)

1. Add SDK project as git submodule

   `git submodule add git@github.com:Blade-Labs/cpp-blade.git libraries/blade-cpp`

2. Add block to CMakeLists.txt

```
# BLADE-CPP SDK
add_subdirectory(libraries/blade-cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE blade-cpp)

find_package(gRPC CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE c-ares::cares)
include_directories(${CMAKE_BINARY_DIR}/_deps/hedera-sdk-cpp-src/${CMAKE_BUILD_TYPE}/${CMAKE_HOST_SYSTEM_NAME}/${CMAKE_HOST_SYSTEM_PROCESSOR}/include)

install(FILES
        ${CMAKE_SOURCE_DIR}/libraries/blade-cpp/assets/mainnet.pb
        ${CMAKE_SOURCE_DIR}/libraries/blade-cpp/assets/previewnet.pb
        ${CMAKE_SOURCE_DIR}/libraries/blade-cpp/assets/testnet.pb
        DESTINATION bin/addressbook)

# /BLADE-CPP SDK
```

3. Run commands

```bash
cmake --preset macos-arm64-release
cmake --build --preset macos-arm64-release
cd package/bin && ./demo-application
```

The above steps are the basic ones required to set up Blade-cpp SDK. However, there are other configuration options that you may want to explore depending on your use case. You can find more information in the documentation or in [demoapp](https://github.com/Blade-Labs/cpp-blade-demoapp/)
