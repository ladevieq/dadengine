#ifndef __DEBUG_HPP_
#define __DEBUG_HPP_

#include <cassert>
#include <cstdint>
#include <cstdio>

namespace DadEngine //::Debug
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
    enum DEBUG_REPORT_CODE : uint32_t
    {
        DEBUG_REPORT_CODE_SHADER_COMPILING_SUCCEDED = 21001,
        DEBUG_REPORT_CODE_SHADER_PROGRAM_LINKING_SUCCEDED = 21002,

        DEBUG_REPORT_CODE_SHADER_COMPILING_FAILED = 23001,
        DEBUG_REPORT_CODE_SHADER_PROGRAM_LINKING_FAILED = 23002,
        DEBUG_REPORT_CODE_DEPTH_STENCIL_BUFFER_FORMAT_ERROR = 23003,

        MAX_DEBUG_REPORT_CODE = 0xffffffff
    };
    using DebugReportCode = uint32_t;


    enum DEBUG_REPORT_TYPE : uint8_t
    {
        DEBUG_REPORT_TYPE_INFORMATION,
        DEBUG_REPORT_TYPE_WARNING,
        DEBUG_REPORT_TYPE_ERROR,
        MAX_DEBUG_REPORT_TYPE = 0xff
    };
    using DebugReportTypeFlags = uint8_t;


    enum DEBUG_REPORT_CONTEXT : uint8_t
    {
        DEBUG_REPORT_CONTEXT_CORE,
        DEBUG_REPORT_CONTEXT_OPENGL,
        DEBUG_REPORT_CONTEXT_VULKAN,
        MAX_DEBUG_REPORT_CONTEXT = 0xff
    };
    using DebugReportContextFlags = uint8_t;


    struct DebugReport
    {
        DebugReport() = default;

        DebugReport(DebugReportContextFlags _contextFlag,
                    DebugReportTypeFlags _reportType,
                    DebugReportCode _errorCode,
                    const char *_message,
                    const uint32_t _line,
                    const char *_filename);

        /*DebugReport(DebugReportContextFlags _InContextFlag,
        DebugReportTypeFlags _InReportType, DebugReportCode _InErrorCode,
        String& sMessage) : m_uiContextFlag(_InContextFlag),
                m_uiReportTypeFlag(_InReportType),
                m_uiErrorCode(_InErrorCode),
                m_sMessage(sMessage.Cstr())
        {}*/

        DebugReportContextFlags m_contextFlag = MAX_DEBUG_REPORT_CONTEXT;
        DebugReportTypeFlags m_reportTypeFlag = MAX_DEBUG_REPORT_TYPE;
        DebugReportCode m_reportCode = MAX_DEBUG_REPORT_CODE;
        const uint32_t m_line = 0U; // May need change
        const char *m_file = nullptr; // May need change
        const char *m_message = nullptr;
    };


    /*
        [Context] : [Type] : (Code, Line, File) : Message
    */
    void LogDebugReport(const DebugReport &_debugReport);

    constexpr void Assert(const bool _expression)
    {
        assert(_expression);
    }

    inline void LogAssert(const bool _expression,
                          const char *const _message,
                          const char *const _file,
                          const uint32_t _line)
    {
        if (!_expression)
        {
            // TODO: Add a message box
            printf("[%s, %s, %u]: %s\n", "Assertion", _file, _line, _message);
        }
    }

    inline void Log(const char *const _message)
    {
        printf("%s\n", _message);
    }

} // namespace DadEngine

// using namespace DadEngine::Debug;

#endif //__DEBUG_HPP_
