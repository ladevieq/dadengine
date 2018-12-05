#include "Debug.hpp"


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
}