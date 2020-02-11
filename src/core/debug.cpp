#include "debug.hpp"

#include "defines.hpp"


namespace DadEngine
{
    const char *ContextName[] = { "Core", "OpenGL", "Vulkan" };

    const char *ReportTypeName[] = { "INFORMATION", "WARNING", "ERROR" };

    const char *CodeName[] = {
        "SHADER_COMPILING_FAILED",
        "SHADER_PROGRAM_LINKING_FAILED",
    };


    DebugReport::DebugReport(DebugReportContextFlags _contextFlag,
                             DebugReportTypeFlags _reportType,
                             DebugReportCode _errorCode,
                             const char *_message,
                             uint32_t _line,
                             const char *_filename)
        : m_contextFlag(_contextFlag), m_reportTypeFlag(_reportType),
          m_reportCode(_errorCode), m_line(_line), m_file(_filename), m_message(_message)
    {
    }


    /*
        [Context] : [Type] : (Code) : Message
    */
    void LogDebugReport(const DebugReport &_debugReport)
    {
        printf("[%s] [%s] (%d, %d, %s) : %s\n", // May need change
               ContextName[_debugReport.m_contextFlag],
               ReportTypeName[_debugReport.m_reportTypeFlag], _debugReport.m_reportCode,
               _debugReport.m_line, _debugReport.m_file, _debugReport.m_message);
    }

} // namespace DadEngine
