//
// Created by jlech on 04/03/2024.
//

#ifndef CLOSING_LOGGER_H
#define CLOSING_LOGGER_H

enum class LogLevel
{
    info, warn, error
};

class Logger
{
public:
    explicit Logger(std::string &&name);

    void Log(const std::string &message, LogLevel level, std::source_location location = std::source_location::current()) const;

private:
    std::string name;
    inline static LogLevel logLevel = LogLevel::info;
};

#endif //CLOSING_LOGGER_H
