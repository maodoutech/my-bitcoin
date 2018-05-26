#ifndef BITCOIN_HTTPRPC_H
#define BITCOIN_HTTPRPC_H

/** Start HTTP RPC subsystem.
 * Precondition; HTTP and RPC has been started.
 */
bool StartHTTPRPC();

/** Interrupt HTTP RPC subsystem.
 */
void InterruptHTTPRPC();

/** Start HTTP REST subsystem.
 * Precondition; HTTP and RPC has been started.
 */
bool StartREST();

/** Interrupt RPC REST subsystem.
 */
void InterruptREST();
/** Stop HTTP REST subsystem.
 * Precondition; HTTP and RPC has been stopped.
 */
void StopREST();

#endif
