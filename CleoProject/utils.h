#pragma once

#include <mod/amlmod.h>
#include <mod/logger.h>
#include <mod/config.h>

#include <string>

#include "Log.h"

template <typename T>
static T* LoadInterface(T** out, std::string name)
{
    Log::Level(eLogLevel::LOG_BOTH) << "Loading interface: " << name << "..." << std::endl;

    void* interface = GetInterface(name.c_str());

    Log::Level(eLogLevel::LOG_BOTH) << "Interface: " << interface << std::endl;

    *out = static_cast<T*>(interface);

    if (*out) Log::Level(eLogLevel::LOG_BOTH) << name << " loaded" << std::endl;
    else Log::Level(eLogLevel::LOG_BOTH) << name << " was not loaded" << std::endl;

    return *out;
}