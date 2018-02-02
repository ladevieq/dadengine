#ifndef __WINDOWS_THREADS_HPP_
#define __WINDOWS_THREADS_HPP_

#include <Windows.h>
#include <cstdio>


namespace DadEngine::Core
{
	class WindowsThread
	{
	public:

		using Job = void (*)(void);

		WindowsThread(uint8 _InStart, Job _InJob)
		{
			m_ptrJobFunction = _InJob;

			m_ThreadHandle = CreateThread(NULL, 0U, (LPTHREAD_START_ROUTINE)Work, this, _InStart ? NULL : CREATE_SUSPENDED, NULL);

			ASSERT(m_ThreadHandle);

			m_eThreadState = _InStart ? WORKING : CREATED;
		}

		~WindowsThread()
		{
			if (m_eThreadState == WORKING || m_eThreadState == STOPPED || m_eThreadState == CREATED)
				Kill();
		}


		FORCE_INLINE void Resume()
		{
			ResumeThread(m_ThreadHandle);

			m_eThreadState = WORKING;
		}

		FORCE_INLINE void Stop()
		{
			SuspendThread(m_ThreadHandle);

			m_eThreadState = STOPPED;
		}

		FORCE_INLINE void Kill()
		{
			TerminateThread(m_ThreadHandle, 0U);

			m_eThreadState = TERMINATED;
		}

		static void Work(WindowsThread* _ptrJob)
		{
			_ptrJob->m_ptrJobFunction();

			_ptrJob->m_eThreadState = DONE;
		}


	//private:
		Job m_ptrJobFunction = nullptr;
		HANDLE m_ThreadHandle = nullptr;
		ThreadState m_eThreadState = CREATED;
	};

	namespace Test
	{
		FORCE_INLINE static void TestThread()
		{
			auto func = []() { while (1) {
				printf("Hello World!");
			}};

			WindowsThread thread(FALSE, func);

			Sleep(1000);

			thread.Resume();

			Sleep(1000);

			thread.Stop();

			Sleep(1000);

			thread.Resume();

			Sleep(3000);

			thread.Kill();
		}
	}
}

#endif //__WINDOWS_THREADS_HPP_