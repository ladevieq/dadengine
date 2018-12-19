#include "IComponent.hpp"

#include "Actor.hpp"

namespace DadEngine::Gameplay
{
	IComponent::IComponent(Actor* _InOwner)
		: m_Owner(_InOwner)
	{}
}