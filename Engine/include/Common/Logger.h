#pragma once

#include "Core.h"

// #############################
// logging
// spdlog
#ifdef CEDAR_ENABLE_LOG
// TODO: These two defines causes linker errors that by saying dublicating
// external symbols so they are uncommented for now
//  #define FMT_HEADER_ONLY
//  #define SPDLOG_FMT_EXTERNAL
	#include <spdlog/sinks/stdout_color_sinks.h>
	#include <spdlog/spdlog.h>
// #include <spdlog/fmt/ostr.h>
namespace cedar
{
	class Logger
	{
	public:
		using SPDLog = std::shared_ptr<spdlog::logger>;

		static SPDLog& Ref()
		{
			static Logger logger {};

			return logger.m_SPD;
		}

		CEDAR_API Logger()
		{
			m_SPD = spdlog::stdout_color_mt("stdout");
			spdlog::set_default_logger(m_SPD);
			spdlog::set_level(spdlog::level::trace);
			spdlog::set_pattern("%^[%T]: [#%t] %v%$");
		}

	private:
		SPDLog m_SPD;
	};
} // namespace CEDAR

// logging macros
	#define CEDAR_TRACE(...) cedar::Logger::Ref()->trace(__VA_ARGS__)
/*  Logs debug message to the console
    To pass arguments use the format "Argument: {}, arg"
*/
	#define CEDAR_DEBUG(...) cedar::Logger::Ref()->debug(__VA_ARGS__)
	#define CEDAR_INFO(...) cedar::Logger::Ref()->info(__VA_ARGS__)
	#define CEDAR_WARN(...) cedar::Logger::Ref()->warn(__VA_ARGS__)
	#define CEDAR_ERROR(...) cedar::Logger::Ref()->error(__VA_ARGS__)
	#define CEDAR_FATAL(...)                                                                    \
		cedar::Logger::Ref()->critical(__VA_ARGS__);                                            \
		cedar::Logger::Ref()->critical("in function: {}, at Line: {}", __FUNCTION__, __LINE__); \
		exit(EXIT_FAILURE)

#else
	#define CEDAR_TRACE
	#define CEDAR_DEBUG
	#define CEDAR_INFO
	#define CEDAR_WARN
	#define CEDAR_ERROR
	#define CEDAR_FATAL
#endif