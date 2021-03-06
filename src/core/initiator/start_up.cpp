﻿/*********************************************************************************
*  Copyright (c) 2017-2018 DeepBrainChain core team
*  Distributed under the MIT software license, see the accompanying
*  file COPYING or http://www.opensource.org/licenses/mit-license.php
* file name        :   start_up.cpp
* description    :   core start up
* date                  : 2017.01.23
* author            :   Bruce Feng
**********************************************************************************/
#include "start_up.h"
#include <memory>
#include "server.h"


#if defined(WIN32) || defined(__linux__) || defined(MAC_OSX)


int main_task(int argc, char* argv[])
{
    int result = g_server->init(argc, argv);
    if (E_SUCCESS != result)
    {
        LOG_ERROR << "server init exited, error code: " << result;
        g_server->exit();

        return result;
    }

    g_server->idle();
    LOG_INFO << "dbc start to exit...";
    g_server->exit();

    LOG_DEBUG << "------dbc shut down------";

    return E_SUCCESS;
}


#else       //not support yet


#endif


