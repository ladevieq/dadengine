#include "Vector3f.hpp"

#include "../../Core/Core.hpp"
#include "../Constants.hpp"
#include "../MathFunctions.hpp"


namespace DadEngine::Math
{
    Vector3f::Vector3f(float _InX, float _InY, float _InZ)
    {
        x = _InX;
        y = _InY;
        z = _InZ;
    }


    // Standard vector functions
    void Vector3f::Normalize()
    {
        float length = Length();

        LOG_ASSERT(length > FLOAT_EPSILON, "Vector length is null");

        *this /= length;
    }

    float Vector3f::Length()
    {
        return Square(SqLength());
    }

    float Vector3f::SqLength()
    {
        return x * x + y * y + z * z;
    }

     float Vector3f::Angle(Vector3f &_InVector)
    {
        Vector3f tempVec = _InVector / (Length() * _InVector.Length());

        return Acos(Dot(tempVec));
    }

    float Vector3f::Dot(Vector3f &_InVector)
    {
        return x * _InVector.x + y * _InVector.y + z * _InVector.z;
    }

    Vector3f Vector3f::Lerp(Vector3f &_InFrom, Vector3f &_InTo, float _InFactor)
    {
        return Vector3f(
			_InFrom.x + _InFactor * (_InTo.x - _InFrom.x),
			_InFrom.y + _InFactor * (_InTo.y - _InFrom.y),
			_InFrom.z + _InFactor * (_InTo.z - _InFrom.z)
		);
    }

    // Unary operators
    Vector3f Vector3f::operator-()
    {
        return Vector3f(-x, -y, -z);
    }

    // Binary math operators
    Vector3f Vector3f::operator+(Vector3f &_InVector)
    {
        return Vector3f(x + _InVector.x, y + _InVector.y, z + _InVector.z);
    }

    Vector3f Vector3f::operator-(Vector3f &_InVector)
    {
        return Vector3f(x - _InVector.x, y - _InVector.y, z - _InVector.z);
    }

    Vector3f Vector3f::operator*(float _InVal)
    {
        return Vector3f(x * _InVal, y * _InVal, z * _InVal);
    }

    Vector3f Vector3f::operator/(float _InVal)
    {
        return Vector3f(x / _InVal, y / _InVal, z / _InVal);
    }

    Vector3f Vector3f::operator^(Vector3f &_InVector)
    {
        return Vector3f(y * _InVector.z - z * _InVector.y, z * _InVector.x - x * _InVector.z,
                        x * _InVector.y - y * _InVector.x);
    }


    // Binary assignement math operators
    void Vector3f::operator+=(Vector3f &_InVector)
    {
        x += _InVector.x;
        y += _InVector.y;
        z += _InVector.z;
    }

    void Vector3f::operator+=(const Vector3f &_InVector)
    {
        x += _InVector.x;
        y += _InVector.y;
        z += _InVector.z;
    }

    void Vector3f::operator-=(Vector3f &_InVector)
    {
        x -= _InVector.x;
        y -= _InVector.y;
        z -= _InVector.z;
    }

    void Vector3f::operator-=(const Vector3f &_InVector)
    {
        x -= _InVector.x;
        y -= _InVector.y;
        z -= _InVector.z;
    }

    void Vector3f::operator*=(float _InVal)
    {
        x -= _InVal;
        y -= _InVal;
        z -= _InVal;
    }

    void Vector3f::operator/=(float _InVal)
    {
        x /= _InVal;
        y /= _InVal;
        z /= _InVal;
    }

    void Vector3f::operator^=(Vector3f &_InVector)
    {
        Vector3f temp = *this;

        x = temp.y * _InVector.z - temp.z * _InVector.y,
        y = temp.z * _InVector.x - temp.x * _InVector.z,
        z = temp.x * _InVector.y - temp.y * _InVector.x;
    }
} // namespace DadEngine::Math