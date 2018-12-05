#ifndef __STATIC_MESH_RENDERING_FEATURE_HPP_
#define __STATIC_MESH_RENDERING_FEATURE_HPP_

#include "RenderingFeature.hpp"

namespace DadEngine::Rendering
{
	class StaticMeshRenderingFeature : public RenderingFeature<StaticMeshComponent>//public RenderingFeature<StaticMeshRenderingFeature>
	{

	public:

		void Initialize(RenderingFeatureInfo &_OutInfo) override final
		{
			_OutInfo.SubmitNode = TRUE;
			_OutInfo.SubmitNodes = TRUE;
		}

		void Extract(RenderNode& _InRenderNode) override final
		{
		}


		void SubmitNode(const RenderNode& _InRenderNode, CommandBuffer& _InCommandBuffer) override final
		{

		}

		void SubmitNodes(const TArray<RenderNode>& _InRenderNode, CommandBuffer& _InCommandBuffer) override final
		{

		}

		void SubmitViewBegin(ViewPacket& _InViewPacket, CommandBuffer& _InCommandBuffer) override final
		{
			//_InCommandBuffer.Clear(Color{1.f, 0.f, 0.f, 1.f});
			//_InCommandBuffer.SetViewport(Viewport{ 0, 0, 1280, 720 });
		}

		void SubmitViewEnd(ViewPacket& _InViewPacket, CommandBuffer& _InCommandBuffer) override final
		{
			//_InCommandBuffer.Present();
		}
	};
}

#endif //__STATIC_MESH_RENDERING_FEATURE_HPP_