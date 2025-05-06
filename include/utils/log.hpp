#pragma once
#include <iostream>
#include <chrono>
#include <iomanip>
#include <ctime>

enum class LogLevel { INFO, WARN, ERROR };

inline void log(LogLevel level, const std::string& message) {
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::string levelStr;
    switch (level) {
        case LogLevel::INFO: levelStr = "INFO"; break;
        case LogLevel::WARN: levelStr = "WARN"; break;
        case LogLevel::ERROR: levelStr = "ERROR"; break;
    }

    std::cout << "[" << std::put_time(std::localtime(&t), "%F %T") << "] "
              << "[" << levelStr << "] " << message << std::endl;
}
