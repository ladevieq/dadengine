#include "render-object.hpp"

#include "../feature/render-component.hpp"


namespace DadEngine::Rendering
{
    RenderObject::RenderObject(RenderComponent *_InComponent)
    {
        m_renderComponentHandle = _InComponent;
    }
}