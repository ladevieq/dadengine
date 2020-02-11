#ifndef __RAW_MESH_HPP_
#define __RAW_MESH_HPP_

#include "../../core/core.hpp"
#include "raw-vertex.hpp"


namespace DadEngine
{
    struct VertexInput;

    // Convert concrete files data into this data structure
    class RawMesh
    {

        public:
        void Create(const TArray<VertexInput> &_verticesLayout,
                    TArray<float> &_data,
                    uint32_t &_stride);


        TArray<RawVertex> m_vertices;
    };
} // namespace DadEngine

#endif // !__RAW_MESH_HPP_

