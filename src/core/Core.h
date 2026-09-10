#pragma once


// DLL export macro - unnecessary for my monolithic game binary
// originally had defined some stuff here as I had remember how we did it
// in hazel series. Ik we shouldnt write a story in comments
// but his is for my rememberanec in future, this isn't a product that i am building
#define CORE_API

#if defined(DEBUG_MODE)
#    define CORE_ENABLE_ASSERTS
#    define CORE_ENABLE_LOGGING
// level 0: TRACE, DEBUG, INFO, WARN, ERR, CRITICAL
#    define CORE_LOG_LEVEL 0

#elif defined(RELEASE_MODE)
#    define CORE_ENABLE_ASSERTS
#    define CORE_ENABLE_LOGGING
// level 2: INFO, WARN, ERR, CRITICAL. strip TRACE and DEBUG
#    define CORE_LOG_LEVEL 2

#elif defined(DIST_MODE)
// strip everything for maximum performance and zero overhead
// keeping critical of cour
#    define CORE_LOG_LEVEL 6
#else
// Fallback default
#    define CORE_ENABLE_ASSERTS
#    define CORE_ENABLE_LOGGING
#    define CORE_LOG_LEVEL 0
#endif

// Debug Break Directive
#if defined(CORE_ENABLE_ASSERTS)
#    if defined(_MSC_VER)
#        define CORE_DEBUGBREAK() __debugbreak()
#    elif defined(__GNUC__) || defined(__clang__)
#        define CORE_DEBUGBREAK() __builtin_trap()
#    else
#        define CORE_DEBUGBREAK()
#    endif

#    define CORE_ASSERT(expr, ...)                                       \
        do {                                                             \
            if (!(expr)) {                                               \
                LOG_CORE_CRITICAL("Assertion Failed: {0}", __VA_ARGS__); \
                CORE_DEBUGBREAK();                                       \
            }                                                            \
        } while (0)
#else
#    define CORE_DEBUGBREAK()
#    define CORE_ASSERT(expr, ...) ((void)0)
#endif
