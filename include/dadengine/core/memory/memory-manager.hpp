#ifndef __MEMORYMANAGER_HPP_
#define __MEMORYMANAGER_HPP_

#include <cstdint>


namespace DadEngine
{
    /* struct MemoryChunk
    {
        const void* const m_ptrLocation = nullptr;
        size_t m_size = 0U;
        uint8 m_uiUsed : 1;
    }; */

    class MemoryManager
    {
        public:
        MemoryManager() = delete;
        ~MemoryManager() = delete;

        MemoryManager &operator=(MemoryManager &_InCpy) = delete;

        static void *Allocate(size_t _InItemSize, size_t _InItemCount);

        static void Deallocate(void *_InMemLocation);

        static void Copy(void *_InSrc, void *_InDst, size_t _InCpySize);

        static void Set(void *_InDst, int32_t _InValue, size_t _InCpySize);

        static void GetMemoryInfo();


        /*FORCE_INLINE static uint32 MemoryUsage()
        {
            uint32 memUsage = 0U;

            for(size_t i = 0; i < m_memChunks.Size(); i++)
            {
                memUsage += m_memChunks[i].m_size;
            }

            return memUsage;
        }*/

        // Array for mem chunk allocated
        // static Containers::TArray<MemoryChunk> m_memChunks;
    };

} // namespace DadEngine


void *operator new(size_t _InChunkSize);

void operator delete(void *_InMemLocation) noexcept;

#endif //__MEMORYMANAGER_HPP_

