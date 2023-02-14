cmake_minimum_required(VERSION 3.15...3.24)
project(blade-cpp VERSION 0.1.0 DESCRIPTION "Blade SDK C++" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(Protobuf_USE_STATIC_LIBS ON)
set(gRPC_SSL_PROVIDER package)

set(HASHGRAPH_SDK_DIR ${CMAKE_SOURCE_DIR}/hedera-sdk-cpp)

include_directories(${HASHGRAPH_SDK_DIR}/sdk/main/include)
add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} ${HASHGRAPH_SDK_DIR}/build/windows-x64-debug/openssl/lib/libssl.lib)
target_link_libraries(${PROJECT_NAME} ${HASHGRAPH_SDK_DIR}/build/windows-x64-debug/vcpkg_installed/x64-windows/lib/libcrypto.lib)
target_link_libraries(${PROJECT_NAME} ${HASHGRAPH_SDK_DIR}/build/windows-x64-debug/vcpkg_installed/x64-windows/lib/libprotobuf.lib)
target_link_libraries(${PROJECT_NAME} ${HASHGRAPH_SDK_DIR}/build/windows-x64-debug/_deps/hapi-src/Debug/Windows/AMD64/lib/hapi.lib)
target_link_libraries(${PROJECT_NAME} ${HASHGRAPH_SDK_DIR}/build/windows-x64-debug/sdk/main/Debug/hedera-sdk-cpp.lib)


file(COPY ${HASHGRAPH_SDK_DIR}/addressbook/testnet.pb DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${HASHGRAPH_SDK_DIR}/addressbook/mainnet.pb DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(COPY ${HASHGRAPH_SDK_DIR}/wordlists/bip39-english.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${HASHGRAPH_SDK_DIR}/wordlists/legacy-english.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Install gRPC's roots.pem file for Windows with the examples so that it can be easily referenced.
if (WIN32)
    file(COPY ${HASHGRAPH_SDK_DIR}/vcpkg/packages/grpc_x64-windows/share/grpc/roots.pem DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
    file(COPY ${HASHGRAPH_SDK_DIR}/build/windows-x64-debug/vcpkg_installed/x64-windows/bin/libcrypto-3-x64.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endif ()
