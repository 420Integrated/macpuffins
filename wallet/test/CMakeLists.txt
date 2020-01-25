include_directories(../..)

add_executable(macpuffins-tests
    accounting_tests.cpp
    allocator_tests.cpp
    base32_tests.cpp
    base58_tests.cpp
    base64_tests.cpp
    bignum_tests.cpp
    bloom_tests.cpp
    canonical_tests.cpp
    compress_tests.cpp
    crypter_tests.cpp
    db_tests.cpp
    getarg_tests.cpp
    hash_tests.cpp
    key_tests.cpp
    mruset_tests.cpp
    netbase_tests.cpp
    ntp1_tests.cpp
    pmt_tests.cpp
    rpc_tests.cpp
    script_tests.cpp
    serialize_tests.cpp
    sigopcount_tests.cpp
    transaction_tests.cpp
    uint160_tests.cpp
    uint256_tests.cpp
    util_tests.cpp
    wallet_tests.cpp
    ${GTEST_PATH}/src/gtest_main.cc
    # sources that depend on target as they have defs inside them, these are not tests
    ${CMAKE_SOURCE_DIR}/wallet/wallet.cpp
    ${CMAKE_SOURCE_DIR}/wallet/init.cpp
    )

target_link_libraries(macpuffins-tests
    gtest
    core_lib
    zerocoin_lib
    ntp1_lib
    curltools_lib
    json_spirit_lib
    txdb_lib
    -lpthread
    -lrt
    -ldl
    Boost::system
    Boost::filesystem
    Boost::thread
    Boost::regex
    Boost::program_options
    Boost::iostreams
    Boost::atomic
    ${BERKELEY_DB_LIBRARIES}
    ${CURL_LIBS}
    ${OPENSSL_LIBS}
    ${ZLIB_LIBRARIES}
    )

set_target_properties(macpuffins-tests PROPERTIES COMPILE_FLAGS -Wno-unused-function)

target_compile_definitions(macpuffins-tests PRIVATE
    TEST_ROOT_PATH=\"${CMAKE_CURRENT_SOURCE_DIR}\"
    MACPUFFINS_UNITTESTS
    )

option(MACPUFFINS_DOWNLOAD_AND_TEST_ALL_TXS "[Unit-tests]: Enable downloading and testing all transactions" ON)
option(MACPUFFINS_DOWNLOAD_TX_DATA "[Unit-tests]: Enable downloading transaction data" OFF)
option(MACPUFFINS_RUN_NTP_PARSE_TESTS "[Unit-tests]: Enable NTP1 parsing tests" OFF)

if(MACPUFFINS_DOWNLOAD_AND_TEST_ALL_TXS)
    target_compile_definitions(macpuffins-tests PRIVATE UNITTEST_DOWNLOAD_PREMADE_TX_DATA_AND_RUN_PARSE_TESTS)
endif()

if(MACPUFFINS_DOWNLOAD_TX_DATA)
    target_compile_definitions(macpuffins-tests PRIVATE UNITTEST_DOWNLOAD_TX_DATA)
endif()

if(MACPUFFINS_RUN_NTP_PARSE_TESTS)
    target_compile_definitions(macpuffins-tests PRIVATE UNITTEST_RUN_NTP_PARSE_TESTS)
endif()

add_test(
    NAME macpuffins-core-tests
    COMMAND macpuffins-core-tests
    --datadir ${CMAKE_CURRENT_SOURCE_DIR}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )
