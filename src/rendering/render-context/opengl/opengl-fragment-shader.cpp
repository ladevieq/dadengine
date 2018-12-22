#include "opengl-fragment-shader.hpp"

#include "opengl-wrapper.hpp"

namespace DadEngine::Rendering
{
    OpenGLFragmentShader::OpenGLFragmentShader(const char *_InShaderCode, size_t _InShaderCodeSize)
        : FragmentShader(_InShaderCode)
    {
        m_uiShaderID = OpenGLWrapper::glCreateShader(GL_FRAGMENT_SHADER);

        OpenGLWrapper::glShaderSource(m_uiShaderID, 1U, &_InShaderCode, NULL);

        OpenGLWrapper::glCompileShader(m_uiShaderID);

#if defined(_DEBUG)
        GLint isCompiled;
        DebugReport report;
        OpenGLWrapper::glGetShaderiv(m_uiShaderID, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            OpenGLWrapper::glGetShaderiv(m_uiShaderID, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            String infoLog(maxLength);
            OpenGLWrapper::glGetShaderInfoLog(m_uiShaderID, maxLength, &maxLength,
                                              const_cast<GLchar *>(infoLog.Cstr()));

            // TODO: get each lines to generates differant messages
            report.m_uiContextFlag = DEBUG_REPORT_CONTEXT_OPENGL;
            report.m_uiReportTypeFlag = DEBUG_REPORT_TYPE_ERROR;
            report.m_uiReportCode = DEBUG_REPORT_CODE_SHADER_COMPILING_FAILED;
            report.m_sMessage = infoLog.Cstr();
            LogDebugReport(report);
        }

        else
        {
            report.m_uiContextFlag = DEBUG_REPORT_CONTEXT_OPENGL;
            report.m_uiReportTypeFlag = DEBUG_REPORT_TYPE_INFORMATION;
            report.m_uiReportCode = DEBUG_REPORT_CODE_SHADER_COMPILING_SUCCEDED;
            report.m_sMessage = "Shader compilation succeded";
            LogDebugReport(report);
        }
#endif
    }

    OpenGLFragmentShader::~OpenGLFragmentShader()
    {
        OpenGLWrapper::glDeleteShader(m_uiShaderID);
    }
}