#include "opengl-geometry-shader.hpp"

#include "opengl-wrapper.hpp"

namespace DadEngine
{
    OpenGLGeometryShader::OpenGLGeometryShader(const char *_shaderCode, size_t _shaderCodeSize)
        : GeometryShader(_shaderCode)
    {
        m_shaderID = glCreateShader(GL_GEOMETRY_SHADER);

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
            TArray<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(m_shaderID, maxLength, &maxLength, &infoLog[0]);

            report.m_contextFlag = DEBUG_REPORT_CONTEXT_OPENGL;
            report.m_reportTypeFlag = DEBUG_REPORT_TYPE_ERROR;
            report.m_reportCode = DEBUG_REPORT_CODE_SHADER_COMPILING_FAILED;
            report.m_message = infoLog.GetData();
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

    OpenGLGeometryShader::~OpenGLGeometryShader()
    {
        glDeleteShader(m_shaderID);
    }
} // namespace DadEngine
