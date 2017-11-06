#ifndef __WINDOWS_TYPES_HPP_
#define	__WINDOWS_TYPES_HPP_


namespace DadEngine::Core//::Types
{
	using uint64 = unsigned long long;
	using int64 =  long long;
	using uint32 = unsigned int;
	using int32 = int;
	using uint16 = unsigned short;
	using int16 = short;
	using uint8 = unsigned char;
	using int8 = char;

	// bool ?

#if defined (_WIN64)
	using uint64 = size_t;
#else
	using uint32 = size_t;
#endif

	namespace Test
	{
		// Insert assert test here:
		FORCE_INLINE void TestTypes()
		{
			/*ASSERT(sizeof(uint64) == 8);
			ASSERT(sizeof(int64) == 8);
			ASSERT(sizeof(uint32) == 4);
			ASSERT(sizeof(int32) == 4);
			ASSERT(sizeof(int16) == 2);
			ASSERT(sizeof(uint16) == 2);
			ASSERT(sizeof(uint8) == 1);
			ASSERT(sizeof(int8) == 1);
			ASSERT(sizeof(size_t) == 4);*/
		}
	}
}

//using namespace DadEngine::Core::Types;

#endif //__WINDOWS_TYPES_HPP_