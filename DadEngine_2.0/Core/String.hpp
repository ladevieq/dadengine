#ifndef __STRING_HPP_
#define __STRING_HPP_


namespace DadEngine::Core
{
	template<typename Allocator = LinearAlllocator<char>>
	class String
	{
		String(char* _InContent)
		{
			//while(_InContent)
		}

		~String() = default;

		String& operator= (String&& _InSrc) = default;

		void operator= (char*&& _InSrc)
		{
			if (m_allocator.m_ptrMemLocation)
			{
				m_allocator.Deallocate();
			}

			m_allocator.m_ptrMemLocation = _InSrc;
		}


		FORCE_INLINE void Append(String& _InNewString)
		{

		}

		FORCE_INLINE void Append(const char* _InNewCStrign)
		{

		}

		FORCE_INLINE const char* Cstr() const
		{
			return m_allocator.m_ptrMemLocation;
		}

		FORCE_INLINE uint32 Size()
		{
			return m_allocator.m_uiCapacity;
		}

		TArray<char> m_string;

		Allocator m_allocator = Allocator();
	};

	namespace Test
	{
		FORCE_INLINE void TestString()
		{
			
		}
	}
}

#endif __STRING_HPP_