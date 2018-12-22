#include "actor.hpp"


namespace DadEngine::Gameplay
{
    Actor::Actor(Actor *_InActor) : m_Parent(_InActor)
    {
    }


    void Actor::MoveLocation(const Vector3f &_InLocation)
    {
        m_Transform.m_Position += _InLocation;
    }

    void Actor::SetLocation(Vector3f &_InPosition)
    {
        m_Transform.m_Position = _InPosition;
    }

    void Actor::SetRotation(float _InAngle, Vector3f &_InVector)
    {
        m_Transform.m_Rotation = Quaternion(_InAngle, _InVector);
    }

    void Actor::SetScale(Vector3f &_InScale)
    {
        m_Transform.m_Scale = _InScale;
    }


    Vector3f Actor::GetAbsoluteLocation()
    {
        Vector3f location = m_Transform.m_Position;

        if (m_Parent)
        {
            location += m_Parent->m_Transform.m_Position;
        }

        return location;
    }

    Vector3f Actor::GetRelativeLocation()
    {
        return m_Transform.m_Position;
    }

	void Actor::SetParent(Actor *_InParent)
    {
        if (m_Parent != _InParent)
            m_Parent = _InParent;
    }

    Actor *Actor::GetParent()
    {
        return m_Parent;
    }
}