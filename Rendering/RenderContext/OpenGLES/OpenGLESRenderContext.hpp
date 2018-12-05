#ifndef __OPENGLES_RENDER_CONTEXT_HPP_
#define __OPENGLES_RENDER_CONTEXT_HPP_

#include "../RenderContext.hpp"

#include "../OpenGLES.hpp"


namespace DadEngine::Rendering
{
	class OpenGLESRenderContext : public RenderContext
	{

	public:

		OpenGLESRenderContext(PlatformWindow& _InWindow);

		// Commands
		void ClearColorBuffer(Color& _InClearColor, CommandBuffer* _InCommandBuffer) override final;

		void ClearDepthStencilBuffer(float _InDepthValue, uint32 _InStencilValue, CommandBuffer* _InCommandBuffer) override final;

		void Present(CommandBuffer* _InCommandBuffer) override final;

		void Draw(VertexBuffer* _InVertexBuffer, CommandBuffer* _InCommandBuffer) override final;

		void BindVertexBuffer(VertexBuffer* _InVertexBuffer, CommandBuffer* _InCommandBuffer) override final;

		void BindShaderProgram(Shader* _InShader, CommandBuffer* _InCommandBuffer) override final;

		void BeginRenderPass(RenderPass* _InRenderPass, Framebuffer* _InFrameBuffer, CommandBuffer* _InCommandBuffer) override final;

		void EndRenderPass(CommandBuffer* _InCommandBuffer) override final;


		// State change commands
		void SetViewport(Viewport& _InViewport, CommandBuffer* _InCommandBuffer) override final;

		void SetCullingMode(CullingMode _InCullingMode, CommandBuffer* _InCommandBuffer) override final;

		void SetFillMode(FillMode _InFillMode, CommandBuffer* _InCommandBuffer) override final;



		Image* GetBackBuffer() override final;

		Image* GetDepthStencilBuffer() override final;

		Framebuffer* GetBackFramebuffer() override final;

		RenderPass* GetRenderPass() override final;



		void BeginFrame() override final;

		void EndFrame() override final;

		void SubmitCommandBuffer(CommandBuffer* _InCommandBuffer) override final;


		VertexBuffer* CreateVertexBuffer(uint32 _InVertexCount, TArray<float>& _InData, TArray<VertexInput>& _InVertexLayout, uint32 _InVerticesStride) override final;
		VertexShader* CreateVertexShader(const char* _InShaderCode, size_t _InShaderCodeSize, TArray<VertexInput>& _InVertexInputLayout) override final;
		GeometryShader* CreateGeometryShader(const char* _InShaderCode, size_t _InShaderCodeSize) override final;
		FragmentShader* CreateFragmentShader(const char* _InShaderCode, size_t _InShaderCodeSize) override final;
		Shader* CreateShader(VertexShader* _InVertexShader, GeometryShader* _InGeometryShader, FragmentShader* _InFragmentShader, RenderPass* _InRenderpass) override final;
		CommandBuffer* CreateCommandBuffer() override final;
		RenderPass* CreateRenderPass(TArray<Image*>& _InImage) override final;
		Framebuffer* CreateFramebuffer(Extent2D& _InFramebufferSize, RenderPass* _InRenderPass) override final;


	private:

		//TArray<OpenGLCommandBuffer*> m_SubmittedCommandBuffers;

		HDC m_HDC = nullptr; // Hardware device context one per rendering thread
		HGLRC m_renderContext = nullptr; // Hardware render context
	};
}

#endif //__OPENGLES_RENDER_CONTEXT_HPP_