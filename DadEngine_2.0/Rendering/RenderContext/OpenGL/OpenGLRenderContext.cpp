#include "OpenGLRenderContext.hpp"

#include "glext.hpp"
#include "wglext.hpp"
#include "OpenGLWrapper.hpp"
#include "../../Mesh/VertexFactory.hpp"
#include "../../../Math/Math.hpp"

namespace DadEngine::Rendering
{
	uint32 OpenGLCullingMode[] =
	{
		GL_FRONT,
		GL_BACK,
		GL_FRONT_AND_BACK
	};

	uint32 OpenGLFillMode[] =
	{
		GL_FILL,
		GL_LINE,
		GL_POINT
	};

	OpenGLRenderContext::OpenGLRenderContext(PlatformWindow& _InWindow)
	{
		m_HDC = GetDC(_InWindow.GetWindowHandle());
		PIXELFORMATDESCRIPTOR pxlDescriptor = {};
		pxlDescriptor.nSize = sizeof(pxlDescriptor);
		pxlDescriptor.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		pxlDescriptor.cColorBits = 32U;
		pxlDescriptor.cDepthBits = 24U;
		pxlDescriptor.cStencilBits = 8U;
		pxlDescriptor.iPixelType = PFD_TYPE_RGBA;
		pxlDescriptor.nVersion = 1U;

		int32 pixelFormat = ChoosePixelFormat(m_HDC, &pxlDescriptor);
		SetPixelFormat(m_HDC, pixelFormat, &pxlDescriptor);

		m_renderContext = wglCreateContext(m_HDC);
		wglMakeCurrent(m_HDC, m_renderContext);

		OpenGLWrapper::glInit();

		wglMakeCurrent(NULL, NULL);

		const int Attributes[]
		{
			WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
			WGL_CONTEXT_MINOR_VERSION_ARB, 1,
			WGL_CONTEXT_PROFILE_MASK_ARB,
			WGL_CONTEXT_CORE_PROFILE_BIT_ARB, 0
		};

		m_renderContext = OpenGLWrapper::wglCreateContextAttribsARB(m_HDC, NULL, Attributes);
		wglMakeCurrent(m_HDC, m_renderContext);

		int32 iMajor = 0, iMinor = 0;

		glGetIntegerv(GL_MAJOR_VERSION, &iMajor);
		glGetIntegerv(GL_MINOR_VERSION, &iMinor);

		printf("%s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

		printf("%s%d%s%d\n", "Version : ", iMajor, ".", iMinor);

		if (_InWindow.GetVerticalSync() == false)
		{
			OpenGLWrapper::wglSwapIntervalEXT(0);
		}
	}


	void OpenGLRenderContext::ClearBuffer(Color& _InClearColor)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		glClearColor(_InClearColor.r, _InClearColor.g, _InClearColor.b, _InClearColor.a);
	}

	void OpenGLRenderContext::Present()
	{
		SwapBuffers(m_HDC);
	}
	

	void OpenGLRenderContext::DrawPrimitives()
	{
		//glDrawElements(GL_TRIANGLES, _InVerticesCount, )
	}

	void OpenGLRenderContext::Draw(VertexBuffer* _InVertexBuffer)
	{
		OpenGLWrapper::glDrawArrays(GL_TRIANGLES, 0U, _InVertexBuffer->m_uiVertexCount);
	}

	void OpenGLRenderContext::BindVertexBuffer(VertexBuffer* _InVertexBuffer)
	{
		// Binding a VBO linked to a VAO and linking vertices inputs to the buffer
		OpenGLWrapper::glBindBuffer(GL_ARRAY_BUFFER, ((OpenGLVertexBuffer*)_InVertexBuffer)->m_uiBufferIndex);

		size_t offset = 0U;

		for (VertexInput input : _InVertexBuffer->m_verticesLayout)
		{
			uint32 count;
			size_t size;

			input.GetInputTypeInfo(size, count);

			OpenGLWrapper::glVertexAttribPointer(input.uiIndex, count, GL_FLOAT, GL_FALSE, (GLsizei)_InVertexBuffer->m_uiVertexLayoutStride, (void*)offset);
			OpenGLWrapper::glEnableVertexAttribArray(input.uiIndex);

			offset += size;
		}
		
		// Unbinding the buffer linked to a VAO
		OpenGLWrapper::glBindBuffer(GL_ARRAY_BUFFER, 0U);

		// Bind the VAO
		OpenGLWrapper::glBindVertexArray(((OpenGLVertexBuffer*)_InVertexBuffer)->m_uiArrayIndex);
	}

	void OpenGLRenderContext::BindShaderProgram(Shader* _InShader)
	{
		OpenGLWrapper::glUseProgram(((OpenGLShader*)_InShader)->m_uiProgramID);
	}

	void OpenGLRenderContext::SetViewport(Viewport& _InViewport)
	{
		glViewport(_InViewport.x, _InViewport.y, _InViewport.width, _InViewport.height);

		// Scissor ?
	}


	// We must keep this state somewhere
	void OpenGLRenderContext::SetCullingMode(CullingMode _InCullingMode)
	{
		glPolygonMode(OpenGLCullingMode[_InCullingMode], GL_FILL);
	}

	void OpenGLRenderContext::SetFillMode(FillMode _InFillMode)
	{
		glPolygonMode(GL_FRONT, OpenGLFillMode[_InFillMode]);
	}


	VertexBuffer * OpenGLRenderContext::CreateVertexBuffer(uint32 _InVertexCount, TArray<float>& _InData, TArray<VertexInput>& _InVertexLayout, uint32 _InVerticesStride)
	{
		return new OpenGLVertexBuffer(_InVertexCount, _InVertexLayout, _InData, _InVerticesStride);
	}


	VertexShader* OpenGLRenderContext::CreateVertexShader(const char * _InShaderCode, size_t _InShaderCodeSize, TArray<VertexInput>& _InVertexInputLayout)
	{
		return new OpenGLVertexShader(_InShaderCode, _InShaderCodeSize, _InVertexInputLayout);
	}

	GeometryShader* OpenGLRenderContext::CreateGeometryShader(const char * _InShaderCode, size_t _InShaderCodeSize)
	{
		return new OpenGLGeometryShader(_InShaderCode, _InShaderCodeSize);
	}

	FragmentShader* OpenGLRenderContext::CreateFragmentShader(const char * _InShaderCode, size_t _InShaderCodeSize)
	{
		return new OpenGLFragmentShader(_InShaderCode, _InShaderCodeSize);
	}


	Shader* OpenGLRenderContext::CreateShader(VertexShader * _InVertexShader, GeometryShader * _InGeometryShader, FragmentShader * _InFragmentShader)
	{
		return new OpenGLShader(_InVertexShader, _InGeometryShader, _InFragmentShader);
	}
}