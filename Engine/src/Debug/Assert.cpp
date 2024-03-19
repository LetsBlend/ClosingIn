//
// Created by jlech on 04/03/2024.
//

#include "Assert.h"
#include "Logger.h"

#ifndef DIST

void Assert(bool arg, Logger &logger, const std::source_location location)
{
    if (!arg)
    {
        logger.Log("Assertion failed: Argument was false", LogLevel::error, location);
        debugBreak();
    }
}

void Assert(bool arg, Logger &logger, const std::string& msg, const std::source_location location)
{
    if (!arg)
    {
        logger.Log("Assertion failed: " + msg, LogLevel::error, location);
        debugBreak();
    }
}

#endif
