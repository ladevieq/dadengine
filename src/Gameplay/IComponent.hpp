#ifndef __ICOMPONENT_HPP_
#define __ICOMPONENT_HPP_


namespace DadEngine::Gameplay
{
	class Actor;

	class IComponent
	{

	public:

		IComponent() = default;

		IComponent(Actor* _InOwner);


		Actor* m_Owner = nullptr;
	};
}

#endif //!__ICOMPONENT_HPP_