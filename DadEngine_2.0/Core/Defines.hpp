#ifndef __DEFINES_HPP_
#define __DEFINES_HPP_

// Plateform defines
#if defined (_WIN32) || (_WIN64)
	#define	WINDOWS
	//#define _CRT_SECURE_NO_WARNINGS
	//#define VK_USE_PLATFORM_WIN32_KHR
#elif defined (__APPLE__)
	#define APPLE
#elif defined (__linux__)
#define LINUX
#elif defined (__unix__)
#define UNIX
#else
#define UNKNOW_PLATFORM
#endif

#define FALSE 0
#define TRUE 1

//if(!expr) doesn't work
#define ASSERT(expr)\
	if(!(expr))		\
		throw

#define LOG_ASSERT(expr, msg)	\
	if(!(expr)) {				\
		DadEngine::Core::LogAssert(msg, __FILE__, __LINE__); \
		throw; }
		

#define FORCE_INLINE __forceinline

#endif //__DEFINES_HPP_