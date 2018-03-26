#include "clientversion.h"

#include "tinyformat.h"

#include <string>

/**
 * Name of client reported in the 'version' message. Report the same name
 * for both bitcoind and bitcoin-core, to make it harder for attackers to
 * target servers or GUI users specifically.
 */
const std::string CLIENT_NAME("Satoshi");

/**
 * Client version number
 */
#define CLIENT_VERSION_SUFFIX ""
#define BUILD_SUFFIX ""

#define BUILD_DESC_WITH_SUFFIX(maj, min, rev, build, suffix) \
    "v" DO_STRINGIZE(maj) "." DO_STRINGIZE(min) "." DO_STRINGIZE(rev) "." DO_STRINGIZE(build) "-" DO_STRINGIZE(suffix)

#define BUILD_DESC BUILD_DESC_WITH_SUFFIX(CLIENT_VERSION_MAJOR, CLIENT_VERSION_MINOR, CLIENT_VERSION_REVISION, CLIENT_VERSION_BUILD, BUILD_SUFFIX)

#define BUILD_DATE __DATE__ ", " __TIME__

const std::string CLIENT_BUILD(BUILD_DESC CLIENT_VERSION_SUFFIX);
const std::string CLIENT_DATE(BUILD_DATE);

static std::string FormatVersion(int nVersion)
{
    if (nVersion % 100 == 0)
        return strprintf("%d.%d.%d", nVersion / 1000000, (nVersion / 10000) % 100, (nVersion / 100) % 100);
    else
        return strprintf("%d.%d.%d.%d", nVersion / 1000000, (nVersion / 10000) % 100, (nVersion / 100) % 100, nVersion % 100);
}

std::string FormatFullVersion()
{
    return CLIENT_BUILD;
}

/**
 * Format the subversion field according to BIP 14 spec (https://github.com/bitcoin/bips/blob/master/bip-0014.mediawiki)
 */
std::string FormatSubVersion(const std::string& name, int nClientVersion, const std::vector<std::string>& comments)
{
    std::ostringstream ss;
    ss << "/";
    ss << name << ":" << FormatVersion(nClientVersion);
    if (!comments.empty())
    {
        std::vector<std::string>::const_iterator it(comments.begin());
        ss << "(" << *it;
        for(++it; it != comments.end(); ++it)
            ss << "; " << *it;
        ss << ")";
    }
    ss << "/";
    return ss.str();
}
