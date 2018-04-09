cmake_minimum_required(VERSION 3.10)

PROJECT(bitcoin)

INCLUDE_DIRECTORIES(
    ./include/
)

set(sources
    ./src/univalue.cpp
    ./src/univalue_read.cpp
    ./src/univalue_write.cpp
)

ADD_DEFINITIONS(-DHAVE_CONFIG_H -DVERIFY -DENABLE_MODULE_ECDH -DENABLE_MODULE_SCHNORR -DENABLE_MODULE_RECOVERY)

ADD_DEFINITIONS(-DMAC_OSX -DEBUG_LOCKORDER)

add_library(univalue ${sources})
