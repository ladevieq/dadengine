#ifndef __RENDER_CONTEXT_HPP_
#define __RENDER_CONTEXT_HPP_

#include "../Color.hpp"
#include "../VertexBuffer.hpp"
#include "../Shader/Shader.hpp"
#include "../RenderPass.hpp"
#include "../Framebuffer.hpp"
#include "../Image.hpp"

namespace DadEngine::Rendering
{
	struct Viewport
	{
        int32_t x;
        int32_t y;
        int32_t width;
        int32_t height;
		//Extent2D extend;
	};

	enum CullingMode
	{
		CLOCKWISE,
		COUNTERCLOCKWISE,
		BOTH,
		MAXCULLINGMODE,
	};

	enum FillMode
	{
		FILL,
		WIREFRAME,
		POINT,
		MAXFILLMODE,
	};

	enum PrimitiveTopology
	{
		TRIANGLE_LIST,
		TRIANGLE_FAN,
		MAX_PIMITIVE_TOPOLOGY,
	};

	enum ShaderParameterType
	{
		SHADER_PARAMETER_TYPE_MATRIX4X4,
		MAX_SHADER_PARAMETER_TYPE,
	};

	// CullingMode state -> Per object
	// FillMode state -> Per object
	// Viewport state -> Camera
	// Primitive type state -> Per object

	class CommandBuffer;

	class RenderContext
	{

	public:


		// Commands
		virtual void ClearColorBuffer(Color& _InClearColor, CommandBuffer* _InCommandBuffer) = 0;

		virtual void ClearDepthStencilBuffer(float _InDepthValue,
                                             uint32_t _InStencilValue,
                                             CommandBuffer *_InCommandBuffer) = 0;

		virtual void Present(CommandBuffer* _InCommandBuffer) = 0;

		virtual void Draw(VertexBuffer* _InVertexBuffer, CommandBuffer* _InCommandBuffer) = 0;

		virtual void DrawMultiples(VertexBuffer *_InVertexBuffer,
                                   int32_t _InInstanceCount,
                                   CommandBuffer *_InCommandBuffer) = 0;

		virtual void BindVertexBuffer(VertexBuffer* _InVertexBuffer, CommandBuffer* _InCommandBuffer) = 0;

		virtual void BindShaderProgram(Shader* _InShader, CommandBuffer* _InCommandBuffer) = 0;

		virtual void BeginRenderPass(RenderPass* _InRenderPass, Framebuffer* _InFrameBuffer, CommandBuffer* _InCommandBuffer) = 0;

		virtual void EndRenderPass(CommandBuffer* _InCommandBuffer) = 0;


		// State change commands
		virtual void SetViewport(Viewport& _InViewport, CommandBuffer* _InCommandBuffer) = 0;

		virtual void SetCullingMode(CullingMode _InCullingMode, CommandBuffer* _InCommandBuffer) = 0;

		virtual void SetFillMode(FillMode _InFillMode, CommandBuffer* _InCommandBuffer) = 0;



		virtual Image* GetBackBuffer() = 0;

		virtual Image* GetDepthStencilBuffer() = 0;

		virtual Framebuffer* GetBackFramebuffer() = 0;

		virtual RenderPass* GetRenderPass() = 0;



		virtual void BeginFrame() = 0;

		virtual void EndFrame() = 0;

		virtual void SubmitCommandBuffer(CommandBuffer* _InCommandBuffer) = 0;


		virtual VertexBuffer *CreateVertexBuffer(uint32_t _InVertexCount,
                                                 TArray<float> &_InData,
                                                 TArray<VertexInput> &_InVertexLayout,
                                                 uint32_t _InVerticesStride) = 0;
		virtual VertexShader* CreateVertexShader(const char* _InShaderCode, size_t _InShaderCodeSize, TArray<VertexInput>& _InVertexInputLayout) = 0;
		virtual GeometryShader* CreateGeometryShader(const char* _InShaderCode, size_t _InShaderCodeSize) = 0;
		virtual FragmentShader* CreateFragmentShader(const char* _InShaderCode, size_t _InShaderCodeSize) = 0;
		virtual Shader* CreateShader(VertexShader* _InVertexShader, GeometryShader* _InGeometryShader, FragmentShader* _InFragmentShader, RenderPass* _InRenderpass) = 0;
		virtual CommandBuffer* CreateCommandBuffer() = 0;
		virtual RenderPass* CreateRenderPass(TArray<Image*>& _InImage) = 0;
		virtual Framebuffer* CreateFramebuffer(Extent2D& _InFramebufferSize, RenderPass* _InRenderPass) = 0;
	};
}

#endif //__RENDER_CONTEXT_HPP_