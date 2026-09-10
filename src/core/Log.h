#pragma once

#include <spdlog/spdlog.h>

#include "Core.h"

namespace core {

class Log {
  public:
    static void Init();
    static void Shutdown();

    static std::shared_ptr<spdlog::logger> &GetCoreLogger() {
        return s_coreLogger;
    }
    static std::shared_ptr<spdlog::logger> &GetGameLogger() {
        return s_gameLogger;
    }

  private:
    static std::shared_ptr<spdlog::logger> s_coreLogger;
    static std::shared_ptr<spdlog::logger> s_gameLogger;
};

} // namespace core

// Helper macro for source location
#define CORE_LOG_CALL(logger, level, ...) \
    logger->log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, level, __VA_ARGS__)

// -------------------------------
// Core Logger Macros
// -------------------------------
#if (CORE_LOG_LEVEL <= 0)
#    define LOG_CORE_TRACE(...) \
        CORE_LOG_CALL(::core::Log::GetCoreLogger(), spdlog::level::trace, __VA_ARGS__)
#else
#    define LOG_CORE_TRACE(...) ((void)0)
#endif

#if (CORE_LOG_LEVEL <= 1)
#    define LOG_CORE_DEBUG(...) \
        CORE_LOG_CALL(::core::Log::GetCoreLogger(), spdlog::level::debug, __VA_ARGS__)
#else
#    define LOG_CORE_DEBUG(...) ((void)0)
#endif

#if (CORE_LOG_LEVEL <= 2)
#    define LOG_CORE_INFO(...) \
        CORE_LOG_CALL(::core::Log::GetCoreLogger(), spdlog::level::info, __VA_ARGS__)
#else
#    define LOG_CORE_INFO(...) ((void)0)
#endif

#if (CORE_LOG_LEVEL <= 3)
#    define LOG_CORE_WARN(...) \
        CORE_LOG_CALL(::core::Log::GetCoreLogger(), spdlog::level::warn, __VA_ARGS__)
#else
#    define LOG_CORE_WARN(...) ((void)0)
#endif

#if (CORE_LOG_LEVEL <= 4)
#    define LOG_CORE_ERR(...) \
        CORE_LOG_CALL(::core::Log::GetCoreLogger(), spdlog::level::err, __VA_ARGS__)
#else
#    define LOG_CORE_ERR(...) ((void)0)
#endif

// #if (CORE_LOG_LEVEL <= 5)
#define LOG_CORE_CRITICAL(...) \
    CORE_LOG_CALL(::core::Log::GetCoreLogger(), spdlog::level::critical, __VA_ARGS__)
// #else
//     #define LOG_CORE_CRITICAL(...) ((void)0)
// #endif

// -------------------------------
// Game Logger Macros
// -------------------------------
#if (CORE_LOG_LEVEL <= 0)
#    define LOG_GAME_TRACE(...) \
        CORE_LOG_CALL(::core::Log::GetGameLogger(), spdlog::level::trace, __VA_ARGS__)
#else
#    define LOG_GAME_TRACE(...) ((void)0)
#endif

#if (CORE_LOG_LEVEL <= 1)
#    define LOG_GAME_DEBUG(...) \
        CORE_LOG_CALL(::core::Log::GetGameLogger(), spdlog::level::debug, __VA_ARGS__)
#else
#    define LOG_GAME_DEBUG(...) ((void)0)
#endif

#if (CORE_LOG_LEVEL <= 2)
#    define LOG_GAME_INFO(...) \
        CORE_LOG_CALL(::core::Log::GetGameLogger(), spdlog::level::info, __VA_ARGS__)
#else
#    define LOG_GAME_INFO(...) ((void)0)
#endif

#if (CORE_LOG_LEVEL <= 3)
#    define LOG_GAME_WARN(...) \
        CORE_LOG_CALL(::core::Log::GetGameLogger(), spdlog::level::warn, __VA_ARGS__)
#else
#    define LOG_GAME_WARN(...) ((void)0)
#endif

#if (CORE_LOG_LEVEL <= 4)
#    define LOG_GAME_ERR(...) \
        CORE_LOG_CALL(::core::Log::GetGameLogger(), spdlog::level::err, __VA_ARGS__)
#else
#    define LOG_GAME_ERR(...) ((void)0)
#endif

// #if (CORE_LOG_LEVEL <= 5)
#define LOG_GAME_CRITICAL(...) \
    CORE_LOG_CALL(::core::Log::GetGameLogger(), spdlog::level::critical, __VA_ARGS__)
// #else
//     #define LOG_GAME_CRITICAL(...) ((void)0)
// #endif
