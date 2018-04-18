#include "OpenGLESRenderContext.hpp"

#include "../OpenGLWrapper.hpp"

namespace DadEngine::Rendering
{
	OpenGLESRenderContext::OpenGLESRenderContext(PlatformWindow& _InWindow)
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
			WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
			WGL_CONTEXT_MINOR_VERSION_ARB, 0,
			WGL_CONTEXT_PROFILE_MASK_ARB,
			WGL_CONTEXT_ES2_PROFILE_BIT_EXT, 0
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


	void OpenGLESRenderContext::ClearColorBuffer(Color& _InClearColor, CommandBuffer* _InCommandBuffer) {}

	void OpenGLESRenderContext::ClearDepthStencilBuffer(float _InDepthValue, uint32 _InStencilValue, CommandBuffer* _InCommandBuffer) {}

	void OpenGLESRenderContext::Present(CommandBuffer* _InCommandBuffer) {}

	void OpenGLESRenderContext::Draw(VertexBuffer* _InVertexBuffer, CommandBuffer* _InCommandBuffer) {}

	void OpenGLESRenderContext::BindVertexBuffer(VertexBuffer* _InVertexBuffer, CommandBuffer* _InCommandBuffer) {}

	void OpenGLESRenderContext::BindShaderProgram(Shader* _InShader, CommandBuffer* _InCommandBuffer) {}

	void OpenGLESRenderContext::BeginRenderPass(RenderPass* _InRenderPass, Framebuffer* _InFrameBuffer, CommandBuffer* _InCommandBuffer) {}

	void OpenGLESRenderContext::EndRenderPass(CommandBuffer* _InCommandBuffer) {}


	// State change commands
	void OpenGLESRenderContext::SetViewport(Viewport& _InViewport, CommandBuffer* _InCommandBuffer) {}

	void OpenGLESRenderContext::SetCullingMode(CullingMode _InCullingMode, CommandBuffer* _InCommandBuffer) {}

	void OpenGLESRenderContext::SetFillMode(FillMode _InFillMode, CommandBuffer* _InCommandBuffer) {}



	Image* OpenGLESRenderContext::GetBackBuffer() { return nullptr; }

	Image* OpenGLESRenderContext::GetDepthStencilBuffer() { return nullptr; }

	Framebuffer* OpenGLESRenderContext::GetBackFramebuffer() { return nullptr; }

	RenderPass* OpenGLESRenderContext::GetRenderPass() { return nullptr; }



	void OpenGLESRenderContext::BeginFrame() {}

	void OpenGLESRenderContext::EndFrame() {}

	void OpenGLESRenderContext::SubmitCommandBuffer(CommandBuffer* _InCommandBuffer) {}


	VertexBuffer* OpenGLESRenderContext::CreateVertexBuffer(uint32 _InVertexCount, TArray<float>& _InData, TArray<VertexInput>& _InVertexLayout, uint32 _InVerticesStride) { return nullptr; }

	VertexShader* OpenGLESRenderContext::CreateVertexShader(const char* _InShaderCode, size_t _InShaderCodeSize, TArray<VertexInput>& _InVertexInputLayout) { return nullptr; }

	GeometryShader* OpenGLESRenderContext::CreateGeometryShader(const char* _InShaderCode, size_t _InShaderCodeSize) { return nullptr; }

	FragmentShader* OpenGLESRenderContext::CreateFragmentShader(const char* _InShaderCode, size_t _InShaderCodeSize) { return nullptr; }

	Shader* OpenGLESRenderContext::CreateShader(VertexShader* _InVertexShader, GeometryShader* _InGeometryShader, FragmentShader* _InFragmentShader, RenderPass* _InRenderpass) { return nullptr; }

	CommandBuffer* OpenGLESRenderContext::CreateCommandBuffer() { return nullptr; }

	RenderPass* OpenGLESRenderContext::CreateRenderPass(TArray<Image*>& _InImage) { return nullptr; }

	Framebuffer* OpenGLESRenderContext::CreateFramebuffer(Extent2D& _InFramebufferSize, RenderPass* _InRenderPass) { return nullptr; }
}