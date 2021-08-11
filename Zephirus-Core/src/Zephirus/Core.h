#pragma once

#ifdef ZPH_PLATFORM_WINDOWS
	#ifdef ZPH_BUILD_DLL
		#define ZPH_API __declspec(dllexport)
	#else
		#define ZPH_API __declspec(dllimport)
	#endif
#else
	#error Zephirus only support Windows !
#endif

#define BIT(x) (1 << x)