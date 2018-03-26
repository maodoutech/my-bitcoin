PROJECT(bitcoin)

set(bitcoind_source
    bitcoind.cpp
    noui.cpp
    util.cpp
    init.cpp)

add_executable(bitcoind ${bitcoind_source})
add_library(bitcoind_static STATIC ${bitcoind_source})

SET_TARGET_PROPERTIES(bitcoind_static PROPERTIES OUTPUT_NAME "bitcoin")
SET_TARGET_PROPERTIES(bitcoind PROPERTIES ENABLE_EXPORTS 1)
#SET_TARGET_PROPERTIES(bitcoind PROPERTIES CLEAN_DIRECT_OUTPUT 1)
#SET_TARGET_PROPERTIES(bitcoind_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)

TARGET_LINK_LIBRARIES(bitcoind boost_filesystem boost_system)
