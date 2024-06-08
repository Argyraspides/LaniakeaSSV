#pragma once

#include "BUILD_EMCC.h"

#ifdef BUILD_EMCC
#include <iostream>
#include <emscripten/emscripten.h>
#include <cstdlib>

// This struct is used to store the response from an HTTP request.
// Data is automatically deleted when the struct goes out of scope.
struct ApiResponse
{
    char *data;

    explicit ApiResponse(char *ptr) : data(ptr) {}

    ~ApiResponse()
    {
        if (data)
        {
            free(data);
        }
    }
};

#endif