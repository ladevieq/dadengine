#include "RenderObject.hpp"

#include "../Feature/RenderComponent.hpp"


namespace DadEngine::Rendering
{
    RenderObject::RenderObject(RenderComponent *_InComponent)
    {
        m_renderComponentHandle = _InComponent;
    }
}