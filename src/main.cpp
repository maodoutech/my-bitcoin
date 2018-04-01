#include "main.h"

#include "amount.h"
#include "txmempool.h"


using namespace std;

#if defined(NDEBUG)
# error "Bitcoin cannot be compiled without assertions."
#endif

int nScriptCheckThreads = 0;
bool fCheckBlockIndex = false;
bool fCheckpointsEnabled = DEFAULT_CHECKPOINTS_ENABLED;
uint64_t nPruneTarget = 0;
bool fPruneMode = false;
bool fRequireStandard = true;
unsigned int nBytesPerSigOp = DEFAULT_BYTES_PER_SIGOP;
bool fIsBareMultisigStd = DEFAULT_PERMIT_BAREMULTISIG;
bool fAlerts = DEFAULT_ALERTS;
bool fEnableReplacement = DEFAULT_ENABLE_REPLACEMENT;

/** Fees smaller than this (in satoshi) are considered zero fee (for relaying, mining and transaction creation) */
CFeeRate minRelayTxFee = CFeeRate(DEFAULT_MIN_RELAY_TX_FEE);

CTxMemPool mempool(::minRelayTxFee);
