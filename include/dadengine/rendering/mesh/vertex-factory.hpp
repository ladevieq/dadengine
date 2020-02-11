#ifndef __VERTEX_FACTORY_HPP_
#define __VERTEX_FACTORY_HPP_

#include "../../core/core.hpp"

namespace DadEngine
{
    class RawMesh;
    struct VertexInput;

    class Vertexfactory
    {

        public:
        static void Create(RawMesh &_mesh,
                           TArray<float> &_data,
                           TArray<VertexInput> &_verticesLayout,
                           uint32_t &_stride);
    };
} // namespace DadEngine

#endif //__VERTEX_FACTORY_HPP_

