#ifndef __STRING_HPP_
#define __STRING_HPP_

#include <string.h>
#include "Collection/TArray.hpp"
#include "../Memory/MemoryManager.hpp"

namespace DadEngine::Core
{
	class String
	{
	public:

		String(const char* _InContent): m_string(strlen(_InContent))
		{
			MemoryManager::Copy((void*)_InContent, m_string.GetData(), m_string.Size());
		}

		String(size_t _InSize)
			: m_string(_InSize, '\0')
		{}

		~String() = default;

		String& operator= (String&& _InSrc) = default;

		void operator= (char*& _InSrc)
		{
			size_t size = strlen(_InSrc);
			m_string.Reserve(size);

			MemoryManager::Copy((void*)_InSrc, m_string.GetData(), size);
		}

		/*void operator= (char*&& _InSrc)
		{
			if (m_allocator.m_ptrMemLocation)
			{
				m_allocator.Deallocate();
			}

			m_allocator. strlen(_InSrc);
			m_allocator.m_ptrMemLocation = _InSrc;
		}*/


		FORCE_INLINE void Append(String& _InNewString)
		{
			size_t currentSize = m_string.Size();
			size_t appendSize = _InNewString.Size();

			m_string.Resize(currentSize + appendSize);

			MemoryManager::Copy((void*)_InNewString.Cstr(), &m_string[(uint32)currentSize - 1U], appendSize);
		}

		FORCE_INLINE void Append(const char* _InNewCString)
		{
			size_t currentSize = m_string.Size();
			size_t appendSize = strlen(_InNewCString);

			m_string.Resize(currentSize + appendSize);

			MemoryManager::Copy((void*)_InNewCString, &m_string[(uint32)currentSize - 1U], appendSize);
		}

		FORCE_INLINE const char* Cstr() const
		{
			return m_string.GetData();
		}

		FORCE_INLINE size_t Size()
		{
			return m_string.Size();
		}


	private:

		TArray<char> m_string;
	};

	namespace Test
	{
		FORCE_INLINE static void TestString()
		{
			
		}
	}
}

#endif //__STRING_HPP_