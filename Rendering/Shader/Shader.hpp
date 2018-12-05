#ifndef __SHADER_HPP_
#define __SHADER_HPP_

#include "../Mesh/VertexInputLayout.hpp"

namespace DadEngine::Rendering
{
	struct VertexShader
	{
		VertexShader(const char* _InShaderCode, TArray<VertexInput>& _InVertexInputLayout)
			: m_vertexInputLayout(_InVertexInputLayout), m_sCode(_InShaderCode)
		{}

		/*
			0U, VERTEX_INPUT_TYPE_POSITION
			1U, VERTEX_INPUT_TYPE_COLOR0
			2U, VERTEX_INPUT_TYPE_NORMAL
		*/
		TArray<VertexInput> m_vertexInputLayout;
		const char* m_sCode = nullptr;
	};

	struct GeometryShader
	{
		GeometryShader(const char* _InShaderCode)
			: m_sCode(_InShaderCode)
		{}

		const char* m_sCode = nullptr;
	};

	struct FragmentShader
	{
		FragmentShader(const char* _InShaderCode)
			: m_sCode(_InShaderCode)
		{}

		const char* m_sCode = nullptr;
	};


	struct TesselationShader
	{
		TesselationShader(const char* _InShaderCode)
			: m_sCode(_InShaderCode)
		{}

		const char* m_sCode = nullptr;
	};

	struct ComputeShader
	{
		ComputeShader(const char* _InShaderCode)
			: m_sCode(_InShaderCode)
		{}

		const char* m_sCode = nullptr;
	};



	// Tesselation shader ?
	// Pipeline for an object ?
	class Shader
	{

	public:

		Shader(VertexShader* _InVertexShader, GeometryShader* _InGeometryShader, FragmentShader* _InFragmentShader)
			: m_ptrVertexShader(_InVertexShader),
			m_ptrGeometryShader(_InGeometryShader),
			m_ptrFragmentShader(_InFragmentShader)
		{}

		VertexShader* m_ptrVertexShader = nullptr;
		GeometryShader* m_ptrGeometryShader = nullptr;
		FragmentShader* m_ptrFragmentShader = nullptr;
	};
}

#endif //!__SHADER_HPP_