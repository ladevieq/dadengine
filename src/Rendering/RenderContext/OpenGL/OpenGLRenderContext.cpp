#include "OpenGLRenderContext.hpp"

#include "OpenGLWrapper.hpp"
#include "../../Mesh/VertexFactory.hpp"

#include "../../../Math/Math.hpp"

#include "../../../Gameplay/CameraManager.hpp"
#include "../../../Gameplay/Actor.hpp"

#include "../../Shader/Shader.hpp"
#include "OpenGLVertexShader.hpp"
#include "OpenGLGeometryShader.hpp"
#include "OpenGLFragmentShader.hpp"

#include "../../Mesh/RawMesh.hpp"
#include "OpenGLCommandBuffer.hpp"
#include "OpenGLFramebuffer.hpp"
#include "OpenGLRenderCommand.hpp"
#include "OpenGLShader.hpp"
#include "OpenGLVertexBuffer.hpp"

namespace DadEngine::Rendering
{
    uint32_t OpenGLCullingMode[] =
	{
		GL_FRONT,
		GL_BACK,
		GL_FRONT_AND_BACK
	};

	uint32_t OpenGLFillMode[] =
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

		int32_t pixelFormat = ChoosePixelFormat(m_HDC, &pxlDescriptor);
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

		int32_t iMajor = 0, iMinor = 0;

		glGetIntegerv(GL_MAJOR_VERSION, &iMajor);
		glGetIntegerv(GL_MINOR_VERSION, &iMinor);

		printf("%s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

		printf("%s%d%s%d\n", "Version : ", iMajor, ".", iMinor);

		if (_InWindow.GetVerticalSync() == false)
		{
			OpenGLWrapper::wglSwapIntervalEXT(0);
		}
	}


	void OpenGLRenderContext::ClearColorBuffer(Color& _InClearColor, CommandBuffer* _InCommandBuffer)
	{
		CommandClearColorBuffer((OpenGLCommandBuffer*)_InCommandBuffer, _InClearColor);
	}

	void OpenGLRenderContext::ClearDepthStencilBuffer(float _InDepthValue, uint32_t _InStencilValue, CommandBuffer* _InCommandBuffer)
	{
		CommandClearDepthStencilBuffer((OpenGLCommandBuffer*)_InCommandBuffer, (double)_InDepthValue, _InStencilValue);
	}

	void OpenGLRenderContext::Present(CommandBuffer* _InCommandBuffer)
	{
		OpenGLWrapper::glBindFrameBuffer(GL_FRAMEBUFFER_DEFAULT, 0U);
	}

	void OpenGLRenderContext::Draw(VertexBuffer* _InVertexBuffer, CommandBuffer* _InCommandBuffer)
	{
		CommandDraw((OpenGLCommandBuffer*)_InCommandBuffer, _InVertexBuffer);
	}

	void OpenGLRenderContext::DrawMultiples(VertexBuffer* _InVertexBuffer, int32_t _InInstanceCount, CommandBuffer* _InCommandBuffer)
	{
		CommandDrawMultiples((OpenGLCommandBuffer*)_InCommandBuffer, _InVertexBuffer, _InInstanceCount);
	}

	void OpenGLRenderContext::BindVertexBuffer(VertexBuffer* _InVertexBuffer, CommandBuffer* _InCommandBuffer)
	{
		CommandBindVertexBuffer((OpenGLCommandBuffer*)_InCommandBuffer, (OpenGLVertexBuffer*)_InVertexBuffer);
	}

	void OpenGLRenderContext::BindShaderProgram(Shader* _InShader, CommandBuffer* _InCommandBuffer)
	{
		CommandBindShaderProgram((OpenGLCommandBuffer*)_InCommandBuffer, _InShader);

		Matrix4x4 pers = Gameplay::CameraManager::GetCameraManager()->GetMainCamera()->GetProjectionMatrix();
		Matrix4x4 view;
		Vector3f eyePos = Gameplay::CameraManager::GetCameraManager()->GetMainCamera()->m_Owner->GetRelativeLocation();
		Vector3f targetPosition = Vector3f{ eyePos.x, eyePos.y, -1.f };
		Vector3f up = Vector3f{ 0.f, 1.f, 0.f };
		view.LookAt(eyePos, targetPosition, up);
		Matrix4x4 vp = pers * view;

		int32_t location = OpenGLWrapper::glGetUniformLocation(((OpenGLShader*)_InShader)->m_uiProgramID, "MVP");
		OpenGLWrapper::glUniformMatrix4fv(location, 1, GL_FALSE, ((float*)&vp));
	}

	void OpenGLRenderContext::SetShaderParameter(Shader* _InShader, const char* _InParameterName, ShaderParameterType _InShaderParameterType, void* _InParam)
	{
		int32_t location = OpenGLWrapper::glGetUniformLocation(((OpenGLShader*)_InShader)->m_uiProgramID, "MVP");

		switch (_InShaderParameterType)
		{
		case SHADER_PARAMETER_TYPE_MATRIX4X4:
			OpenGLWrapper::glUniformMatrix4fv(location, 1, GL_FALSE, ((float*)_InParam));
			break;

		default:
			break;
		}
	}

	void BeginRenderPass(RenderPass* _InRenderPass, Framebuffer* _InFrameBuffer, CommandBuffer* _InCommandBuffer)
	{
		OpenGLWrapper::glBindFrameBuffer(GL_READ_FRAMEBUFFER, ((OpenGLFramebuffer*)_InFrameBuffer)->m_uiFramebufferIndex);
	}

	void EndRenderPass(CommandBuffer* _InCommandBuffer)
	{
		OpenGLWrapper::glBindFrameBuffer(GL_FRAMEBUFFER_DEFAULT, 0U);
	}


	// We must keep this state somewhere
	void OpenGLRenderContext::SetCullingMode(CullingMode _InCullingMode, CommandBuffer* _InCommandBuffer)
	{
		glPolygonMode(OpenGLCullingMode[_InCullingMode], GL_FILL);
	}

	void OpenGLRenderContext::SetFillMode(FillMode _InFillMode, CommandBuffer* _InCommandBuffer)
	{
		glPolygonMode(GL_FRONT, OpenGLFillMode[_InFillMode]);
	}

	void OpenGLRenderContext::SetViewport(Viewport& _InViewport, CommandBuffer* _InCommandBuffer)
	{
		glViewport(_InViewport.x, _InViewport.y, _InViewport.width, _InViewport.height);

		// Scissor ?
	}



	void OpenGLRenderContext::BeginFrame()
	{
		OpenGLWrapper::glBindFrameBuffer(GL_FRAMEBUFFER_DEFAULT, 0U);
	}

	void OpenGLRenderContext::EndFrame()
	{
		// Execute commands
		for (OpenGLCommandBuffer* currentCmdBuffer : m_SubmittedCommandBuffers)
		{
			for (OpenGLRenderCommand* currentRenderCmd : currentCmdBuffer->m_Commands)
			{
				currentRenderCmd->Execute();
			}
		}

		SwapBuffers(m_HDC);

		m_SubmittedCommandBuffers.Clear();
	}

	void OpenGLRenderContext::SubmitCommandBuffer(CommandBuffer * _InCommandBuffer)
	{
		m_SubmittedCommandBuffers.Add((OpenGLCommandBuffer*)_InCommandBuffer);
	}



	VertexBuffer *OpenGLRenderContext::CreateVertexBuffer(uint32_t _InVertexCount,
                                                          TArray<float> &_InData,
                                                          TArray<VertexInput> &_InVertexLayout,
                                                          uint32_t _InVerticesStride)
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

	Shader* OpenGLRenderContext::CreateShader(VertexShader * _InVertexShader, GeometryShader * _InGeometryShader, FragmentShader * _InFragmentShader, RenderPass* _InRenderpass)
	{
		return new OpenGLShader(_InVertexShader, _InGeometryShader, _InFragmentShader);
	}
	
	CommandBuffer * OpenGLRenderContext::CreateCommandBuffer()
	{
		return new OpenGLCommandBuffer(this);
	}
}