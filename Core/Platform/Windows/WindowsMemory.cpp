#include "WindowsMemory.hpp"

#include <stdio.h>
#include <Windows.h>


namespace DadEngine::Core
{
    void WindowsMemory::GetStatus()
    {
        MEMORYSTATUSEX status = {};
        status.dwLength = sizeof(status);

        GlobalMemoryStatusEx(&status);

        printf("%s%llu\n", "Available physical memory : ", status.ullAvailPhys);
        printf("%s%llu\n", "Available virtual memory : ", status.ullAvailVirtual);
        printf("%s%llu\n", "Total physical memory : ", status.ullTotalPhys);
        printf("%s%llu\n", "Toral virtual memory : ", status.ullTotalVirtual);
    }
}