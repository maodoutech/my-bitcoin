#include "random.h"

#include "support/cleanse.h"
#include "util.h"             // for LogPrint()

#include <sys/time.h>
#include <openssl/err.h>
#include <openssl/rand.h>

static inline int64_t GetPerformanceCounter()
{
    int64_t nCounter = 0;

    timeval t;
    gettimeofday(&t, NULL);
    nCounter = (int64_t)(t.tv_sec * 1000000 + t.tv_usec);

    return nCounter;
}

void RandAddSeed()
{
    // Seed with CPU performance counter
    int64_t nCounter = GetPerformanceCounter();
    RAND_add(&nCounter, sizeof(nCounter), 1.5);
    memory_cleanse((void*)&nCounter, sizeof(nCounter));
}

void RandAddSeedPerfmon()
{
    RandAddSeed();
}


void GetRandBytes(unsigned char* buf, int num)
{
    if (RAND_bytes(buf, num) != 1) {
        LogPrintf("%s: OpenSSL RAND_bytes() failed with error: %s\n", __func__, ERR_error_string(ERR_get_error(), NULL));
        assert(false);
    }
}

uint32_t insecure_rand_Rz = 11;
uint32_t insecure_rand_Rw = 11;
void seed_insecure_rand(bool fDeterministic)
{
    // The seed values have some unlikely fixed points which we avoid.
    if (fDeterministic) {
        insecure_rand_Rz = insecure_rand_Rw = 11;
    } else {
        uint32_t tmp;
        do {
            GetRandBytes((unsigned char*)&tmp, 4);
        } while (tmp == 0 || tmp == 0x9068ffffU);
        insecure_rand_Rz = tmp;
        do {
            GetRandBytes((unsigned char*)&tmp, 4);
        } while (tmp == 0 || tmp == 0x464fffffU);
        insecure_rand_Rw = tmp;
    }
}
