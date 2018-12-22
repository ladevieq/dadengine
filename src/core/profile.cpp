#include "Profile.hpp"

#include <stdio.h>

#include "platform/timers.hpp"


namespace DadEngine::Core
{
    Profile::Profile(const char *_sProfilename)
		: m_sProfilename(_sProfilename)
    {
        time.Start();
    }

    Profile::~Profile()
    {
        printf("%s %llu %s\n", m_sProfilename, time.GetMilliseconds(), "ms.");
    }

	namespace Test
    {
        void TestProfile()
        {
            Profile test("Test");

            for (size_t i = 0; i < 1000000000U; i++)
            {
            }
        }
    } // namespace Test
}