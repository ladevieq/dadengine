#include "Debug.hpp"

#include <stdio.h>

#include "Defines.hpp"
#include "Platform/Types.hpp"


namespace DadEngine::Core
{
	const char* gContextName[] =
	{
		"Core" ,
		"OpenGL",
		"Vulkan"
	};

	const char* gReportTypeName[] =
	{
		"INFORMATION",
		"WARNING",
		"ERROR"
	};

	const char* gCodeName[] =
	{
		"SHADER_COMPILING_FAILED",
		"SHADER_PROGRAM_LINKING_FAILED",
	};


	DebugReport::DebugReport(DebugReportContextFlags _InContextFlag,
                DebugReportTypeFlags _InReportType,
                DebugReportCode _InErrorCode,
                const char *sMessage,
                uint32 _InLine,
                const char *sFileName)
        : m_uiContextFlag(_InContextFlag), m_uiReportTypeFlag(_InReportType),
          m_uiReportCode(_InErrorCode), m_sMessage(sMessage), m_iLine(_InLine), m_sFile(sFileName)
    {
    }


	/*
		[Context] : [Type] : (Code) : Message
	*/
	void LogDebugReport(const DebugReport & _InDebugReport)
	{
		printf("[%s] [%s] (%d, %d, %s) : %s\n",// May need change
			gContextName[_InDebugReport.m_uiContextFlag],
			gReportTypeName[_InDebugReport.m_uiReportTypeFlag],
			_InDebugReport.m_uiReportCode,
			_InDebugReport.m_iLine,
			_InDebugReport.m_sFile,
			_InDebugReport.m_sMessage);
	}


	void LogAssert(const char* const _InMessage, const char* const _InFile, uint32 _InLine)
	{
		printf("[%s, %s, %u]: %s\n", "Assertion", _InFile, _InLine, _InMessage);
	}


	void Log(const char* const _InMessage)
	{
		printf("%s\n", _InMessage);
	}


	namespace Test
    {
        void TestDebug()
        {
            int i = 10;
            int *ptr = &i;

            LOG_ASSERT(ptr == nullptr, "Erreur de pointeur");

            ptr = nullptr;
        }
    } // namespace Test
}