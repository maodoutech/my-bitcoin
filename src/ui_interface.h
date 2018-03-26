#ifndef BITCOIN_UI_INTERFACE_H
#define BITCOIN_UI_INTERFACE_H

#include <stdint.h>
#include <string>

#include <boost/signals2/last_value.hpp>
#include <boost/signals2/signal.hpp>

/** Signals for UI communication. */
class CClientUIInterface
{
public:
    /** Show message box. */
    boost::signals2::signal<bool (const std::string& message, const std::string& caption, unsigned int style), boost::signals2::last_value<bool> > ThreadSafeMessageBox;

    /** Progress message during initialization. */
    boost::signals2::signal<void (const std::string &message)> InitMessage;
};

extern CClientUIInterface uiInterface;

#endif // BITCOIN_UI_INTERFACE_H
