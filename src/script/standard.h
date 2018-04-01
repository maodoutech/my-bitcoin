#ifndef BITCOIN_SCRIPT_STANDARD_H
#define BITCOIN_SCRIPT_STANDARD_H

static const bool DEFAULT_ACCEPT_DATACARRIER = true;

static const unsigned int MAX_OP_RETURN_RELAY = 83; //! bytes (+1 for OP_RETURN, +2 for the pushdata opcodes)
extern bool fAcceptDatacarrier;
extern unsigned nMaxDatacarrierBytes;

#endif // BITCOIN_SCRIPT_STANDARD_H
