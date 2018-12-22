#ifndef __ACTOR_HPP_
#define __ACTOR_HPP_

#include "../core/core.hpp"
#include "../math/math.hpp"


namespace DadEngine::Gameplay
{
    class IComponent;

	class Actor
	{

	public:

		Actor(Actor *_InActor);


		void MoveLocation(const Vector3f &_InLocation);

		void SetLocation(Vector3f &_InPosition);

		void SetRotation(float _InAngle, Vector3f &_InVector);

		void SetScale(Vector3f &_InScale);


		Vector3f GetAbsoluteLocation();

		Vector3f GetRelativeLocation();


		template<typename T>
		T* AddComponent()
		{
			m_Components.Add(new T{});

			return m_Components.Last();
		}

		template<typename T>
		void AddComponent(T* _InNewComponent)
		{
			m_Components.Add(_InNewComponent);
		}

		template<typename T>
		T* GetComponent()
		{
			for (IComponent* currComp : m_Components)
			{
				if (dynamic_cast<T>(currComp) != nullptr)
					return currComp;
			}
		}

		template<typename T>
		void GetComponents(TArray<T>& _OutComponent)
		{
			for (IComponent* currComp : m_Components)
			{
				if (dynamic_cast<T>(currComp) != nullptr)
					_OutComponent.Add(currComp);
			}
		}


		void SetParent(Actor *_InParent);

		Actor *GetParent();


	private:

		Actor* m_Parent = nullptr;

		Transform3D m_Transform;

		TArray<IComponent*> m_Components;
	};
}

#endif //!__ACTOR_HPP_