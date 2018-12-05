#ifndef __MEMORYMANAGER_HPP_
#define __MEMORYMANAGER_HPP_

#include <malloc.h>

#include "../Defines.hpp"
#include "../PlatformTypes.hpp"
#include "../PlatformMemory.hpp"

namespace DadEngine::Core//::Memory
{
	struct MemoryChunk
	{
		const void* const m_ptrLocation = nullptr;
		size_t m_size = 0U;
		uint8 m_uiUsed : 1;
	};

	class MemoryManager
	{
	public:

		MemoryManager() = delete;
		~MemoryManager() = delete;

		MemoryManager& operator= (MemoryManager& _InCpy) = delete;

		FORCE_INLINE static void* Allocate(size_t _InItemSize, size_t _InItemCount)
		{
			size_t allocSize = _InItemSize * _InItemCount;

			return malloc(allocSize);
		}

		FORCE_INLINE static void Deallocate(void* _InMemLocation)
		{
			ASSERT(_InMemLocation);
			free(_InMemLocation);
		}

		FORCE_INLINE static void Copy(void* _InSrc, void* _InDst, size_t _InCpySize)
		{
			ASSERT(_InSrc);
			ASSERT(_InDst);

			memcpy(_InDst, _InSrc, _InCpySize);

			// Try with move constructor ...
			//(uint8 [_InCpySize])_InSrc
		}

		FORCE_INLINE static void Set(void* _InDst, int32 _InValue, size_t _InCpySize)
		{
			ASSERT(_InDst);
			memset(_InDst, _InValue, _InCpySize);
		}

		FORCE_INLINE static void GetMemoryInfo()
		{
			PlatformMemory::GetStatus();
		}


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
		//static Containers::TArray<MemoryChunk> m_memChunks;
	};


	namespace Test
	{
		FORCE_INLINE static void TestMemoryManager()
		{
			uint32* i = nullptr;

			i = new uint32;

			ASSERT(i);

			delete i;
		}
	}

};


void* operator new(size_t _InChunkSize);

void operator delete (void * _InMemLocation) noexcept;

#endif //__MEMORYMANAGER_HPP_