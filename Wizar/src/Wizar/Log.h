#pragma once

#include "Core.h"
//#define FMT_UNICODE
//#define SPDLOG_FMT_EXTERNAL
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Wizar {

	class Wizar_API Log
	{
	public:
		static void Init();
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

#define WZ_CORE_FATAL(...)		::Wizar::Log::GetCoreLogger()->fatal(__VA_ARGS__)
#define WZ_CORE_ERROR(...)		::Wizar::Log::GetCoreLogger()->error(__VA_ARGS__)
#define WZ_CORE_WARN(...)		::Wizar::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define WZ_CORE_INFO(...)		::Wizar::Log::GetCoreLogger()->info(__VA_ARGS__)
#define WZ_CORE_TRACE(...)		::Wizar::Log::GetCoreLogger()->trace(__VA_ARGS__)


#define WZ_FATAL(...)			::Wizar::Log::GetClientLogger()->fatal(__VA_ARGS__)
#define WZ_ERROR(...)			::Wizar::Log::GetClientLogger()->error(__VA_ARGS__)
#define WZ_WARN(...)			::Wizar::Log::GetClientLogger()->warn(__VA_ARGS__)
#define WZ_INFO(...)			::Wizar::Log::GetClientLogger()->info(__VA_ARGS__)
#define WZ_TRACE(...)			::Wizar::Log::GetClientLogger()->trace(__VA_ARGS__)