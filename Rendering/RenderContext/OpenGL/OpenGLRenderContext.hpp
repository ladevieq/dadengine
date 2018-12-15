#ifndef __OPENGL_RENDER_CONTEXT_HPP_
#define __OPENGL_RENDER_CONTEXT_HPP_

#include <Windows.h>
#include <gl/GL.h>
#include "../../../Core/Core.hpp"
#include "../RenderContext.hpp"
#include "../../Mesh/RawMesh.hpp"
#include "OpenGLVertexBuffer.hpp"
#include "OpenGLShader.hpp"
#include "OpenGLRenderCommand.hpp"
#include "OpenGLCommandBuffer.hpp"
#include "OpenGLFramebuffer.hpp"


namespace DadEngine::Rendering
{
    class Shader;
    struct VertexShader;
    struct GeometryShader;
    struct FragmentShader;

	class OpenGLRenderContext : public RenderContext
	{

	public:

		OpenGLRenderContext(PlatformWindow& _InWindow);

		void ClearColorBuffer(Color& _InClearColor, CommandBuffer* _InCommandBuffer) override final;

		void ClearDepthStencilBuffer(float _InDepthValue, uint32_t _InStencilValue, CommandBuffer *_InCommandBuffer);

		void Present(CommandBuffer* _InCommandBuffer) override final;

		void Draw(VertexBuffer* _InVertexBuffer, CommandBuffer* _InCommandBuffer) override final;

		void DrawMultiples(VertexBuffer* _InVertexBuffer, int32_t _InInstanceCount, CommandBuffer* _InCommandBuffer) override final;

		void BindVertexBuffer(VertexBuffer* _InVertexBuffer, CommandBuffer* _InCommandBuffer) override final;

		void BindShaderProgram(Shader* _InShader, CommandBuffer* _InCommandBuffer) override final;

		void SetShaderParameter(Shader* _InShader, const char* _InParameterName, ShaderParameterType _InParameterType, void* _InParam);

		void BeginRenderPass(RenderPass* _InRenderPass, Framebuffer* _InFrameBuffer, CommandBuffer* _InCommandBuffer) override final {};

		void EndRenderPass(CommandBuffer* _InCommandBuffer) override final {};


		void SetViewport(Viewport& _InViewport, CommandBuffer* _InCommandBuffer) override final;

		void SetCullingMode(CullingMode _InCullingMode, CommandBuffer* _InCommandBuffer) override final;

		void SetFillMode(FillMode _InFillMode, CommandBuffer* _InCommandBuffer) override final;


		Image* GetBackBuffer() override final { return nullptr; }

		Image* GetDepthStencilBuffer() override final { return nullptr; }

		Framebuffer* GetBackFramebuffer() override final { return nullptr; }

		RenderPass* GetRenderPass() override final { return nullptr; }


		void BeginFrame() override final;

		void EndFrame() override final;

		void SubmitCommandBuffer(CommandBuffer* _InCommandBuffer) override final;


		VertexBuffer *CreateVertexBuffer(uint32_t _InVertexCount,
                                         TArray<float> &_InData,
                                         TArray<VertexInput> &_InVertexLayout,
                                         uint32_t _InVerticesStride) override final;

		VertexShader* CreateVertexShader(const char* _InShaderCode, size_t _InShaderCodeSize, TArray<VertexInput>& _InVertexInputLayout) override final;
		GeometryShader* CreateGeometryShader(const char* _InShaderCode, size_t _InShaderCodeSize) override final;
		FragmentShader* CreateFragmentShader(const char* _InShaderCode, size_t _InShaderCodeSize) override final;

		Shader* CreateShader(VertexShader* _InVertexShader, GeometryShader* _InGeometryShader, FragmentShader* _InFragmentShader, RenderPass* _InRenderpass) override final;

		CommandBuffer* CreateCommandBuffer() override final;
		virtual RenderPass* CreateRenderPass(TArray<Image*>& _InImage) override final { return nullptr; }
		virtual Framebuffer* CreateFramebuffer(Extent2D& _InFramebufferSize, RenderPass* _InRenderPass) override final { return nullptr; }

	private:

		TArray<OpenGLCommandBuffer*> m_SubmittedCommandBuffers;

		HDC m_HDC = nullptr; // Hardware device context one per rendering thread
		HGLRC m_renderContext = nullptr; // Hardware render context
	};
}

#endif //__OPENGL_RENDER_CONTEXT_HPP_