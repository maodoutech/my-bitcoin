#ifndef BITCOIN_MAIN_H
#define BITCOIN_MAIN_H

#include "amount.h"
#include "net.h"
#include "sync.h"

#include <stdint.h>

class CTxMemPool;

/** Default for accepting alerts from the P2P network. */
static const bool DEFAULT_ALERTS = false;
/** Default for DEFAULT_WHITELISTRELAY. */
static const bool DEFAULT_WHITELISTRELAY = true;
/** Default for DEFAULT_WHITELISTFORCERELAY. */
static const bool DEFAULT_WHITELISTFORCERELAY = true;
/** Default for -minrelaytxfee, minimum relay fee for transactions */
static const unsigned int DEFAULT_MIN_RELAY_TX_FEE = 1000;
/** Default for -maxorphantx, maximum number of orphan transactions kept in memory */
static const unsigned int DEFAULT_MAX_ORPHAN_TRANSACTIONS = 100;
/** Default for -limitancestorcount, max number of in-mempool ancestors */
static const unsigned int DEFAULT_ANCESTOR_LIMIT = 25;
/** Default for -limitancestorsize, maximum kilobytes of tx + all in-mempool ancestors */
static const unsigned int DEFAULT_ANCESTOR_SIZE_LIMIT = 101;
/** Default for -limitdescendantcount, max number of in-mempool descendants */
static const unsigned int DEFAULT_DESCENDANT_LIMIT = 25;
/** Default for -limitdescendantsize, maximum kilobytes of in-mempool descendants */
static const unsigned int DEFAULT_DESCENDANT_SIZE_LIMIT = 101;
/** Default for -mempoolexpiry, expiration time for mempool transactions in hours */
static const unsigned int DEFAULT_MEMPOOL_EXPIRY = 72;
/** The maximum size of a blk?????.dat file (since 0.8) */
static const unsigned int MAX_BLOCKFILE_SIZE = 0x8000000; // 128 MiB
/** The pre-allocation chunk size for blk?????.dat files (since 0.8) */
static const unsigned int BLOCKFILE_CHUNK_SIZE = 0x1000000; // 16 MiB
/** The pre-allocation chunk size for rev?????.dat files (since 0.8) */
static const unsigned int UNDOFILE_CHUNK_SIZE = 0x100000; // 1 MiB

/** Maximum number of script-checking threads allowed */
static const int MAX_SCRIPTCHECK_THREADS = 16;
/** -par default (number of script-checking threads, 0 = auto) */
static const int DEFAULT_SCRIPTCHECK_THREADS = 0;
/** Number of blocks that can be requested at any given time from a single peer. */
static const int MAX_BLOCKS_IN_TRANSIT_PER_PEER = 16;
/** Timeout in seconds during which a peer must stall block download progress before being disconnected. */
static const unsigned int BLOCK_STALLING_TIMEOUT = 2;
/** Number of headers sent in one getheaders result. We rely on the assumption that if a peer sends
 *  less than this number, we reached its tip. Changing this value is a protocol upgrade. */
static const unsigned int MAX_HEADERS_RESULTS = 2000;
/** Size of the "block download window": how far ahead of our current height do we fetch?
 *  Larger windows tolerate larger download speed differences between peer, but increase the potential
 *  degree of disordering of blocks on disk (which make reindexing and in the future perhaps pruning
 *  harder). We'll probably want to make this a per-peer adaptive value at some point. */
static const unsigned int BLOCK_DOWNLOAD_WINDOW = 1024;
/** Time to wait (in seconds) between writing blocks/block index to disk. */
static const unsigned int DATABASE_WRITE_INTERVAL = 60 * 60;
/** Time to wait (in seconds) between flushing chainstate to disk. */
static const unsigned int DATABASE_FLUSH_INTERVAL = 24 * 60 * 60;
/** Maximum length of reject messages. */
static const unsigned int MAX_REJECT_MESSAGE_LENGTH = 111;
/** Average delay between local address broadcasts in seconds. */
static const unsigned int AVG_LOCAL_ADDRESS_BROADCAST_INTERVAL = 24 * 24 * 60;
/** Average delay between peer address broadcasts in seconds. */
static const unsigned int AVG_ADDRESS_BROADCAST_INTERVAL = 30;
/** Average delay between trickled inventory broadcasts in seconds.
 *  Blocks, whitelisted receivers, and a random 25% of transactions bypass this. */
static const unsigned int AVG_INVENTORY_BROADCAST_INTERVAL = 5;
/** Block download timeout base, expressed in millionths of the block interval (i.e. 10 min) */
static const int64_t BLOCK_DOWNLOAD_TIMEOUT_BASE = 1000000;
/** Additional block download timeout per parallel downloading peer (i.e. 5 min) */
static const int64_t BLOCK_DOWNLOAD_TIMEOUT_PER_PEER = 500000;

static const unsigned int DEFAULT_LIMITFREERELAY = 15;
static const bool DEFAULT_RELAYPRIORITY = true;

/** Default for -permitbaremultisig */
static const bool DEFAULT_PERMIT_BAREMULTISIG = true;
static const unsigned int DEFAULT_BYTES_PER_SIGOP = 20;
static const bool DEFAULT_CHECKPOINTS_ENABLED = true;
static const bool DEFAULT_TXINDEX = false;
static const unsigned int DEFAULT_BANSCORE_THRESHOLD = 100;

static const bool DEFAULT_TESTSAFEMODE = false;
/** Default for -mempoolreplacement */
static const bool DEFAULT_ENABLE_REPLACEMENT = true;

/** Maximum number of headers to announce when relaying blocks with headers message.*/
static const unsigned int MAX_BLOCKS_TO_ANNOUNCE = 8;

extern CTxMemPool mempool;
extern int nScriptCheckThreads;
extern bool fCheckBlockIndex;
extern bool fCheckpointsEnabled;
extern CFeeRate minRelayTxFee;
extern bool fRequireStandard;
extern unsigned int nBytesPerSigOp;
extern bool fIsBareMultisigStd;
extern bool fAlerts;
extern bool fEnableReplacement;

extern CConditionVariable cvBlockChange;

/** True if we're running in -prune mode. */
extern bool fPruneMode;
/** Number of MiB of block files that we're trying to stay below. */
extern uint64_t nPruneTarget;

/** Block files containing a block-height within MIN_BLOCKS_TO_KEEP of chainActive.Tip() will not be pruned. */
static const unsigned int MIN_BLOCKS_TO_KEEP = 288;

static const signed int DEFAULT_CHECKBLOCKS = MIN_BLOCKS_TO_KEEP;
static const unsigned int DEFAULT_CHECKLEVEL = 3;

// Require that user allocate at least 550MB for block & undo files (blk???.dat and rev???.dat)
// At 1MB per block, 288 blocks = 288MB.
// Add 15% for Undo data = 331MB
// Add 20% for Orphan block rate = 397MB
// We want the low water mark after pruning to be at least 397 MB and since we prune in
// full block file chunks, we need the high water mark which triggers the prune to be
// one 128MB block file + added 15% undo data = 147MB greater for a total of 545MB
// Setting the target to > than 550MB will make it likely we can respect the target.
static const uint64_t MIN_DISK_SPACE_FOR_BLOCK_FILES = 550 * 1024 * 1024;

/** Process protocol messages received from a given node */
bool ProcessMessages(CNode* pfrom);
/**
 * Send queued protocol messages to be sent to a give node.
 *
 * @param[in]   pto             The node which we are sending messages to.
 */
bool SendMessages(CNode* pto);

/** Format a string that describes several potential problems detected by the core.
 * strFor can have three values:
 * - "rpc": get critical warnings, which should put the client in safe mode if non-empty
 * - "statusbar": get all warnings
 * - "gui": get all warnings, translated (where possible) for GUI
 * This function only returns the highest priority warning of the set selected by strFor.
 */
std::string GetWarnings(const std::string& strFor);

#endif // BITCOIN_MAIN_H
