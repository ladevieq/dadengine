#ifndef __DEBUG_HPP_
#define __DEBUG_HPP_

#include <stdio.h>

#include "Defines.hpp"
//#include "String.hpp"
#include "PlatformTypes.hpp"


namespace DadEngine::Core//::Debug
{
	/* Codes ranges
		1xxxx - Core Report Codes
			11xxx -
			12xxx -
			13xxx -
		2xxxx - Rendering Context Report Codes
			21xxx - Shader / Shader program Informations
				21001 Shader compilation succeded
				21002 Shader program linking succeded
			22xxx - Shader / Shader program Warnings
			23xxx - Shader / Shader Program Errors
				23001 Shader compilation error
				23002 Shader program linking error
				23003 Depth stencil buffer created with wrong format

		x1xxx - INFORMATION
		x2xxx - WARNING
		x3xxx - ERROR
	*/
	enum DEBUG_REPORT_CODE
	{
		DEBUG_REPORT_CODE_SHADER_COMPILING_SUCCEDED = 21001,
		DEBUG_REPORT_CODE_SHADER_PROGRAM_LINKING_SUCCEDED = 21002,
		
		DEBUG_REPORT_CODE_SHADER_COMPILING_FAILED = 23001,
		DEBUG_REPORT_CODE_SHADER_PROGRAM_LINKING_FAILED = 23002,
		DEBUG_REPORT_CODE_DEPTH_STENCIL_BUFFER_FORMAT_ERROR = 23003,

		MAX_DEBUG_REPORT_CODE = 0xffffffff
	};
	using DebugReportCode = uint32;


	enum DEBUG_REPORT_TYPE
	{
		DEBUG_REPORT_TYPE_INFORMATION,
		DEBUG_REPORT_TYPE_WARNING,
		DEBUG_REPORT_TYPE_ERROR,
		MAX_DEBUG_REPORT_TYPE = 0xffffffff
	};
	using DebugReportTypeFlags = uint32;


	enum DEBUG_REPORT_CONTEXT
	{
		DEBUG_REPORT_CONTEXT_CORE,
		DEBUG_REPORT_CONTEXT_OPENGL,
		DEBUG_REPORT_CONTEXT_VULKAN,
		MAX_DEBUG_REPORT_CONTEXT = 0xff
	};
	using DebugReportContextFlags = uint8;


	struct DebugReport
	{
		DebugReport() = default;

		DebugReport(DebugReportContextFlags _InContextFlag, DebugReportTypeFlags _InReportType, DebugReportCode _InErrorCode, const char* sMessage)
			: m_uiContextFlag(_InContextFlag),
				m_uiReportTypeFlag (_InReportType),
				m_uiReportCode(_InErrorCode),
				m_sMessage(sMessage)
		{}

		/*DebugReport(DebugReportContextFlags _InContextFlag, DebugReportTypeFlags _InReportType, DebugReportCode _InErrorCode, String& sMessage)
			: m_uiContextFlag(_InContextFlag),
				m_uiReportTypeFlag(_InReportType),
				m_uiErrorCode(_InErrorCode),
				m_sMessage(sMessage.Cstr())
		{}*/

		DebugReportContextFlags m_uiContextFlag = MAX_DEBUG_REPORT_CONTEXT;
		DebugReportTypeFlags m_uiReportTypeFlag = MAX_DEBUG_REPORT_TYPE;
		DebugReportCode m_uiReportCode = MAX_DEBUG_REPORT_CODE;
		int32 m_iLine; // May need change
		const char* m_sFile = nullptr; // May need change
		const char* m_sMessage = nullptr;
	};


	/*
		[Context] : [Type] : (Code, Line, File) : Message
	*/
	void LogDebugReport(const DebugReport& _InDebugReport);

	void LogAssert(const char* const _InMessage, const char* const _InFile, uint32 _InLine);

	void Log(const char* const _InMessage);
	

	namespace Test
	{
		FORCE_INLINE static void TestDebug()
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