#pragma once

#include <memory>

#ifdef WZ_PLATFORM_WINDOWS
#if WZ_DDYNAMIC_LINK
	#ifdef WZ_BUILD_DLL
		#define WIZAR_API __declspec(dllexport)
		#else
		#define WIZAR_API __declspec(dllimport)
	#endif
#else 
	#define WIZAR_API
#endif
	#else
		#error Wizar only support Windows!
#endif

#ifdef WZ_DEBUG
#define WZ_ENABLE_ASSERTS
#endif

#ifdef WZ_ENABLE_ASSERTS
#define WZ_ASSERT(x,...) { if(!(x)){WZ_ERROR("Assertion Failed :{0}",__VA_ARGS__);__debugbreak();}}
#define WZ_CORE_ASSERT(x,...) { if(!(x)){WZ_CORE_ERROR("Assertion Failed :{0}",__VA_ARGS__);__debugbreak();}}
#else
#define WZ_ASSERT(x,...)  
#define WZ_CORE_ASSERT(x,...) 
#endif

#define BIT(x)  (1 << x)

//ռλ�� `_1` ��ʾ������������󶨺���ʱ��`x` �����ĵ�һ���������ɵ����ߴ��롣
#define WZ_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
namespace Wizar{

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;

}
