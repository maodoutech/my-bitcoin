#include "net.h"

#include "chain.h"
#include "main.h"
#include "sync.h"

/**
 * Global state
 */

CCriticalSection cs_main;

CChain chainActive;

int nMaxConnections = DEFAULT_MAX_PEER_CONNECTIONS;

uint64_t nLocalServices = NODE_NETWORK;

// Signals for message handling
static CNodeSignals g_signals;
CNodeSignals& GetNodeSignals() { return g_signals; }

int GetHeight()
{
    LOCK(cs_main);
    return chainActive.Height();
}

void InitializeNode(NodeId nodeid, const CNode *pnode) {
    (void) nodeid;
    (void) pnode;
}

void FinalizeNode(NodeId nodeid) {
    (void) nodeid;
}

void RegisterNodeSignals(CNodeSignals& nodeSignals)
{
    nodeSignals.GetHeight.connect(&GetHeight);
    nodeSignals.ProcessMessages.connect(&ProcessMessages);
    nodeSignals.SendMessages.connect(&SendMessages);
    nodeSignals.InitializeNode.connect(&InitializeNode);
    nodeSignals.FinalizeNode.connect(&FinalizeNode);
}
