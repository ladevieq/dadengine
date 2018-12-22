#ifndef __STATIC_MESH_RENDERING_FEATURE_HPP_
#define __STATIC_MESH_RENDERING_FEATURE_HPP_

#include "rendering-feature.hpp"

namespace DadEngine::Rendering
{
    class StaticMeshComponent;

	class StaticMeshRenderingFeature : public RenderingFeature<StaticMeshComponent>//public RenderingFeature<StaticMeshRenderingFeature>
	{

	public:

		void Initialize(RenderingFeatureInfo &_OutInfo) override final;

		void Extract(RenderNode &_InRenderNode) override final;


		void SubmitNode(const RenderNode &_InRenderNode, CommandBuffer &_InCommandBuffer) override final;

		void SubmitNodes(const TArray<RenderNode> &_InRenderNode, CommandBuffer &_InCommandBuffer) override final;

		void SubmitViewBegin(ViewPacket &_InViewPacket, CommandBuffer &_InCommandBuffer) override final;

		void SubmitViewEnd(ViewPacket& _InViewPacket, CommandBuffer& _InCommandBuffer) override final;
	};
}

#endif //__STATIC_MESH_RENDERING_FEATURE_HPP_