#include "static-mesh-rendering-feature.hpp"

namespace DadEngine::Rendering
{
    void StaticMeshRenderingFeature::Initialize(RenderingFeatureInfo &_OutInfo)
    {
        _OutInfo.SubmitNode = TRUE;
        _OutInfo.SubmitNodes = TRUE;
    }

    void StaticMeshRenderingFeature::Extract(RenderNode &_InRenderNode)
    {
    }


    void StaticMeshRenderingFeature::SubmitNode(const RenderNode &_InRenderNode, CommandBuffer &_InCommandBuffer)
    {
    }

    void StaticMeshRenderingFeature::SubmitNodes(const TArray<RenderNode> &_InRenderNode, CommandBuffer &_InCommandBuffer)
    {
    }

    void StaticMeshRenderingFeature::SubmitViewBegin(ViewPacket &_InViewPacket, CommandBuffer &_InCommandBuffer)
    {
        //_InCommandBuffer.Clear(Color{1.f, 0.f, 0.f, 1.f});
        //_InCommandBuffer.SetViewport(Viewport{ 0, 0, 1280, 720 });
    }

    void StaticMeshRenderingFeature::SubmitViewEnd(ViewPacket &_InViewPacket, CommandBuffer &_InCommandBuffer)
    {
        //_InCommandBuffer.Present();
    }
} // namespace DadEngine::Rendering