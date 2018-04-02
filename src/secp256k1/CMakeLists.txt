cmake_minimum_required(VERSION 3.10)

PROJECT(bitcoin)

INCLUDE_DIRECTORIES(
    ./src/
)
#aux_source_directory(src sources)
set(sources
    ./src/bench_schnorr_verify.c
    ./src/bench_recover.c
    ./src/secp256k1.c
    ./src/bench_sign.c
    ./src/bench_verify.c
    ./src/tests.c
    ./src/gen_context.c
    ./src/bench_ecdh.c
    ./src/bench_internal.c
)

ADD_DEFINITIONS(-DHAVE_CONFIG_H -DVERIFY -DENABLE_MODULE_ECDH -DENABLE_MODULE_SCHNORR -DENABLE_MODULE_RECOVERY)

ADD_DEFINITIONS(-DMAC_OSX -DEBUG_LOCKORDER)

add_library(secp256k1 ${sources})
