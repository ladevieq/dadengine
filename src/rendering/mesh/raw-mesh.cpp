#include "raw-mesh.hpp"

#include "raw-vertex.hpp"
#include "vertex-input-layout.hpp"

namespace DadEngine
{
    void RawMesh::Create(const TArray<VertexInput> &_verticesLayout,
                         TArray<float> &_data,
                         uint32_t &_stride)
    {
        for (RawVertex &currentVertex : m_vertices)
        {
            _stride = 0U;

            for (VertexInput inputType : _verticesLayout)
            {
                if (inputType.vertexInputType == VERTEX_INPUT_TYPE_POSITION)
                {
                    _stride += sizeof(Vector3);

                    _data.Add(currentVertex.position.x);
                    _data.Add(currentVertex.position.y);
                    _data.Add(currentVertex.position.z);
                }

                if (inputType.vertexInputType == VERTEX_INPUT_TYPE_COLOR)
                {
                    _stride += sizeof(Vector3);

                    _data.Add(currentVertex.color0.x);
                    _data.Add(currentVertex.color0.y);
                    _data.Add(currentVertex.color0.z);
                }
            }
        }
    }
} // namespace DadEngine
