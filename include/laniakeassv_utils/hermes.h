// File: hermes.h
// This file is part of the Laniakea SSV project.
// It contains functions to make standard HTTP requests in JavaScript through C++

#pragma once
#include "BUILD_EMCC.h"

#ifdef BUILD_EMCC
#include <string>
#include <functional>
#include <emscripten/emscripten.h>
#include <emscripten/val.h>

namespace Hermes
{

    EM_JS(void, GET, (const char* url), {
        return Asyncify.handleAsync(async function() {
            const response = await fetch(UTF8ToString(url));
            const data = await response.json();
            console.log(JSON.stringify(data));
        });
    });

}

#endif