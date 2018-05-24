PROJECT(bitcoin)

set(bitcoind_source
    addrman.cpp
    amount.cpp
    arith_uint256.cpp
    bitcoind.cpp
    bloom.cpp
    chainparams.cpp
    chainparamsbase.cpp
    compat/glibc_sanity.cpp
    compat/glibcxx_sanity.cpp
    clientversion.cpp
    compat/glibc_sanity.cpp
    compat/glibcxx_sanity.cpp
    crypto/hmac_sha256.cpp
    crypto/hmac_sha512.cpp
    crypto/ripemd160.cpp
    crypto/sha256.cpp
    crypto/sha512.cpp
    hash.cpp
    httpserver.cpp
    httprpc.cpp
    init.cpp
    key.cpp
    main.cpp
    net.cpp
    netbase.cpp
    noui.cpp
    protocol.cpp
    pubkey.cpp
    primitives/transaction.cpp
    primitives/block.cpp
    random.cpp
    rest.cpp
    rpcprotocol.cpp
    rpcserver.cpp
    scheduler.cpp
    script/script.cpp
    script/standard.cpp
    support/cleanse.cpp
    support/pagelocker.cpp
    sync.cpp
    timedata.cpp
    txmempool.cpp
    torcontrol.cpp
    util.cpp
    utilmoneystr.cpp
    utilstrencodings.cpp
    utiltime.cpp
    uint256.cpp
    wallet/wallet.cpp
)

ADD_SUBDIRECTORY(secp256k1)
ADD_SUBDIRECTORY(univalue)

ADD_DEFINITIONS(-DMAC_OSX -DEBUG_LOCKORDER -DENABLE_WALLET)

LINK_DIRECTORIES(/usr/local/Cellar/berkeley-db@4/4.8.30/lib)
LINK_DIRECTORIES(/usr/local/Cellar/libevent/2.1.8/lib)

add_executable(bitcoind ${bitcoind_source})
#add_library(bitcoind_static STATIC ${bitcoind_source})

#SET_TARGET_PROPERTIES(bitcoind_static PROPERTIES OUTPUT_NAME "bitcoin")
#SET_TARGET_PROPERTIES(bitcoind PROPERTIES ENABLE_EXPORTS 1)
#SET_TARGET_PROPERTIES(bitcoind PROPERTIES CLEAN_DIRECT_OUTPUT 1)
#SET_TARGET_PROPERTIES(bitcoind_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)

TARGET_LINK_LIBRARIES(bitcoind boost_filesystem boost_system boost_thread boost_program_options boost_chrono secp256k1 crypto ssl db db_cxx event event_pthreads univalue miniupnpc)
