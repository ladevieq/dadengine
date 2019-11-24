#ifndef __PROFILER_HPP_
#define __PROFILER_HPP_

#include "platform/timers.hpp"


namespace DadEngine
{
    class Profile
    {
        public:
        Profile(const char *_sProfilename);

        ~Profile();


        private:
        const char *m_sProfilename = "\0";
        PlatformTimer time;
    };

    namespace Test
    {
        void TestProfile();
    } // namespace Test
} // namespace DadEngine

#endif //__PROFILER_HPP_

