#ifndef __RENDER_CONTEXT_HPP_
#define __RENDER_CONTEXT_HPP_

#include "../Color.hpp"
#include "../VertexBuffer.hpp"
#include "../Shader/Shader.h"

namespace DadEngine::Rendering
{
	struct Viewport
	{
		int32 x;
		int32 y;
		int32 width;
		int32 height;
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

	// CullingMode state -> Per object
	// FillMode state -> Per object
	// Viewport state -> Camera
	// Primitive type state -> Per object

	class RenderContext
	{

	public:


		// Commands
		virtual void ClearBuffer(Color& _InClearColor) = 0;
		virtual void Present() = 0;


		virtual void BeginFrame() = 0;


		virtual void DrawPrimitives() = 0;

		virtual void Draw(VertexBuffer* _InVertexBuffer) = 0;

		virtual void BindVertexBuffer(VertexBuffer* _InVertexBuffer) = 0;

		virtual void BindShaderProgram(Shader* _InShader) = 0;

		// State change commands
		virtual void SetViewport(Viewport& _InViewport) = 0;

		virtual void SetCullingMode(CullingMode _InCullingMode) = 0;

		virtual void SetFillMode(FillMode _InFillMode) = 0;


		virtual VertexBuffer* CreateVertexBuffer(uint32 _InVertexCount, TArray<float>& _InData, TArray<VertexInput>& _InVertexLayout, uint32 _InVerticesStride) = 0;

		virtual VertexShader* CreateVertexShader(const char* _InShaderCode, size_t _InShaderCodeSize, TArray<VertexInput>& _InVertexInputLayout) = 0;
		virtual GeometryShader* CreateGeometryShader(const char* _InShaderCode, size_t _InShaderCodeSize) = 0;
		virtual FragmentShader* CreateFragmentShader(const char* _InShaderCode, size_t _InShaderCodeSize) = 0;

		virtual Shader* CreateShader(VertexShader* _InVertexShader, GeometryShader* _InGeometryShader, FragmentShader* _InFragmentShader) = 0;
	};
}

#endif //__RENDER_CONTEXT_HPP_