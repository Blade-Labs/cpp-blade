cmake_minimum_required(VERSION 3.15...3.24)
set(namespace "Blade")
project(blade-cpp VERSION 0.0.1 DESCRIPTION "Blade SDK C++" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
        hedera-sdk-cpp
	URL https://github.com/hashgraph/hedera-sdk-cpp/archive/refs/tags/v0.3.0.tar.gz
        URL_HASH SHA256=b644fa28a0299b32728d66612969e10fd77f7a7eaaa4caa8f7591877e0c95c8e
)
set(FETCHCONTENT_QUIET OFF)
FetchContent_MakeAvailable(hedera-sdk-cpp)


set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME ON)

find_package(ZLIB REQUIRED)
find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)
find_package(re2 CONFIG REQUIRED)
find_package(absl CONFIG REQUIRED)
find_package(upb CONFIG REQUIRED)
find_package(Threads REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Boost REQUIRED)


include_directories(${OPENSSL_INCLUDE_DIR} ${Boost_INCLUDE_DIRS})
include_directories(${hedera-sdk-cpp_SOURCE_DIR}/${CMAKE_BUILD_TYPE}/${CMAKE_HOST_SYSTEM_NAME}/${CMAKE_HOST_SYSTEM_PROCESSOR}/include)
include_directories(${hedera-sdk-cpp_SOURCE_DIR}/sdk/main/include)
# add_executable(${PROJECT_NAME} src/main.cpp)
add_library(${PROJECT_NAME} STATIC)
target_sources(${PROJECT_NAME}
    PRIVATE
        src/main.cpp
)
target_include_directories(${PROJECT_NAME}
    PRIVATE
        # where the library itself will look for its internal headers
        ${CMAKE_CURRENT_SOURCE_DIR}/src
    PUBLIC
        # where top-level project will look for the library's public headers
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        # where external projects will look for the library's public headers
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

set(public_headers
    include/main.h
)

# not for MSVC
if(CMAKE_COMPILER_IS_GNUCXX)
    # compile options for this target only
    # treat warnings as errors
    target_compile_options(${PROJECT_NAME} PRIVATE -Werror)
endif()

# where to find our CMake modules
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
#message(STATUS "CMake module path: ${CMAKE_MODULE_PATH}")
include(Installing)

target_link_libraries(${PROJECT_NAME} PRIVATE hedera-sdk-cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${OPENSSL_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${OPENSSL_ROOT}/lib)
target_link_libraries(${PROJECT_NAME} PRIVATE ${Boost_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE dl)

if (APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${OSX_CORE_FOUNDATION})
    target_link_libraries(${PROJECT_NAME} PRIVATE ${OSX_CF_NETWORK})
endif ()

if (NOT WIN32)
#    target_link_libraries(${PROJECT_NAME} PRIVATE sys::resolv)
endif ()

target_link_libraries(${PROJECT_NAME} PRIVATE
        gRPC::address_sorting
        gRPC::gpr
        gRPC::grpc
        gRPC::grpc_plugin_support
        gRPC::grpc_unsecure
        protobuf::libprotobuf)

target_link_libraries(${PROJECT_NAME} PRIVATE
        gRPC::grpc++
        gRPC::grpc++_alts
        gRPC::grpc++_error_details
        gRPC::grpc++_unsecure)

if (TARGET gRPC::grpc++_reflection)
    target_link_libraries(${PROJECT_NAME} PRIVATE gRPC::grpc++_reflection)
endif ()

if (TARGET gRPC::grpcpp_channelz)
    target_link_libraries(${PROJECT_NAME} PRIVATE gRPC::grpcpp_channelz)
endif ()

target_link_libraries(${PROJECT_NAME} PRIVATE
        absl::bad_any_cast_impl
        absl::bad_optional_access
        absl::bad_variant_access
        absl::base
        absl::city
        absl::civil_time
        absl::cord
        absl::cord_internal
        absl::cordz_functions
        absl::cordz_handle
        absl::cordz_info
        absl::cordz_sample_token
        absl::debugging_internal
        absl::demangle_internal
        absl::examine_stack
        absl::exponential_biased
        absl::failure_signal_handler
        absl::flags
        absl::flags_commandlineflag
        absl::flags_commandlineflag_internal
        absl::flags_config
        absl::flags_internal
        absl::flags_marshalling
        absl::flags_parse
        absl::flags_private_handle_accessor
        absl::flags_program_name
        absl::flags_reflection
        absl::flags_usage
        absl::flags_usage_internal
        absl::graphcycles_internal
        absl::hash
        absl::hashtablez_sampler
        absl::int128
        absl::leak_check
        absl::log_severity
        absl::low_level_hash
        absl::malloc_internal
        absl::periodic_sampler
        absl::random_distributions
        absl::random_internal_distribution_test_util
        absl::random_internal_platform
        absl::random_internal_pool_urbg
        absl::random_internal_randen
        absl::random_internal_randen_hwaes
        absl::random_internal_randen_hwaes_impl
        absl::random_internal_randen_slow
        absl::random_internal_seed_material
        absl::random_seed_gen_exception
        absl::random_seed_sequences
        absl::raw_hash_set
        absl::raw_logging_internal
        absl::scoped_set_env
        absl::spinlock_wait
        absl::stacktrace
        absl::status
        absl::statusor
        absl::str_format_internal
        absl::strerror
        absl::strings
        absl::strings_internal
        absl::symbolize
        absl::synchronization
        absl::throw_delegate
        absl::time
        absl::time_zone)

target_link_libraries(${PROJECT_NAME} PRIVATE
        upb::upb
        upb::descriptor_upb_proto
        upb::extension_registry
        upb::fastdecode
        upb::json
        upb::mini_table
        upb::reflection
        upb::textformat
        upb::utf8_range)

target_link_libraries(${PROJECT_NAME} PRIVATE
        c-ares::cares
        re2::re2
        ${ZLIB_LIBRARIES})

# Install Library & Headers
install(TARGETS ${PROJECT_NAME} 
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

file(COPY ${hedera-sdk-cpp_SOURCE_DIR}/addressbook/testnet.pb DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE})
file(COPY ${hedera-sdk-cpp_SOURCE_DIR}/addressbook/mainnet.pb DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE})
file(COPY ${hedera-sdk-cpp_SOURCE_DIR}/wordlists/bip39-english.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE})
file(COPY ${hedera-sdk-cpp_SOURCE_DIR}/wordlists/legacy-english.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE})
