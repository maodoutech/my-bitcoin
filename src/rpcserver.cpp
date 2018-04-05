#include "rpcserver.h"

#include "sync.h"

static CCriticalSection cs_rpcWarmup;
static std::string rpcWarmupStatus("RPC server started");

void SetRPCWarmupStatus(const std::string& newStatus)
{
    LOCK(cs_rpcWarmup);
    rpcWarmupStatus = newStatus;
}
