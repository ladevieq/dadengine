#include "memory-manager.hpp"

#include <malloc.h>
#include <memory.h>

#include "../debug.hpp"
#include "../platform/memory.hpp"

namespace DadEngine
{
    void *MemoryManager::Allocate(size_t _InItemSize, size_t _InItemCount)
    {
        size_t allocSize = _InItemSize * _InItemCount;

        return malloc(allocSize);
    }

    void MemoryManager::Deallocate(void *_InMemLocation)
    {
        free(_InMemLocation);
    }

    void MemoryManager::Copy(void *_InSrc, void *_InDst, size_t _InCpySize)
    {
        Assert(_InSrc);
        Assert(_InDst);

        memcpy(_InDst, _InSrc, _InCpySize);

        // Try with move constructor ...
        //(uint8 [_InCpySize])_InSrc
    }

    void MemoryManager::Set(void *_InDst, int32_t _InValue, size_t _InCpySize)
    {
        Assert(_InDst);
        memset(_InDst, _InValue, _InCpySize);
    }

    void MemoryManager::GetMemoryInfo()
    {
        // PlatformMemory::GetStatus();
    }

} // namespace DadEngine

void *operator new(size_t _InChunkSize)
{
    return DadEngine::MemoryManager::Allocate(1, _InChunkSize);
}

void operator delete(void *_InMemLocation) noexcept
{
    DadEngine::MemoryManager::Deallocate(_InMemLocation);
}
