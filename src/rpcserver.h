#ifndef BITCOIN_RPCSERVER_H
#define BITCOIN_RPCSERVER_H

#include <string>

/**
 * Set the RPC warmup status.  When this is done, all RPC calls will error out
 * immediately with RPC_IN_WARMUP.
 */
void SetRPCWarmupStatus(const std::string& newStatus);

#endif // BITCOIN_RPCSERVER_H
