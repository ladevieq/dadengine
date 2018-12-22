#include "opengl-shader.hpp"

#include "opengl-fragment-shader.hpp"
#include "opengl-geometry-shader.hpp"
#include "opengl-vertex-shader.hpp"
#include "opengl-wrapper.hpp"

namespace DadEngine::Rendering
{
    OpenGLShader::OpenGLShader(VertexShader *_InVertexShader, GeometryShader *_InGeometryShader, FragmentShader *_InFragmentShader)
        : Shader(_InVertexShader, _InGeometryShader, _InFragmentShader)
    {
        m_uiProgramID = OpenGLWrapper::glCreateProgram();

        OpenGLWrapper::glAttachShader(m_uiProgramID, ((OpenGLVertexShader *)_InVertexShader)->m_uiShaderID);
        OpenGLWrapper::glAttachShader(m_uiProgramID, ((OpenGLFragmentShader *)_InFragmentShader)->m_uiShaderID);

        OpenGLWrapper::glLinkProgram(m_uiProgramID);

#if defined(_DEBUG)
        DebugReport report;
        GLint isLinked = 0;
        OpenGLWrapper::glGetProgramiv(m_uiProgramID, GL_LINK_STATUS, &isLinked);
        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            OpenGLWrapper::glGetProgramiv(m_uiProgramID, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            TArray<GLchar> infoLog(maxLength);
            OpenGLWrapper::glGetProgramInfoLog(m_uiProgramID, maxLength, &maxLength, &infoLog[0]);

            report.m_uiContextFlag = DEBUG_REPORT_CONTEXT_OPENGL;
            report.m_uiReportTypeFlag = DEBUG_REPORT_TYPE_ERROR;
            report.m_uiReportCode = DEBUG_REPORT_CODE_SHADER_PROGRAM_LINKING_FAILED;
            report.m_iLine = __LINE__;
            report.m_sFile = __FILE__;
            report.m_sMessage = infoLog.GetData();
            LogDebugReport(report);
        }

        else
        {
            report.m_uiContextFlag = DEBUG_REPORT_CONTEXT_OPENGL;
            report.m_uiReportTypeFlag = DEBUG_REPORT_TYPE_INFORMATION;
            report.m_uiReportCode = DEBUG_REPORT_CODE_SHADER_PROGRAM_LINKING_SUCCEDED;
            report.m_iLine = __LINE__;
            report.m_sFile = __FILE__;
            report.m_sMessage = "Shader program linking succeded";
            LogDebugReport(report);
        }
#endif

        // Bind function
        // OpenGLWrapper::glUseProgram(m_uiProgramID);
    }

    OpenGLShader::~OpenGLShader()
    {
        OpenGLWrapper::glDeleteProgram(m_uiProgramID);
    }
}