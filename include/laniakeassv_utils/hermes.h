// File: hermes.h
// This file is part of the Laniakea SSV project.
// It contains utility functions to make GET, POST, and other HTTP requests
#pragma once
#include "BUILD_EMCC.h"

#ifdef BUILD_EMCC
#include <string>
#include <functional>
#include <iostream>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Easy.hpp>
#include <curl/curl.h>
#include <sstream>

namespace Hermes
{

    std::string GET(const std::string &url)
    {
        std::ostringstream response;
        try
        {
            curlpp::Cleanup cleanup;
            curlpp::Easy request;

            request.setOpt(curlpp::options::Url(url));
            request.setOpt(curlpp::options::WriteStream(&response));

            request.perform();
        }
        catch (curlpp::RuntimeError &e)
        {
            std::cerr << "Runtime error: " << e.what() << std::endl;
        }
        catch (curlpp::LogicError &e)
        {
            std::cerr << "Logic error: " << e.what() << std::endl;
        }

        return response.str();
    }
}

#endif