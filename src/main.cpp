#include "main.h"

#include "amount.h"
#include "clientversion.h"
#include "txmempool.h"
#include "util.h"


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

CConditionVariable cvBlockChange;

// requires LOCK(cs_vRecvMsg)
bool ProcessMessages(CNode* pfrom)
{
    (void) pfrom;
    return true;
}

bool SendMessages(CNode* pto)
{
    (void) pto;
    return true;
}


bool fLargeWorkForkFound = false;
bool fLargeWorkInvalidChainFound = false;

//////////////////////////////////////////////////////////////////////////////
//
// CAlert
//

std::string GetWarnings(const std::string& strFor)
{
    int nPriority = 0;
    string strStatusBar;
    string strRPC;
    string strGUI;

    if (!CLIENT_VERSION_IS_RELEASE) {
        strStatusBar = "This is a pre-release test build - use at your own risk - do not use for mining or merchant applications";
        strGUI = "This is a pre-release test build - use at your own risk - do not use for mining or merchant applications";
    }

    if (GetBoolArg("-testsafemode", DEFAULT_TESTSAFEMODE))
        strStatusBar = strRPC = strGUI = "testsafemode enabled";

    // Misc warnings like out of disk space and clock is wrong
    if (strMiscWarning != "")
    {
        nPriority = 1000;
        strStatusBar = strGUI = strMiscWarning;
    }

    if (fLargeWorkForkFound)
    {
        nPriority = 2000;
        strStatusBar = strRPC = "Warning: The network does not appear to fully agree! Some miners appear to be experiencing issues.";
        strGUI = "Warning: The network does not appear to fully agree! Some miners appear to be experiencing issues.";
    }
    else if (fLargeWorkInvalidChainFound)
    {
        nPriority = 2000;
        strStatusBar = strRPC = "Warning: We do not appear to fully agree with our peers! You may need to upgrade, or other nodes may need to upgrade.";
        strGUI = "Warning: We do not appear to fully agree with our peers! You may need to upgrade, or other nodes may need to upgrade.";
    }

    // Alerts
    {
        /*
        LOCK(cs_mapAlerts);
        BOOST_FOREACH(PAIRTYPE(const uint256, CAlert)& item, mapAlerts)
        {
            const CAlert& alert = item.second;
            if (alert.AppliesToMe() && alert.nPriority > nPriority)
            {
                nPriority = alert.nPriority;
                strStatusBar = strGUI = alert.strStatusBar;
            }
        }
        */
    }

    if (strFor == "gui")
        return strGUI;
    else if (strFor == "statusbar")
        return strStatusBar;
    else if (strFor == "rpc")
        return strRPC;
    assert(!"GetWarnings(): invalid parameter");
    return "error";
}
