#ifndef __PROFILER_HPP_
#define __PROFILER_HPP_


#include <stdio.h>

namespace DadEngine::Core
{
	class Profile
	{
	public:

		Profile(const char* _sProfilename): m_sProfilename(_sProfilename)
		{
			time.Start();
		}

		~Profile()
		{
			printf("%s %llu %s\n", m_sProfilename, time.GetMilliseconds(), "ms.");
		}


	private:

		const char* m_sProfilename = "\0";
		PlatformTimer time;
	};

	namespace Test
	{
		FORCE_INLINE static void TestProfile() {
			Profile test("Test");

			for (size_t i = 0; i < 1000000000U; i++)
			{

			}
		}
	}
}

#endif //__PROFILER_HPP_