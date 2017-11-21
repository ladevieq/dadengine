#ifndef __OPENGL_RENDER_CONTEXT_HPP_
#define __OPENGL_RENDER_CONTEXT_HPP_

#include <Windows.h>
#include <gl/GL.h>
#include "../../Core/Core.hpp"
#include "../RenderContext.hpp"
#include "../../Mesh/RawMesh.hpp"
#include "OpenGLVertexBuffer.hpp"
#include "OpenGLShader.hpp"

namespace DadEngine::Rendering
{
	class OpenGLRenderContext : public RenderContext
	{

	public:

		OpenGLRenderContext(PlatformWindow& _InWindow);


		void ClearBuffer(Color& _InClearColor) override final;

		void Present() override final;


		void BeginFrame() override final {};

		void DrawPrimitives() override final;

		void Draw(VertexBuffer* _InVertexBuffer) override final;

		void BindVertexBuffer(VertexBuffer* _InVertexBuffer) override final;

		void BindShaderProgram(Shader* _InShader) override final;


		void SetViewport(Viewport& _InViewport) override final;

		void SetCullingMode(CullingMode _InCullingMode) override final;

		void SetFillMode(FillMode _InFillMode) override final;


		VertexBuffer* CreateVertexBuffer(uint32 _InVertexCount, TArray<float>& _InData, TArray<VertexInput>& _InVertexLayout, uint32 _InVerticesStride) override final;

		VertexShader* CreateVertexShader(const char* _InShaderCode, size_t _InShaderCodeSize, TArray<VertexInput>& _InVertexInputLayout) override final;
		GeometryShader* CreateGeometryShader(const char* _InShaderCode, size_t _InShaderCodeSize) override final;
		FragmentShader* CreateFragmentShader(const char* _InShaderCode, size_t _InShaderCodeSize) override final;

		Shader* CreateShader(VertexShader* _InVertexShader, GeometryShader* _InGeometryShader, FragmentShader* _InFragmentShader) override final;


	private:

		HDC m_HDC = nullptr; // Hardware device context one per rendering thread
		HGLRC m_renderContext = nullptr; // Hardware render context
	};
}

#endif //__OPENGL_RENDER_CONTEXT_HPP_