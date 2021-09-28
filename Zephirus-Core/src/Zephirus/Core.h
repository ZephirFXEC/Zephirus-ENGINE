#pragma once
#include <memory>

#ifdef ZPH_PLATFORM_WINDOWS
#if ZPH_DYNAMIC_LINK
	#ifdef ZPH_BUILD_DLL
		#define ZPH_API __declspec(dllexport)
	#else
		#define ZPH_API __declspec(dllimport)
	#endif
#else
	#define ZPH_API
#endif
#else
	#error Zephirus only support Windows !
#endif

#ifdef ZPH_DEBUG
	#define  ZPH_ENABLE_ASSERT
#endif

#ifdef HZ_ENABLE_ASSERTS
	#define ZPH_ASSERT(x, ...) { if(!(x)) { HZ_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define ZPH_CORE_ASSERT(x, ...) { if(!(x)) { HZ_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define ZPH_ASSERT(x, ...)
	#define ZPH_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define ZPH_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace ZPH
{
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
}