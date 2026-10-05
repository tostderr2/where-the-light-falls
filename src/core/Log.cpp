#include "Log.h"

#include <spdlog/async.h>
#include <spdlog/sinks/null_sink.h> // Added for clean zero-op fallback
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Core {

std::shared_ptr<spdlog::logger> Log::s_coreLogger;
std::shared_ptr<spdlog::logger> Log::s_gameLogger;

void Log::Init() {

#if defined(DIST_MODE)
/*
// a lightweight file logger active ONLY for fatal engine crashes:
auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
    "logs/crash.log", 1024 * 1024 * 2, 1, false
);
file_sink->set_pattern("[%Y-%m-%d %H:%M:%S] [%n] [%l]: %v");

s_coreLogger = std::make_shared<spdlog::logger>("CORE", file_sink);
s_gameLogger = std::make_shared<spdlog::logger>("GAME", file_sink);

s_coreLogger->set_level(spdlog::level::critical);
s_gameLogger->set_level(spdlog::level::critical);

spdlog::register_logger(s_coreLogger);
spdlog::register_logger(s_gameLogger);
return;
*/
#endif

    // DEBUG / RELEASE: Full Async Engine Pipeline
    spdlog::init_thread_pool(8192, 1);

    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_pattern("%^[%T.%e] [T:%t] [%n] [%s:%#]: %v%$");

    auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
        "logs/game.log", 1024 * 1024 * 5, 3, false);
    file_sink->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [T:%t] [%n] [%l] [%s:%#]: %v");

    std::vector<spdlog::sink_ptr> sinks{console_sink, file_sink};

    s_coreLogger = std::make_shared<spdlog::async_logger>(
        "CORE", sinks.begin(), sinks.end(), spdlog::thread_pool(),
        spdlog::async_overflow_policy::overrun_oldest);
    s_coreLogger->set_level(spdlog::level::trace);

#if defined(DEBUG_MODE)
    s_coreLogger->flush_on(spdlog::level::trace);
#else
    s_coreLogger->flush_on(spdlog::level::info);
#endif
    spdlog::register_logger(s_coreLogger);

    s_gameLogger = std::make_shared<spdlog::async_logger>(
        "GAME", sinks.begin(), sinks.end(), spdlog::thread_pool(),
        spdlog::async_overflow_policy::overrun_oldest);
    s_gameLogger->set_level(spdlog::level::trace);

#if defined(DEBUG_MODE)
    s_gameLogger->flush_on(spdlog::level::trace);
#else
    s_gameLogger->flush_on(spdlog::level::info);
#endif
    spdlog::register_logger(s_gameLogger);

    LOG_CORE_INFO("=====================================================");
    LOG_CORE_INFO("  ENGINE INITIALIZED SYSTEM PROFILE: Build [{}]", CORE_BUILD_NAME);
    LOG_CORE_INFO("=====================================================");
}

void Log::Shutdown() {
    // Safely check for pointers to avoid dropping errors on exit
    if (s_coreLogger)
        s_coreLogger->flush();
    if (s_gameLogger)
        s_gameLogger->flush();

#if !defined(DIST_MODE)
    // Only shut down the global thread pool if it was actually initialized
    spdlog::shutdown();
#endif
}

} // namespace Core
