//
// Created by jlech on 04/03/2024.
//

#ifndef CLOSING_ASSERT_H
#define CLOSING_ASSERT_H

#include "Debugger.h"

#define debugBreak() std::cin.get()

template<typename... Args>
inline void Assert(bool arg, const Message& msg, Args... message)
{
    if (!arg)
    {
        Message msg1("Assertion failed: " + msg.message, msg.location);
        Debug::Error(msg1, std::forward<Args>(message)...);
        debugBreak();
    }
}

template<typename T, typename U, typename... Args>
inline void AssertEquals(T arg1, U arg2, const Message& msg, const Args&... message)
{
    if (!(arg1 == arg2))
    {
        Debug::Error(msg, "Assertion failed: ", std::forward<Args>(message)...);
        debugBreak();
    }
}

template<typename T, typename U, typename... Args>
inline void AssertUnequals(T arg1, U arg2, const Message& msg, const Args&... message)
{
    if (arg1 == arg2)
    {
        Debug::Error(msg, "Assertion failed: ", std::forward<Args>(message)...);
        debugBreak();
    }
}

inline void Assert(bool arg, Logger &logger, std::source_location location = std::source_location::current());

inline void Assert(bool arg, Logger &logger, const std::string& msg, std::source_location location = std::source_location::current());

template<typename T, typename U>
inline void AssertEquals(T arg1, U arg2, Logger &logger, std::source_location location = std::source_location::current())
{
    if (!(arg1 == arg2))
    {
        logger.Log("Assertion failed: Arguments are not equal", LogLevel::error, location);
        debugBreak();
    }
}

template<typename T, typename U>
inline void AssertEquals(T arg1, U arg2, Logger &logger, std::string& msg, const std::source_location location = std::source_location::current())
{
    if (!(arg1 == arg2))
    {
        logger.Log("Assertion failed: " + msg, LogLevel::error, location);
        debugBreak();
    }
}

template<typename T, typename U>
inline void AssertUnequals(T arg1, U arg2, Logger &logger, std::source_location location = std::source_location::current())
{
    if (arg1 == arg2)
    {
        logger.Log("Assertion failed: Arguments are equal", LogLevel::error, location);
        debugBreak();
    }
}

template<typename T, typename U>
inline static void AssertUnequals(T arg1, U arg2, Logger &logger, const std::string& msg, std::source_location location = std::source_location::current())
{
    if (arg1 == arg2)
    {
        logger.Log("Assertion failed: " + msg, LogLevel::error, location);
        debugBreak();
    }
}

#endif //CLOSING_ASSERT_H
