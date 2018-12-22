#include "vertex-factory.hpp"

#include "vertex-input-layout.hpp"
#include "raw-mesh.hpp"

namespace DadEngine::Rendering
{
    void Vertexfactory::Create(RawMesh &_InMesh,
                                      TArray<float> &_OutData,
                                      TArray<VertexInput> &_InVerticesLayout,
                                      uint32_t &_OutStride)
    {
        _InMesh.Create(_InVerticesLayout, _OutData, _OutStride);
    }
} // namespace DadEngine::Rendering