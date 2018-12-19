#include "Shader.hpp"

#include "../Mesh/VertexInputLayout.hpp"

namespace DadEngine::Rendering
{
    VertexShader::VertexShader(const char *_InShaderCode, TArray<VertexInput> &_InVertexInputLayout)
        : m_vertexInputLayout(_InVertexInputLayout), m_sCode(_InShaderCode)
    {
    }
} // namespace DadEngine::Rendering