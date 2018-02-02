#ifndef __ACTOR_HPP_
#define __ACTOR_HPP_

#include "../Math/Math.hpp"


namespace DadEngine::Gameplay
{
	class Actor
	{

	public:

		Actor(Actor* _InActor)
			: m_Parent(_InActor)
		{}


		FORCE_INLINE void MoveLocation(const Vector3f& _InLocation)
		{
			m_Transform.m_Position += _InLocation;
		}

		FORCE_INLINE void SetLocation(Vector3f& _InPosition)
		{
			m_Transform.m_Position = _InPosition;
		}

		FORCE_INLINE void SetRotation(float _InAngle, Vector3f& _InVector)
		{
			m_Transform.m_Rotation = Quaternion(_InAngle, _InVector);
		}

		FORCE_INLINE void SetScale(Vector3f& _InScale)
		{
			m_Transform.m_Scale =_InScale;
		}


		FORCE_INLINE Vector3f GetAbsoluteLocation()
		{
			Vector3f location = m_Transform.m_Position;

			if (m_Parent)
			{
				location += m_Parent->m_Transform.m_Position;
			}

			return location;
		}

		FORCE_INLINE Vector3f GetRelativeLocation()
		{
			return m_Transform.m_Position;
		}


		template<typename T>
		FORCE_INLINE T* AddComponent()
		{
			m_Components.Add(new T{});

			return m_Components.Last();
		}

		template<typename T>
		FORCE_INLINE void AddComponent(T* _InNewComponent)
		{
			m_Components.Add(_InNewComponent);
		}

		template<typename T>
		FORCE_INLINE T* GetComponent()
		{
			for (IComponent* currComp : m_Components)
			{
				if (dynamic_cast<T>(currComp) != nullptr)
					return currComp;
			}
		}

		template<typename T>
		FORCE_INLINE void GetComponents(TArray<T>& _OutComponent)
		{
			for (IComponent* currComp : m_Components)
			{
				if (dynamic_cast<T>(currComp) != nullptr)
					_OutComponent.Add(currComp);
			}
		}


		FORCE_INLINE void SetParent(Actor* _InParent)
		{
			if(m_Parent != _InParent)
				m_Parent = _InParent;
		}

		FORCE_INLINE Actor* GetParent()
		{
			return m_Parent;
		}


	private:

		Actor* m_Parent = nullptr;

		Transform3D m_Transform;

		TArray<IComponent*> m_Components;
	};
}

#endif //!__ACTOR_HPP_