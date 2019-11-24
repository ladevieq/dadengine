#ifndef __DEFINES_HPP_
#define __DEFINES_HPP_

// Compiler defines
#if defined(_MSC_VER)
#define FORCE_INLINE __forceinline
#elif defined(__GNUG__)
#define FORCE_INLINE __attribute__((always_inline))
#elif defined(__clang__)
#define FORCE_INLINE __forceinline
#endif

// Plateform defines
#if defined(_WIN32) || defined(_WIN64)
#define WINDOWS
//#define _CRT_SECURE_NO_WARNINGS
#elif defined(__APPLE__)
#define APPLE
#elif defined(__linux__)
#define LINUX
#elif defined(__unix__)
#define UNIX
#else
#define UNKNOW_PLATFORM
#endif

#endif //__DEFINES_HPP_

