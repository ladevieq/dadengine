#ifndef __WINDOWS_TIMERS_HPP_
#define __WINDOWS_TIMERS_HPP_

#include <Windows.h>
#include <stdio.h>

namespace DadEngine::Core
{
	class WindowsTimer
	{
	public:

		WindowsTimer() = default;
		~WindowsTimer() = default;

		FORCE_INLINE void Start()
		{
			QueryPerformanceCounter(&m_StartTime);
			QueryPerformanceFrequency(&m_Frequency);
		}

		FORCE_INLINE void Stop()
		{
			
		}

		FORCE_INLINE void Reset()
		{
			Start();
		}

		FORCE_INLINE uint64 GetSeconds()
		{
			LARGE_INTEGER EndingTime;

			QueryPerformanceCounter(&EndingTime);

			EndingTime.QuadPart -= m_StartTime.QuadPart;
			return EndingTime.QuadPart / m_Frequency.QuadPart;
		}

		FORCE_INLINE uint64 GetMilliseconds()
		{
			LARGE_INTEGER EndingTime;

			QueryPerformanceCounter(&EndingTime);

			EndingTime.QuadPart -= m_StartTime.QuadPart;
			EndingTime.QuadPart *= 1000U;
			return EndingTime.QuadPart / m_Frequency.QuadPart;
		}

		FORCE_INLINE uint64 GetMicroseconds()
		{
			LARGE_INTEGER EndingTime;

			QueryPerformanceCounter(&EndingTime);

			EndingTime.QuadPart -= m_StartTime.QuadPart;
			EndingTime.QuadPart *= 1000000U;
			return EndingTime.QuadPart / m_Frequency.QuadPart;
		}

		FORCE_INLINE uint64 GetNanoseconds()
		{
			LARGE_INTEGER EndingTime;

			QueryPerformanceCounter(&EndingTime);

			EndingTime.QuadPart -= m_StartTime.QuadPart;
			EndingTime.QuadPart *= 1000000000U;
			return EndingTime.QuadPart / m_Frequency.QuadPart;
		}


	private:

		LARGE_INTEGER m_StartTime;
		LARGE_INTEGER m_Frequency;
	};

	namespace Test
	{
		FORCE_INLINE void TestTime()
		{
			WindowsTimer time;

			time.Start();

			Sleep(1000);

			printf("%llu seconds\n", time.GetSeconds());
			printf("%llu milliseconds\n", time.GetMilliseconds());
			printf("%llu microseconds\n", time.GetMicroseconds());
			printf("%llu nanoseconds\n", time.GetNanoseconds());
		}
	}
}

using PlatformTimer = DadEngine::Core::WindowsTimer;

#endif __WINDOWS_TIMERS_HPP_