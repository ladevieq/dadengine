#include "WindowsTimers.hpp"

#include <stdio.h>

namespace DadEngine::Core
{
    void WindowsTimer::Start()
    {
        QueryPerformanceCounter(&m_StartTime);
        QueryPerformanceFrequency(&m_Frequency);
    }

    void WindowsTimer::Stop()
    {
    }

    void WindowsTimer::Reset()
    {
        Start();
    }

    uint64 WindowsTimer::GetSeconds()
    {
        LARGE_INTEGER EndingTime;

        QueryPerformanceCounter(&EndingTime);

        EndingTime.QuadPart -= m_StartTime.QuadPart;
        return EndingTime.QuadPart / m_Frequency.QuadPart;
    }

	uint64 WindowsTimer::GetMilliseconds()
    {
        LARGE_INTEGER EndingTime;

        QueryPerformanceCounter(&EndingTime);

        EndingTime.QuadPart -= m_StartTime.QuadPart;
        EndingTime.QuadPart *= 1000U;
        return EndingTime.QuadPart / m_Frequency.QuadPart;
    }

    uint64 WindowsTimer::GetMicroseconds()
    {
        LARGE_INTEGER EndingTime;

        QueryPerformanceCounter(&EndingTime);

        EndingTime.QuadPart -= m_StartTime.QuadPart;
        EndingTime.QuadPart *= 1000000U;
        return EndingTime.QuadPart / m_Frequency.QuadPart;
    }

	uint64 WindowsTimer::GetNanoseconds()
    {
        LARGE_INTEGER EndingTime;

        QueryPerformanceCounter(&EndingTime);

        EndingTime.QuadPart -= m_StartTime.QuadPart;
        EndingTime.QuadPart *= 1000000000U;
        return EndingTime.QuadPart / m_Frequency.QuadPart;
    }

	namespace Test
    {
        void TestTime()
        {
            WindowsTimer time;

            time.Start();

            Sleep(1000);

            printf("%llu seconds\n", time.GetSeconds());
            printf("%llu milliseconds\n", time.GetMilliseconds());
            printf("%llu microseconds\n", time.GetMicroseconds());
            printf("%llu nanoseconds\n", time.GetNanoseconds());
        }
    } // namespace Test
}