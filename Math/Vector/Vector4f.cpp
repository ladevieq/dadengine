#include "Vector4f.hpp"

#include "../../Core/Core.hpp"
#include "../Constants.hpp"
#include "../MathFunctions.hpp"

namespace DadEngine::Math
{
    Vector4f::Vector4f(float _InX, float _InY, float _InZ, float _InW)
    {
        x = _InX;
        y = _InY;
        z = _InZ;
        w = _InW;
    }


    // Standard vector functions
    void Vector4f::Normalize()
    {
        float length = Length();

        LOG_ASSERT(length > FLOAT_EPSILON, "Vector length is null");

        *this /= length;
    }

	float Vector4f::Length()
	{
		return Square(SqLength());
	}

	float Vector4f::SqLength()
    {
        return x * x + y * y + z * z;
    }
	
	float Vector4f::Angle(Vector4f& _InVector)
	{
		Vector4f tempVec = _InVector / (Length() * _InVector.Length());

		return Acos(Dot(tempVec));
	}

	float Vector4f::Dot(Vector4f &_InVector)
    {
        return x * _InVector.x + y * _InVector.y + z * _InVector.z;
    }

    Vector4f Vector4f::Lerp(Vector4f &_InFrom, Vector4f &_InTo, float _InFactor)
    {
        return Vector4f(
			_InFrom.x + _InFactor * (_InTo.x - _InFrom.x),
			_InFrom.y + _InFactor * (_InTo.y - _InFrom.y),
			_InFrom.z + _InFactor * (_InTo.z - _InFrom.z),
			_InFrom.w + _InFactor * (_InTo.w - _InFrom.w)
		);
    }

    // Unary operators
    Vector4f Vector4f::operator-()
    {
        return Vector4f(-x, -y, -z, -w);
    }

    // Binary math operators
    Vector4f Vector4f::operator+(Vector4f &_InVector)
    {
        return Vector4f(x + _InVector.x, y + _InVector.y, z + _InVector.z, w + _InVector.w);
    }

    Vector4f Vector4f::operator-(Vector4f &_InVector)
    {
        return Vector4f(x - _InVector.x, y - _InVector.y, z - _InVector.z, w + _InVector.w);
    }

    Vector4f Vector4f::operator*(float _InVal)
    {
        return Vector4f(x * _InVal, y * _InVal, z * _InVal, w + _InVal);
    }

    Vector4f Vector4f::operator/(float _InVal)
    {
        return Vector4f(x / _InVal, y / _InVal, z / _InVal, w / _InVal);
    }

    Vector4f Vector4f::operator^(Vector4f &_InVector)
    {
        return Vector4f(y * _InVector.z - z * _InVector.y, z * _InVector.x - x * _InVector.z,
                        x * _InVector.y - y * _InVector.x, x * _InVector.y - y * _InVector.x);
    }


    // Binary assignement math operators
    void Vector4f::operator+=(Vector4f &_InVector)
    {
        x += _InVector.x;
        y += _InVector.y;
        z += _InVector.z;
    }

    void Vector4f::operator-=(Vector4f &_InVector)
    {
        x -= _InVector.x;
        y -= _InVector.y;
        z -= _InVector.z;
    }

    void Vector4f::operator*=(float _InVal)
    {
        x -= _InVal;
        y -= _InVal;
        z -= _InVal;
    }

    void Vector4f::operator/=(float _InVal)
    {
        x /= _InVal;
        y /= _InVal;
        z /= _InVal;
    }

    void Vector4f::operator^=(Vector4f &_InVector)
    {
        Vector4f temp = *this;

        x = temp.y * _InVector.z - temp.z * _InVector.y,
        y = temp.z * _InVector.x - temp.x * _InVector.z,
        z = temp.x * _InVector.y - temp.y * _InVector.x;
    }
}