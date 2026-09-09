#pragma once

#include <spdlog/spdlog.h>

#include "common.h"

namespace core {

CORE_API class Log {
  public:
    static void Init();

    inline static std::shared_ptr<spdlog::logger> &GetCoreLogger() {
        return s_coreLogger;
    }
    inline static std::shared_ptr<spdlog::logger> &GetGameLogger() {
        return s_gameLogger;
    }

  private:
    static std::shared_ptr<spdlog::logger> s_coreLogger;
    static std::shared_ptr<spdlog::logger> s_gameLogger;
};

} // namespace core

// macros for logs
#define LOG_CORE_TRACE(...) ::core::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define LOG_CORE_DEBUG(...) ::core::Log::GetCoreLogger()->debug(__VA_ARGS__)
#define LOG_CORE_INFO(...) ::core::Log::GetCoreLogger()->info(__VA_ARGS__)
#define LOG_CORE_WARN(...) ::core::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define LOG_CORE_ERR(...) ::core::Log::GetCoreLogger()->error(__VA_ARGS__)
#define LOG_CORE_CRITICAL(...) ::core::Log::GetCoreLogger()->critical(__VA_ARGS__)

#define LOG_GAME_TRACE(...) ::core::Log::GetGameLogger()->trace(__VA_ARGS__)
#define LOG_GAME_DEBUG(...) ::core::Log::GetGameLogger()->debug(__VA_ARGS__)
#define LOG_GAME_INFO(...) ::core::Log::GetGameLogger()->info(__VA_ARGS__)
#define LOG_GAME_WARN(...) ::core::Log::GetGameLogger()->warn(__VA_ARGS__)
#define LOG_GAME_ERR(...) ::core::Log::GetGameLogger()->error(__VA_ARGS__)
#define LOG_GAME_CRITICAL(...) ::core::Log::GetGameLogger()->critical(__VA_ARGS__)

/* INFO: examples from spdlog/examples.cpp

        spdlog::info("Welcome to spdlog version {}.{}.{}  !", SPDLOG_VER_MAJOR, SPDLOG_VER_MINOR,
                     SPDLOG_VER_PATCH);

        spdlog::warn("Easy padding in numbers like {:08d}", 12);
        spdlog::critical("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
        spdlog::info("Support for floats {:03.2f}", 1.23456);
        spdlog::info("Positional args are {1} {0}..", "too", "supported");
        spdlog::info("{:>8} aligned, {:<8} aligned", "right", "left");

        // Runtime log levels
        spdlog::set_level(spdlog::level::info);  // Set global log level to info
        spdlog::debug("This message should not be displayed!");
        spdlog::set_level(spdlog::level::trace);  // Set specific logger's log level
        spdlog::debug("This message should be displayed..");

        // Customize msg format for all loggers
        spdlog::set_pattern("[%H:%M:%S %z] [%^%L%$] [thread %t] %v");
        spdlog::info("This an info message with custom format");
        spdlog::set_pattern("%+");  // back to default format
        spdlog::set_level(spdlog::level::info);

        // Backtrace support
        // Loggers can store in a ring buffer all messages (including debug/trace) for later
        // inspection. When needed, call dump_backtrace() to see what happened:
        spdlog::enable_backtrace(10);  // create ring buffer with capacity of 10  messages
        for (int i = 0; i < 100; i++) {
            spdlog::debug("Backtrace message {}", i);  // not logged..
        }
        // e.g. if some error happened:
        spdlog::dump_backtrace();  // log them now!
*/
