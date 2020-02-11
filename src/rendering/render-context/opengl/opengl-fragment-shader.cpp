#include "opengl-fragment-shader.hpp"

#include "opengl-wrapper.hpp"

namespace DadEngine
{
    OpenGLFragmentShader::OpenGLFragmentShader(const char *_shaderCode, size_t _shaderCodeSize)
        : FragmentShader(_shaderCode)
    {
        m_shaderID = glCreateShader(GL_FRAGMENT_SHADER);

        glShaderSource(m_shaderID, 1U, &_shaderCode, NULL);

        glCompileShader(m_shaderID);

#if defined(_DEBUG)
        GLint isCompiled;
        DebugReport report;
        glGetShaderiv(m_shaderID, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(m_shaderID, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            String infoLog(maxLength);
            glGetShaderInfoLog(m_shaderID, maxLength, &maxLength,
                               const_cast<GLchar *>(infoLog.Cstr()));

            // TODO: get each lines to generates different messages
            report.m_contextFlag = DEBUG_REPORT_CONTEXT_OPENGL;
            report.m_reportTypeFlag = DEBUG_REPORT_TYPE_ERROR;
            report.m_reportCode = DEBUG_REPORT_CODE_SHADER_COMPILING_FAILED;
            report.m_message = infoLog.Cstr();
            LogDebugReport(report);
        }

        else
        {
            report.m_contextFlag = DEBUG_REPORT_CONTEXT_OPENGL;
            report.m_reportTypeFlag = DEBUG_REPORT_TYPE_INFORMATION;
            report.m_reportCode = DEBUG_REPORT_CODE_SHADER_COMPILING_SUCCEDED;
            report.m_message = "Shader compilation succeded";
            LogDebugReport(report);
        }
#endif
    }

    OpenGLFragmentShader::~OpenGLFragmentShader()
    {
        glDeleteShader(m_shaderID);
    }
} // namespace DadEngine
