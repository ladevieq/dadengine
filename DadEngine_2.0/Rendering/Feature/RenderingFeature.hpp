#ifndef __RENDERING_FEATURE_HPP_
#define __RENDERING_FEATURE_HPP_

#include "../Culling/ViewPacket.hpp"
#include "../Culling/RenderNode.hpp"
#include "../CommandBuffer.hpp"
#include "../Culling/RenderObject.hpp"
#include "../../Core/Core.hpp"

namespace DadEngine::Rendering
{
	struct RenderingFeatureInfo
	{
		uint8 SubmitNode : 1;
		uint8 SubmitNodes : 1;
	};

	template<typename T>
	class RenderingFeature
	{

	public:

		RenderObject* AddComponent(T* _InComponent)
		{
			RenderObject* renderObjectHandle = new RenderObject(_InComponent);
			renderObjectHandle->m_renderComponentHandle = _InComponent;

			m_renderObjects.Add(renderObjectHandle);

			_InComponent->m_RenderObjectHandle = renderObjectHandle;

			return renderObjectHandle;
		}

		void RemoveComponent(T* _InComponent);


		virtual void Initialize(RenderingFeatureInfo &_OutInfo) = 0;

		// Copy the node data over to the gpu
		virtual void Extract(RenderNode& _InRenderNode) = 0;

		// Submit rendering commands for each RenerNode
		virtual void SubmitNode(const RenderNode& _InRenderNode, CommandBuffer& _InCommandBuffer) = 0;

		// Submit all rendering feature RenderNodes
		virtual void SubmitNodes(const TArray<RenderNode>& _InRenderNode, CommandBuffer& _InCommandBuffer) = 0;

		// Frame begin
		virtual void SubmitViewBegin(ViewPacket& _InViewPacket, CommandBuffer& _InCommandBuffer) = 0;

		// Frame end
		virtual void SubmitViewEnd(ViewPacket& _InViewPacket, CommandBuffer& _InCommandBuffer) = 0;


	private:

		TArray<RenderObject*> m_renderObjects;

	};
}

#endif //__RENDERING_FEATURE_HPP_