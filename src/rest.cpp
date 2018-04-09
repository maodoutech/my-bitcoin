#include "httpserver.h"
#include "utilstrencodings.h"
#include "rpcprotocol.h"

static bool rest_tx(HTTPRequest* req, const std::string& strURIPart)
{
    (void) strURIPart;
    req->WriteHeader("Content-Type", "application/json");
    req->WriteReply(HTTP_OK, "{'rest_tx' : 'data'}");
    return true;
}

static const struct {
    const char* prefix;
    bool (*handler)(HTTPRequest* req, const std::string& strReq);
} uri_prefixes[] = {
    {"/rest/tx/", rest_tx}
};

bool StartREST()
{
    for (unsigned int i = 0; i < ARRAYLEN(uri_prefixes); i++)
        RegisterHTTPHandler(uri_prefixes[i].prefix, false, uri_prefixes[i].handler);
    return true;
}
