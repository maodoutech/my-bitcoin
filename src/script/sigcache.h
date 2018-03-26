#ifndef BITCOIN_SCRIPT_SIGCACHE_H
#define BITCOIN_SCRIPT_SIGCACHE_H

// DoS prevention: limit cache size to less than 40MB (over 500000
// entries on 64-bit systems).
static const unsigned int DEFAULT_MAX_SIG_CACHE_SIZE = 40;

#endif // BITCOIN_SCRIPT_SIGCACHE_H
