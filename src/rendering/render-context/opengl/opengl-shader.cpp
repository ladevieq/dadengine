#include "opengl-shader.hpp"

#include "opengl-fragment-shader.hpp"
#include "opengl-geometry-shader.hpp"
#include "opengl-vertex-shader.hpp"
#include "opengl-wrapper.hpp"

namespace DadEngine
{
    OpenGLShader::OpenGLShader(VertexShader *_vertexShader,
                               GeometryShader *_geometryShader,
                               FragmentShader *_fragmentShader)
        : Shader(_vertexShader, _geometryShader, _fragmentShader)
    {
        m_programID = glCreateProgram();

        glAttachShader(m_programID,
                       dynamic_cast<OpenGLVertexShader *>(_vertexShader)->m_shaderID);
        glAttachShader(m_programID,
                       dynamic_cast<OpenGLFragmentShader *>(_fragmentShader)->m_shaderID);

        glLinkProgram(m_programID);

#if defined(_DEBUG)
        DebugReport report;
        GLint isLinked = 0;
        glGetProgramiv(m_programID, GL_LINK_STATUS, &isLinked);
        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            TArray<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(m_programID, maxLength, &maxLength, &infoLog[0]);

            report.m_contextFlag = DEBUG_REPORT_CONTEXT_OPENGL;
            report.m_reportTypeFlag = DEBUG_REPORT_TYPE_ERROR;
            report.m_reportCode = DEBUG_REPORT_CODE_SHADER_PROGRAM_LINKING_FAILED;
            report.m_line = __LINE__;
            report.m_file = __FILE__;
            report.m_message = infoLog.GetData();
            LogDebugReport(report);
        }

        else
        {
            report.m_contextFlag = DEBUG_REPORT_CONTEXT_OPENGL;
            report.m_reportTypeFlag = DEBUG_REPORT_TYPE_INFORMATION;
            report.m_reportCode = DEBUG_REPORT_CODE_SHADER_PROGRAM_LINKING_SUCCEDED;
            report.m_line = __LINE__;
            report.m_file = __FILE__;
            report.m_message = "Shader program linking succeded";
            LogDebugReport(report);
        }
#endif

        // Bind function
        // glUseProgram(m_uiProgramID);
    }

    OpenGLShader::~OpenGLShader()
    {
        glDeleteProgram(m_programID);
    }
} // namespace DadEngine
