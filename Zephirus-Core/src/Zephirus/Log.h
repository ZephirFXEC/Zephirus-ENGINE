#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace ZPH {

	class ZPH_API Log {
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }


	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}


//Core log macros
#define ZPH_CORE_ERROR(...) ::ZPH::Log::GetCoreLogger()->error(__VA_ARGS__)
#define ZPH_CORE_TRACE(...) ::ZPH::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define ZPH_CORE_WARN(...)  ::ZPH::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ZPH_CORE_INFO(...)  ::ZPH::Log::GetCoreLogger()->info(__VA_ARGS__)
#define ZPH_CORE_FATAL(...) ::ZPH::Log::GetCoreLogger()->critical(__VA_ARGS__)


//Client log macros

#define ZPH_ERROR(...) ::ZPH::Log::GetClientLogger()->error(__VA_ARGS__)
#define ZPH_TRACE(...) ::ZPH::Log::GetClientLogger()->trace(__VA_ARGS__)
#define ZPH_WARN(...)  ::ZPH::Log::GetClientLogger()->warn(__VA_ARGS__)
#define ZPH_INFO(...)  ::ZPH::Log::GetClientLogger()->info(__VA_ARGS__)
#define ZPH_FATAL(...) ::ZPH::Log::GetClientLogger()->critical(__VA_ARGS__)