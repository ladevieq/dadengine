#ifndef __OPENGL_GEOMETRY_SHADER_HPP_
#define __OPENGL_GEOMETRY_SHADER_HPP_

namespace DadEngine::Rendering
{
	class OpenGLGeometryShader : public GeometryShader
	{
	public:
		
		OpenGLGeometryShader(const char* _InShaderCode, size_t _InShaderCodeSize)
			: GeometryShader(_InShaderCode)
		{
			m_uiShaderID = OpenGLWrapper::glCreateShader(GL_GEOMETRY_SHADER);

			OpenGLWrapper::glShaderSource(m_uiShaderID, 1U, &_InShaderCode, NULL);

			OpenGLWrapper::glCompileShader(m_uiShaderID);

#if defined (_DEBUG)
			GLint isCompiled;
			DebugReport report;
			OpenGLWrapper::glGetShaderiv(m_uiShaderID, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				OpenGLWrapper::glGetShaderiv(m_uiShaderID, GL_INFO_LOG_LENGTH, &maxLength);

				//The maxLength includes the NULL character
				TArray<GLchar> infoLog(maxLength);
				OpenGLWrapper::glGetShaderInfoLog(m_uiShaderID, maxLength, &maxLength, &infoLog[0]);

				report.m_uiContextFlag = DEBUG_REPORT_CONTEXT_OPENGL;
				report.m_uiReportTypeFlag = DEBUG_REPORT_TYPE_ERROR;
				report.m_uiReportCode = DEBUG_REPORT_CODE_SHADER_COMPILING_FAILED;
				report.m_sMessage = infoLog.GetData();
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

		~OpenGLGeometryShader()
		{
			OpenGLWrapper::glDeleteShader(m_uiShaderID);
		}


		GLuint m_uiShaderID = 0U;
	};
}

#endif //!__OPENGL_GEOMETRY_SHADER_HPP_