#include "Log.h"

#include <spdlog/async.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Core {

std::shared_ptr<spdlog::logger> Log::s_coreLogger;
std::shared_ptr<spdlog::logger> Log::s_gameLogger;

void Log::Init() {
    // queue size 8192 items, 1 background thread
    spdlog::init_thread_pool(8192, 1);

    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_st>();

    // Pattern breakdown:
    // %^     : Start color range
    // [%T.%e]: Time with milliseconds HH:MM:SS.ms
    // [%t]   : Thread ID
    // %n     : Logger name
    // %s:%#  : Short source filename and line number
    // %v     : Message
    // %$     : End color range
    console_sink->set_pattern("%^[%T.%e] [T:%t] [%n] [%s:%#]: %v%$");

    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_st>("logs/game.log", true);
    file_sink->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [T:%t] [%n] [%l] [%s:%#]: %v");

    std::vector<spdlog::sink_ptr> sinks{console_sink, file_sink};

    //  async loggers with non-blocking overrun policy
    s_coreLogger = std::make_shared<spdlog::async_logger>(
        "CORE", sinks.begin(), sinks.end(), spdlog::thread_pool(),
        spdlog::async_overflow_policy::overrun_oldest);
    s_coreLogger->set_level(spdlog::level::trace);
    s_coreLogger->flush_on(spdlog::level::err);
    spdlog::register_logger(s_coreLogger);

    s_gameLogger = std::make_shared<spdlog::async_logger>(
        "GAME", sinks.begin(), sinks.end(), spdlog::thread_pool(),
        spdlog::async_overflow_policy::overrun_oldest);
    s_gameLogger->set_level(spdlog::level::trace);
    s_gameLogger->flush_on(spdlog::level::err);
    spdlog::register_logger(s_gameLogger);
}

void Log::Shutdown() {
    spdlog::shutdown();
}

} // namespace Core
