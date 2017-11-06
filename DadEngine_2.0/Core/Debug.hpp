#ifndef __DEBUG_HPP_
#define __DEBUG_HPP_

#include <stdio.h>


namespace DadEngine::Core//::Debug
{
	FORCE_INLINE static void LogAssert(const char* const _InMessage, const char* const _InFile, uint32 _InLine)
	{
		printf("[%s, %s, %u]: %s", "Assertion", _InFile, _InLine, _InMessage);
	}

	FORCE_INLINE static void Log(const char* const _InMessage)
	{
		printf("%s", _InMessage);
	}

	namespace Test
	{
		FORCE_INLINE void TestDebug()
		{
			int i = 10;
			int* ptr = &i;

			LOG_ASSERT(ptr == nullptr, "Erreur de pointeur");

			ptr = nullptr;
		}
	}
}

//using namespace DadEngine::Core::Debug;

#endif //__DEBUG_HPP_