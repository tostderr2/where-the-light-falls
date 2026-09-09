#include "Log.h"
#include <spdlog/sinks/stdout_color_sinks-inl.h>

namespace core {
std::shared_ptr<spdlog::logger> Log::s_coreLogger;
std::shared_ptr<spdlog::logger> Log::s_gameLogger;

void Log::Init() {
	spdlog::set_pattern("%^[%T] %n: %v%$");

	s_coreLogger = spdlog::stdout_color_mt("_CORE");
	s_coreLogger->set_level(spdlog::level::trace);

	s_gameLogger = spdlog::stdout_color_mt("GAME");
	s_gameLogger->set_level(spdlog::level::trace);
}

} // namespace core
