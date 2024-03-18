//
// Created by jlech on 04/03/2024.
//

#ifndef CLOSING_ASSERT_H
#define CLOSING_ASSERT_H

#include "Logger.h"

#define debugBreak() asm volatile("int $0x03")

class Assert {
public:
    static void that(bool arg, Logger &logger, std::source_location location = std::source_location::current());

    static void that(bool arg, std::source_location location = std::source_location::current() = std::source_location::current());

    static void that(bool arg, Logger &logger, const std::string& msg, std::source_location location = std::source_location::current());

    static void that(bool arg, const std::string &msg, std::source_location location = std::source_location::current());

    template<typename T, typename U>
    static void equals(T arg1, U arg2, Logger &logger, const std::string& msg, const std::source_location location = std::source_location::current()) {
        if (!(arg1 == arg2)) {
            logger.log("Assertion failed: " + msg, LogLevel::error, location);
            debugBreak();
        } else {
            logger.log("Assertion passed", LogLevel::info, location);
        }
    }

    template<typename T, typename U>
    static void equals(T arg1, U arg2, Logger &logger, const std::source_location location = std::source_location::current()) {
        if (!(arg1 == arg2)) {
            logger.log("Assertion failed: Arguments are not equal", LogLevel::error, location);
            debugBreak();
        } else {
            logger.log("Assertion passed", LogLevel::info, location);
        }
    }

    template<typename T, typename U>
    static void equals(T arg1, U arg2, const std::source_location location = std::source_location::current()) {
        if (!(arg1 == arg2)) {
            Logger::error("Assertion failed: Arguments are not equal", location);
            debugBreak();
        } else {
            Logger::info("Assertion passed", location);
        }
    }

    template<typename T, typename U>
    static void equals(T arg1, U arg2, const std::string& msg, const std::source_location location = std::source_location::current()) {
        if (!(arg1 == arg2)) {
            Logger::error("Assertion failed: " + msg, location);
            debugBreak();
        } else {
            Logger::info("Assertion passed", location);
        }
    }

    template<typename T, typename U>
    static void unequals(T arg1, U arg2, Logger &logger, const std::source_location location = std::source_location::current()) {
        if (arg1 == arg2) {
            logger.log("Assertion failed: Arguments are equal", LogLevel::error, location);
            debugBreak();
        } else {
            logger.log("Assertion passed", LogLevel::info, location);
        }
    }

    template<typename T, typename U>
    static void unequals(T arg1, U arg2, Logger &logger, const std::string& msg, const std::source_location location = std::source_location::current()) {
        if (arg1 == arg2) {
            logger.log("Assertion failed: " + msg, LogLevel::error, location);
            debugBreak();
        } else {
            logger.log("Assertion passed", LogLevel::info, location);
        }
    }

    template<typename T, typename U>
    static void unequals(T arg1, U arg2, const std::source_location location = std::source_location::current()) {
        if (arg1 == arg2) {
            Logger::error("Assertion failed: Arguments are equal", location);
            debugBreak();
        } else {
            Logger::info("Assertion passed", location);
        }
    }

    template<typename T, typename U>
    static void unequals(T arg1, U arg2, const std::string& msg, const std::source_location location = std::source_location::current()) {
        if (arg1 == arg2) {
            Logger::error("Assertion failed: " + msg, location);
            debugBreak();
        } else {
            Logger::info("Assertion passed", location);
        }
    }
};


#endif //CLOSING_ASSERT_H
