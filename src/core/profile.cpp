#include "profile.hpp"

#include <cstdio>

#include "platform/timers.hpp"


namespace DadEngine
{
    Profile::Profile(const char *_sProfilename) : m_sProfilename(_sProfilename)
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
} // namespace DadEngine

