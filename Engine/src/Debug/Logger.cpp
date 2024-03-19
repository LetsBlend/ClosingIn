//
// Created by jlech on 04/03/2024.
//

#include "Logger.h"
#include "Assert.h"
#include "Util/ConsoleColours.h"
#include "EngineTime.h"

Logger::Logger(std::string &&name) {
    this->name = std::move(name);
}

void Logger::Log(const std::string &message, LogLevel level, const std::source_location location) const {
    switch (level)
    {
        case LogLevel::info :
        {
            std::cout << ConsoleColors::WHITE << '[' << EngineTime::time_in_HH_MM_SS_MMM() << "] [" << name << ']';
            std::string temp = location.file_name();
#ifndef DIST
            std::cout << " [" << EraseTill(temp, "src") << " at " << location.line() << "] ";
#endif
            std::cout <<"[INFO]: " << message << ConsoleColors::RESET << '\n';
            break;
        }
        case LogLevel::warn :
        {
            std::cout << ConsoleColors::YELLOW_CUSTOM << '[' << EngineTime::time_in_HH_MM_SS_MMM() << "] [" << name << ']';
            std::string temp = location.file_name();
#ifndef DIST
            std::cout << " [" << EraseTill(temp, "src") << " at " << location.line() << "] ";
#endif
            std::cout << "[WARN]: " << message << ConsoleColors::RESET << '\n';
            break;
        }
        case LogLevel::error :
        {
            std::cout << ConsoleColors::RED_BRIGHT << '[' << EngineTime::time_in_HH_MM_SS_MMM() << "] [" << name << ']';
            std::string temp = location.file_name();
#ifndef DIST
            std::cout  << " [" << EraseTill(temp, "src") << " at " << location.line() << "] ";
#endif
            std::cout << "[ERROR]: " << message << ConsoleColors::RESET << '\n';
            break;
        }
        default :
        {
            this->Log("Invalid argument: Logger level", LogLevel::error);
            debugBreak();
        }
    }
}

