#include "icomponent.hpp"

#include "actor.hpp"

namespace DadEngine::Gameplay
{
	IComponent::IComponent(Actor* _InOwner)
		: m_Owner(_InOwner)
	{}
}