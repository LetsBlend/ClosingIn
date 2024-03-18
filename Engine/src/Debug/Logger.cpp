//
// Created by jlech on 04/03/2024.
//

#include "Logger.h"
#include "Assert.h"
#include "Util/ConsoleColours.h"

Logger::Logger(std::string &&name) {
    this->name = std::move(name);
}

void Logger::log(const std::string &message, LogLevel level, const std::source_location location) const {
    switch (level) {
        case LogLevel::info : {
            std::cout << '[' << time_in_HH_MM_SS_MMM() << "] [" << name << ']';
            std::string temp = location.file_name();
            std::cout << ConsoleColors::WHITE << " [" << Logger::getFileName(temp) << " at " << location.line() << "] [INFO]: " << message << ConsoleColors::RESET << '\n';
            break;
        }
        case LogLevel::warn : {
            std::cout << '[' << time_in_HH_MM_SS_MMM() << "] [" << name << ']';
            std::string temp = location.file_name();
            std::cout << "\033[38;5;221m [" << Logger::getFileName(temp) << " at " << location.line() << "] [WARN]: " << message << ConsoleColors::RESET << '\n';
            break;
        }

        case LogLevel::error : {
            std::cout << '[' << time_in_HH_MM_SS_MMM() << "] [" << name << ']';
            std::string temp = location.file_name();
            std::cout << ConsoleColors::RED_BRIGHT << " [" << Logger::getFileName(temp) << " at " << location.line() << "] [ERROR]: " << message << ConsoleColors::RESET << '\n';
            break;
        }

        default : {
            this->log("Invalid argument: Logger level", LogLevel::error);
            debugBreak();
        }
    }
}

void Logger::info(const std::string &message, const std::source_location location) {
    std::cout << '[' << time_in_HH_MM_SS_MMM() << "] [Default]";
    std::string temp = location.file_name();
    std::cout << ConsoleColors::WHITE << " [" << Logger::getFileName(temp) << " at " << location.line() << "] [INFO]: " << message << ConsoleColors::RESET << '\n';
}

void Logger::warn(const std::string &message, const std::source_location location) {
    std::cout << '[' << time_in_HH_MM_SS_MMM() << "] [Default]";
    std::string temp = location.file_name();
    std::cout << "\033[38;5;221m [" << Logger::getFileName(temp) << " at " << location.line() << "] [WARN]: " << message << ConsoleColors::RESET << '\n';
}

void Logger::error(const std::string &message, const std::source_location location) {
    std::cout << '[' << time_in_HH_MM_SS_MMM() << "] [Default]";
    std::string temp = location.file_name();
    std::cout << ConsoleColors::RED_BRIGHT << " [" << Logger::getFileName(temp) << " at " << location.line() << "] [ERROR]: " << message << ConsoleColors::RESET << '\n';
}

std::string Logger::getFileName(std::string& fullPath) {
    std::reverse(fullPath.begin(), fullPath.end());
    auto it = fullPath.end() - fullPath.find('\\');
    std::reverse(fullPath.begin(), fullPath.end());
    fullPath.erase(fullPath.begin(), it);
    return fullPath;
}

std::string Logger::time_in_HH_MM_SS_MMM() {
    /*
     * using namespace std::chrono;
     * // get current time
     * auto now = system_clock::now();
     * // get number of milliseconds for the current second
     * // (remainder after division into seconds)
     * auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;
     * // convert to std::time_t in order to convert to std::tm (broken time)
     * auto timer = system_clock::to_time_t(now);
     * // convert to broken time
     * std::tm bt = *std::localtime(&timer);
     * std::ostringstream oss;
     * oss << std::put_time(&bt, "%H:%M:%S"); // HH:MM:SS
     * oss << '.' << std::setfill('0') << std::setw(3) << ms.count();
     * return oss.str();
     */
    using namespace std::chrono;
    auto now = system_clock::now();
    auto timer = system_clock::to_time_t(now);
    std::tm bt = *std::localtime(&timer);
    std::ostringstream oss; //TODO remove stream
    oss << std::put_time(&bt, "%H:%M:%S"); // HH:MM:SS
    return oss.str();
}