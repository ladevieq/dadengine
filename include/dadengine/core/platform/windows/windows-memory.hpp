#ifndef __WINDOWS_MEMORY_HPP_
#define __WINDOWS_MEMORY_HPP_


namespace DadEngine
{
    class WindowsMemory
    {

        public:
        static void GetStatus();
    };
} // namespace DadEngine

using PlatformMemory = DadEngine::WindowsMemory;

#endif //__WINDOWS_MEMORY_HPP_

