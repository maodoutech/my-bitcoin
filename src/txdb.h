#ifndef BITCOIN_TXDB_H
#define BITCOIN_TXDB_H

#include <stdint.h>
#include <utility>

//! -dbcache default (MiB)
static const int64_t nDefaultDbCache = 100;
//! max. -dbcache in (MiB)
static const int64_t nMaxDbCache = sizeof(void*) > 4 ? 16384 : 1024;
//! min. -dbcache in (MiB)
static const int64_t nMinDbCache = 4;

#endif // BITCOIN_TXDB_H
