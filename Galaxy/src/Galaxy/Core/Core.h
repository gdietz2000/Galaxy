#pragma once

#include <memory>

#ifdef _WIN32
	#ifdef _WIN64
		#ifndef GX_PLATFORM_WINDOWS
			#define GX_PLATFORM_WINDOWS
		#endif	
	#elif
		#error Galaxy does not support Win32!
	#endif
	#else
		#error We dont support anything else!
#endif

#ifdef GX_DEBUG
#define GX_ENABLE_ASSERTS
#endif

#ifdef GX_ENABLE_ASSERTS
	#define GX_ASSERT(x, ...) { if(!(x)) { GX_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define GX_CORE_ASSERT(x, ...) { if(!(x)) { GX_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define GX_ASSERT(x, ...)
	#define GX_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define PRINT_EVENT(x) x.ToString()

#define GX_BIND(x) std::bind(&x, this, std::placeholders::_1)

namespace Galaxy
{
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}