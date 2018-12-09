#include "ViewPacket.hpp"

namespace DadEngine::Rendering
{
	// Hotfix aui pus la merde
	ViewPacket::ViewPacket() : m_VisibleObjects(0U) {}

	void ViewPacket::AddRenderObject(RenderObject * _InVisibleObject)
	{
		//FramePacket p;

		//_InVisibleObject->m_renderComponentHandle->Extract(p);

		m_VisibleObjects.Add(_InVisibleObject);
	}
	
	void ViewPacket::ExtractObjects(FramePacket& _InFramePacket)
	{
		for (RenderObject* currentObject : m_VisibleObjects)
		{
			if (_InFramePacket.HasExtracted(currentObject) == FALSE)
			{
				currentObject->m_renderComponentHandle->Extract(_InFramePacket);
			}
		}
	}
}