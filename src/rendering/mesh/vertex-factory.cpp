#include "vertex-factory.hpp"

#include "raw-mesh.hpp"
#include "vertex-input-layout.hpp"

namespace DadEngine
{
    void Vertexfactory::Create(RawMesh &_mesh,
                               TArray<float> &_data,
                               TArray<VertexInput> &_verticesLayout,
                               uint32_t &_stride)
    {
        _mesh.Create(_verticesLayout, _data, _stride);
    }
} // namespace DadEngine
