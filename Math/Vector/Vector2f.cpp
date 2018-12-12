#include "Vector2f.hpp"

#include "../../Core/Core.hpp"

#include "../MathFunctions.hpp"
#include "../Constants.hpp"


namespace DadEngine::Math
{
    Vector2f::Vector2f(float _InX, float _InY)
    {
        x = _InX;
        y = _InY;
    }


    // Standard vector functions
    void Vector2f::Normalize()
    {
        float length = Length();

        LOG_ASSERT(length > FLOAT_EPSILON, "Vector length is null");

        *this /= length;
    }

	float Vector2f::Length()
    {
        return Square(SqLength());
    }

    float Vector2f::SqLength()
    {
        return x * x + y * y;
    }

    float Vector2f::Angle(Vector2f &_InVector)
    {
        Vector2f tempVec = _InVector / (Length() * _InVector.Length());

        return Acos(Dot(tempVec));
    }

    float Vector2f::Dot(Vector2f &_InVector)
    {
        return x * _InVector.x + y * _InVector.y;
    }

    Vector2f Vector2f::Lerp(Vector2f &_InFrom, Vector2f &_InTo, float _InFactor)
    {
        return Vector2f(
			_InFrom.x + _InFactor * (_InTo.x - _InFrom.x),
			_InFrom.y + _InFactor * (_InTo.y - _InFrom.y)
		);
    }

    // Unary operators
    Vector2f Vector2f::operator-()
    {
        return Vector2f(-x, -y);
    }

    // Binary math operators
    Vector2f Vector2f::operator+(Vector2f &_InVector)
    {
        return Vector2f(x + _InVector.x, y + _InVector.y);
    }

    Vector2f Vector2f::operator-(Vector2f &_InVector)
    {
        return Vector2f(x - _InVector.x, y - _InVector.y);
    }

    Vector2f Vector2f::operator*(float _InVal)
    {
        return Vector2f(x * _InVal, y * _InVal);
    }

    Vector2f Vector2f::operator/(float _InVal)
    {
        return Vector2f(x / _InVal, y / _InVal);
    }

    float Vector2f::operator^(Vector2f &_InVector)
    {
        return x * _InVector.y - y * _InVector.x;
    }


    // Binary assignement math operators
    void Vector2f::operator+=(Vector2f &_InVector)
    {
        x += _InVector.x;
        y += _InVector.y;
    }

    void Vector2f::operator-=(Vector2f &_InVector)
    {
        x -= _InVector.x;
        y -= _InVector.y;
    }

    void Vector2f::operator*=(float _InVal)
    {
        x -= _InVal;
        y -= _InVal;
    }

    void Vector2f::operator/=(float _InVal)
    {
        x /= _InVal;
        y /= _InVal;
    }
}