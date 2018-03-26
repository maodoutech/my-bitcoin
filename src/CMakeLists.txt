PROJECT(bitcoin)

set(bitcoind_source
    amount.cpp
    bitcoind.cpp
    chainparams.cpp
    chainparamsbase.cpp
    clientversion.cpp
    init.cpp
    noui.cpp
    torcontrol.cpp
    util.cpp
    utilmoneystr.cpp
    utilstrencodings.cpp
)

ADD_DEFINITIONS(-DMAC_OSX)

add_executable(bitcoind ${bitcoind_source})
add_library(bitcoind_static STATIC ${bitcoind_source})

SET_TARGET_PROPERTIES(bitcoind_static PROPERTIES OUTPUT_NAME "bitcoin")
SET_TARGET_PROPERTIES(bitcoind PROPERTIES ENABLE_EXPORTS 1)
#SET_TARGET_PROPERTIES(bitcoind PROPERTIES CLEAN_DIRECT_OUTPUT 1)
#SET_TARGET_PROPERTIES(bitcoind_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)

TARGET_LINK_LIBRARIES(bitcoind boost_filesystem boost_system boost_thread boost_program_options)
