#include "RawMesh.hpp"

#include "RawVertex.hpp"
#include "VertexInputLayout.hpp"

namespace DadEngine::Rendering
{
    void RawMesh::Create(const TArray<VertexInput> &_InVerticesLayout, TArray<float> &_OutData, uint32_t &_OutStride)
    {
        for (RawVertex &currentVertex : m_vertices)
        {
            _OutStride = 0U;

            for (VertexInput inputType : _InVerticesLayout)
            {
                if (inputType.uiVertexInputType == VERTEX_INPUT_TYPE_POSITION)
                {
                    _OutStride += sizeof(Vector3f);

                    _OutData.Add(currentVertex.Position.x);
                    _OutData.Add(currentVertex.Position.y);
                    _OutData.Add(currentVertex.Position.z);
                }

                if (inputType.uiVertexInputType == VERTEX_INPUT_TYPE_COLOR)
                {
                    _OutStride += sizeof(Vector3f);

                    _OutData.Add(currentVertex.Color0.x);
                    _OutData.Add(currentVertex.Color0.y);
                    _OutData.Add(currentVertex.Color0.z);
                }
            }
        }
    }
}