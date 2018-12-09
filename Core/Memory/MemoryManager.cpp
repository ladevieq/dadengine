#include "MemoryManager.hpp"

#include <malloc.h>

#include "../Defines.hpp"
#include "../Platform/Memory.hpp"
#include "../Platform/Types.hpp"

namespace DadEngine::Core
{
    void *MemoryManager::Allocate (size_t _InItemSize, size_t _InItemCount)
    {
        size_t allocSize = _InItemSize * _InItemCount;

        return malloc (allocSize);
    }

    void MemoryManager::Deallocate (void *_InMemLocation)
    {
        ASSERT (_InMemLocation);
        free (_InMemLocation);
    }

    void MemoryManager::Copy (void *_InSrc, void *_InDst, size_t _InCpySize)
    {
        ASSERT (_InSrc);
        ASSERT (_InDst);

        memcpy (_InDst, _InSrc, _InCpySize);

        // Try with move constructor ...
        //(uint8 [_InCpySize])_InSrc
    }

    void MemoryManager::Set (void *_InDst, int32 _InValue, size_t _InCpySize)
    {
        ASSERT (_InDst);
        memset (_InDst, _InValue, _InCpySize);
    }

    void MemoryManager::GetMemoryInfo ()
    {
        PlatformMemory::GetStatus ();
    }

	namespace Test
    {
        static void TestMemoryManager ()
        {
            uint32 *i = nullptr;

            i = new uint32;

            ASSERT (i);

            delete i;
        }
    } // namespace Test
} // namespace DadEngine::Core

void *operator new (size_t _InChunkSize)
{
    return DadEngine::Core::MemoryManager::Allocate (1, _InChunkSize);
}

void operator delete (void *_InMemLocation) noexcept
{
    DadEngine::Core::MemoryManager::Deallocate (_InMemLocation);
}
