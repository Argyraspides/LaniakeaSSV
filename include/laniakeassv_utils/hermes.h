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
#include "api_response.h"

namespace Hermes
{

    EM_JS(char *, EM_JS_GET, (const char *url), {
        return Asyncify.handleAsync(async function() {
            
            const response = await fetch(UTF8ToString(url));
            const data = await response.json();
            const jsonString = JSON.stringify(data);

            // JS and C++ represent strings differently, so we need to convert the string to a format that C++ can understand.
            // _malloc() allocates memory on the WASM heap, and stringToUTF8() copies the string to that memory.
            const lengthBytes = lengthBytesUTF8(jsonString) + 1;

            // Malloc MUST be freed. This is done through the ApiResponse destructor.
            const stringOnWasmHeap = _malloc(lengthBytes);
            stringToUTF8(jsonString, stringOnWasmHeap, lengthBytes);

            return stringOnWasmHeap;
        });
    });

    EM_JS(char *, EM_JS_POST, (const char *url, const char *reqBody), {
        return Asyncify.handleAsync(async function() {


            const urlString = UTF8ToString(url);
            const reqBodyString = UTF8ToString(reqBody);


            const response = await fetch(urlString, {
                method: 'POST',
                body: reqBodyString,
                headers: {
                    'Content-Type': 'application/json'
                }
            });
            const data = await response.json();
            const jsonString = JSON.stringify(data);

            // JS and C++ represent strings differently, so we need to convert the string to a format that C++ can understand.
            // _malloc() allocates memory on the WASM heap, and stringToUTF8() copies the string to that memory.
            const lengthBytes = lengthBytesUTF8(jsonString) + 1;

            // Malloc MUST be freed. This is done through the ApiResponse destructor.
            const stringOnWasmHeap = _malloc(lengthBytes);
            stringToUTF8(jsonString, stringOnWasmHeap, lengthBytes);

            return stringOnWasmHeap;
        });
    });


    ApiResponse GET(const char *url)
    {
        return ApiResponse(EM_JS_GET(url));
    }

    ApiResponse POST(const char *url, const char *data = "{}")
    {
        return ApiResponse(EM_JS_POST(url, data));
    }

}

#endif