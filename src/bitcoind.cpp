#include "noui.h"
#include "util.h"

#include <iostream>

bool AppInit(int argc, char* argv[])
{
    std::cout << "AppInit!" << std::endl;
    return true;
}

int main(int argc, char* argv[])
{
    SetupEnvironment();

    // Connect bitcoind signal handlers
    noui_connect();

    return (AppInit(argc, argv) ? 0 : 1);
}
