#include "shader.hpp"

#include "../mesh/vertex-input-layout.hpp"

namespace DadEngine
{
    VertexShader::VertexShader(const char *_shaderCode, TArray<VertexInput> &_vertexInputLayout)
        : m_vertexInputLayout(_vertexInputLayout), m_code(_shaderCode)
    {
    }
} // namespace DadEngine
