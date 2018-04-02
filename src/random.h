#ifndef BITCOIN_RANDOM_H
#define BITCOIN_RANDOM_H

/**
 * Seed OpenSSL PRNG with additional entropy data
 */
void RandAddSeed();
void RandAddSeedPerfmon();

/**
 * Functions to gather random data via the OpenSSL PRNG
 */
void GetRandBytes(unsigned char* buf, int num);

#endif // BITCOIN_RANDOM_H
