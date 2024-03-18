//
// Created by jlech on 04/03/2024.
//

#ifndef CLOSING_LOGGER_H
#define CLOSING_LOGGER_H

enum class LogLevel{
    info, warn, error
};

class Logger {
private:
    std::string name;

public:
    explicit Logger(std::string &&name);

    void log(const std::string &message, LogLevel level, const std::source_location location = std::source_location::current()) const;

    static void warn(const std::string &message, const std::source_location location = std::source_location::current());

    static void info(const std::string &message, const std::source_location location = std::source_location::current());

    static void error(const std::string &message, const std::source_location location = std::source_location::current());


    static std::string time_in_HH_MM_SS_MMM();

    inline static LogLevel logLevel = LogLevel::info;

    static std::string getFileName(std::string &fullPath);
};


#endif //CLOSING_LOGGER_H
