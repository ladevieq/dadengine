#ifndef __SHADER_HPP_
#define __SHADER_HPP_

#include "../../core/core.hpp"

namespace DadEngine
{
    struct VertexInput;

    struct VertexShader
    {
        VertexShader(const char *_InShaderCode, TArray<VertexInput> &_InVertexInputLayout);

        virtual ~VertexShader()
        {
        }

        /*
            0U, VERTEX_INPUT_TYPE_POSITION
            1U, VERTEX_INPUT_TYPE_COLOR0
            2U, VERTEX_INPUT_TYPE_NORMAL
        */
        TArray<VertexInput> m_vertexInputLayout;
        const char *m_code = nullptr;
    };

    struct GeometryShader
    {
        GeometryShader(const char *_shaderCode) : m_code(_shaderCode)
        {
        }

        virtual ~GeometryShader()
        {
        }

        const char *m_code = nullptr;
    };

    struct FragmentShader
    {
        FragmentShader(const char *_shaderCode) : m_code(_shaderCode)
        {
        }

        virtual ~FragmentShader()
        {
        }

        const char *m_code = nullptr;
    };


    struct TesselationShader
    {
        TesselationShader(const char *_shaderCode) : m_code(_shaderCode)
        {
        }

        virtual ~TesselationShader()
        {
        }

        const char *m_code = nullptr;
    };

    struct ComputeShader
    {
        ComputeShader(const char *_shaderCode) : m_code(_shaderCode)
        {
        }

        virtual ~ComputeShader()
        {
        }

        const char *m_code = nullptr;
    };


    // Tesselation shader ?
    // Pipeline for an object ?
    class Shader
    {

        public:
        Shader(VertexShader *_vertexShader, GeometryShader *_geometryShader, FragmentShader *_fragmentShader)
            : m_ptrVertexShader(_vertexShader), m_ptrGeometryShader(_geometryShader),
              m_ptrFragmentShader(_fragmentShader)
        {
        }

        virtual ~Shader()
        {
        }

        VertexShader *m_ptrVertexShader = nullptr;
        GeometryShader *m_ptrGeometryShader = nullptr;
        FragmentShader *m_ptrFragmentShader = nullptr;
    };
} // namespace DadEngine

#endif //!__SHADER_HPP_
