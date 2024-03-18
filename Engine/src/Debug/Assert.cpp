//
// Created by jlech on 04/03/2024.
//

#include "Assert.h"
#include "Logger.h"

#ifndef DIST

void Assert::that(bool arg, Logger &logger, const std::source_location location) {
    if (!arg) {
        logger.log("Assertion failed: Argument was false", LogLevel::error, location);
        debugBreak();
    } else {
        logger.log("Assertion passed", LogLevel::info, location);
    }
}

void Assert::that(bool arg, Logger &logger, const std::string& msg, const std::source_location location) {
    if (!arg) {
        logger.log("Assertion failed: " + msg, LogLevel::error, location);
        debugBreak();
    } else {
        logger.log("Assertion passed", LogLevel::info, location);
    }
}

void Assert::that(bool arg, const std::source_location location) {
    if (!arg) {
        Logger::error("Assertion failed: Argument was false", location);
        debugBreak();
    } else {
        Logger::info("Assertion passed", location);
    }
}

void Assert::that(bool arg, const std::string& msg, const std::source_location location) {
    if (!arg) {
        Logger::error("Assertion failed: " + msg, location);
        debugBreak();
    } else {
        Logger::info("Assertion passed", location);
    }
}

#endif
