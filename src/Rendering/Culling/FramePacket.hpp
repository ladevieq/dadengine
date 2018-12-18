#ifndef __FRAME_PACKET_HPP_
#define __FRAME_PACKET_HPP_
// Video #3 37:15

#include "../../Core/Core.hpp"

namespace DadEngine::Rendering
{
	class RenderObject;
    class RenderNode;
	class ViewPacket;

	// One frame rendering informations
	class FramePacket
	{

	public:

		void AddViewPacket(const ViewPacket& _InViewPacket);

		template <typename T>
		void AddExtractedRenderObjectData(const RenderObject* _InRenderObject, const T& _InExtractData);

		void Extract();

		bool HasExtracted(RenderObject* _InRenderObject);

		TArray<ViewPacket> m_Packets;
		TArray<RenderNode> m_Nodes;
	};

	template<typename T>
	void FramePacket::AddExtractedRenderObjectData(const RenderObject* _InRenderObject, const T& _InExtractData)
	{
		_InRenderObject->m_renderComponentHandle->Extract(*this);
	}
}

#endif //__FRAME_PACKET_HPP_