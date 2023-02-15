cmake_minimum_required(VERSION 3.15...3.24)
project(blade-cpp VERSION 0.0.1 DESCRIPTION "Blade SDK C++" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
        hedera-sdk-cpp
        URL https://github.com/hashgraph/hedera-sdk-cpp/releases/download/v0.2.0/hedera-sdk-cpp-v0.2.0-5f4154b3.tar.gz
        URL_HASH SHA256=31343933ea5e148133a49b2abe355954a18d84d8a61f335cca1da985b0419a93
)
set(FETCHCONTENT_QUIET OFF)
FetchContent_MakeAvailable(hedera-sdk-cpp)


include_directories(${hedera-sdk-cpp_SOURCE_DIR}/Debug/Darwin/arm64/include)

#message( "${hedera-sdk-cpp_SOURCE_DIR}/Release/Darwin/arm64/include")

add_executable(${PROJECT_NAME} main.cpp)
