#ifndef BITCOIN_AMOUNT_H
#define BITCOIN_AMOUNT_H

#include <stdlib.h>
#include <string>

typedef int64_t CAmount;

static const CAmount COIN = 100000000;
static const CAmount CENT = 1000000;

extern const std::string CURRENCY_UNIT;

#endif //  BITCOIN_AMOUNT_H
