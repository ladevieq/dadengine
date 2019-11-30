#include "vector2.hpp"

#include <cmath>


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

        LOG_ASSERT(length > FLOAT_EPSILON, "Vector length is null");

        *this /= length;
    }

    float Vector2::Length()
    {
        return Square(SqLength());
    }

    float Vector2::SqLength()
    {
        return x * x + y * y;
    }

    float Vector2::Angle(Vector2 &_vector)
    {
        Vector2 tempVec = _vector / (Length() * _vector.Length());

        return acos(Dot(tempVec));
    }

    float Vector2::Dot(Vector2 &_vector)
    {
        return x * _vector.x + y * _vector.y;
    }

    Vector2 Vector2::Lerp(Vector2 &_from, Vector2 &_to, float _factor)
    {
        return Vector2f(_from.x + _factor * (_to.x - _from.x),
                        _from.y + _factor * (_to.y - _from.y));
    }

    // Unary operators
    Vector2 Vector2::operator-()
    {
        return Vector2(-x, -y);
    }

    // Binary math operators
    Vector2 Vector2::operator+(Vector2 &_vector)
    {
        return Vector2(x + _vector.x, y + _vector.y);
    }

    Vector2 Vector2::operator-(Vector2 &_vector)
    {
        return Vector2(x - _vector.x, y - _vector.y);
    }

    Vector2 Vector2::operator*(float _val)
    {
        return Vector2(x * _val, y * _val);
    }

    Vector2 Vector2::operator/(float _val)
    {
        return Vector2(x / _val, y / _val);
    }

    float Vector2::operator^(Vector2 &_vector)
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
