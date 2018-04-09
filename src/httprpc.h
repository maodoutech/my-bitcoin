#ifndef BITCOIN_HTTPRPC_H
#define BITCOIN_HTTPRPC_H

/** Start HTTP RPC subsystem.
 * Precondition; HTTP and RPC has been started.
 */
bool StartHTTPRPC();

/** Start HTTP REST subsystem.
 * Precondition; HTTP and RPC has been started.
 */
bool StartREST();

#endif
