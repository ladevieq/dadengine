#include "vector/vector2.hpp"

#include "constants.hpp"


namespace DadEngine
{
    Vector2::Vector2(float _x, float _y)
    {
        x = _x;
        y = _y;
    }


    // Standard vector functions
    void Vector2::Normalize()
    {
        float length = Length();
        *this /= length;
    }

    float Vector2::Length() const
    {
        return std::sqrt(SqLength());
    }

    float Vector2::SqLength() const
    {
        return x * x + y * y;
    }

    float Vector2::Angle(Vector2 &_vector) const
    {
        Vector2 tempVec = _vector / (Length() * _vector.Length());

        return std::acos(Dot(tempVec));
    }

    float Vector2::Dot(Vector2 &_vector) const
    {
        return x * _vector.x + y * _vector.y;
    }

    Vector2 Vector2::Lerp(Vector2 &_from, Vector2 &_to, float _factor)
    {
        return Vector2(_from.x + _factor * (_to.x - _from.x),
                       _from.y + _factor * (_to.y - _from.y));
    }

    // Unary operators
    Vector2 Vector2::operator-() const
    {
        return Vector2(-x, -y);
    }

    // Binary math operators
    Vector2 Vector2::operator+(Vector2 &_vector) const
    {
        return Vector2(x + _vector.x, y + _vector.y);
    }

    Vector2 Vector2::operator-(Vector2 &_vector) const
    {
        return Vector2(x - _vector.x, y - _vector.y);
    }

    Vector2 Vector2::operator*(float _val) const
    {
        return Vector2(x * _val, y * _val);
    }

    Vector2 Vector2::operator/(float _val) const
    {
        return Vector2(x / _val, y / _val);
    }

    float Vector2::operator^(Vector2 &_vector) const
    {
        return x * _vector.y - y * _vector.x;
    }


    // Binary assignement math operators
    void Vector2::operator+=(Vector2 &_vector)
    {
        x += _vector.x;
        y += _vector.y;
    }

    void Vector2::operator-=(Vector2 &_vector)
    {
        x -= _vector.x;
        y -= _vector.y;
    }

    void Vector2::operator*=(float _val)
    {
        x -= _val;
        y -= _val;
    }

    void Vector2::operator/=(float _val)
    {
        x /= _val;
        y /= _val;
    }
} // namespace DadEngine
