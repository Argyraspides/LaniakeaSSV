// File: hermes.h
// This file is part of the Laniakea SSV project.
// It contains utility functions to make GET, POST, and other HTTP requests
#pragma once
#include "BUILD_EMCC.h"

#ifdef BUILD_EMCC
#include <string>
#include <functional>
#include <iostream>
#include <sstream>

namespace Hermes
{

    std::string GET(const std::string &url)
    {
        
    }
}

#endif