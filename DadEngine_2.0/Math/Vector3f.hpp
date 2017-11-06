#ifndef __VECTOR3F_HPP_
#define __VECTOR3F_HPP_

#include "../Core/Core.hpp"
#include "Constants.hpp"

namespace DadEngine::Math
{
	class Vector3f
	{

	public:

		Vector3f() = default;

		Vector3f(float _InX, float _InY, float _InZ)
		{
			x = _InX;
			y = _InY;
			z = _InZ;
		}


		// Standard vector functions
		FORCE_INLINE void Normalize()
		{
			float length = Length();

			LOG_ASSERT(length > FLOAT_EPSILON, "Vector length is null");

			*this /= length;
		}

		float Length();

		FORCE_INLINE float SqLength()
		{
			return x * x + y * y + z * z;
		}

		float Angle(Vector3f& _InVector);

		FORCE_INLINE float Dot(Vector3f& _InVector)
		{
			return x * _InVector.x + y * _InVector.y + z * _InVector.z;
		}

		FORCE_INLINE Vector3f& Lerp(Vector3f& _InFrom, Vector3f& _InTo, float _InFactor)
		{
			x = _InFrom.x + _InFactor * (_InTo.x - _InFrom.x);
			y = _InFrom.y + _InFactor * (_InTo.y - _InFrom.y);
			z = _InFrom.z + _InFactor * (_InTo.z - _InFrom.z);
		}

		// Unary operators
		FORCE_INLINE Vector3f operator-()
		{
			return Vector3f(-x, -y, -z);
		}

		// Binary math operators
		FORCE_INLINE Vector3f operator+(Vector3f& _InVector)
		{
			return Vector3f(x + _InVector.x, y + _InVector.y, z + _InVector.z);
		}

		FORCE_INLINE Vector3f operator-(Vector3f& _InVector)
		{
			return Vector3f(x - _InVector.x, y - _InVector.y, z - _InVector.z);
		}

		FORCE_INLINE Vector3f operator*(float _InVal)
		{
			return Vector3f(x *_InVal, y * _InVal, z * _InVal);
		}

		FORCE_INLINE Vector3f operator/(float _InVal)
		{
			return Vector3f(x / _InVal, y / _InVal, z / _InVal);
		}

		FORCE_INLINE Vector3f operator^(Vector3f& _InVector)
		{
			return Vector3f(y * _InVector.z - z * _InVector.y,
							z * _InVector.x - x * _InVector.z,
							x * _InVector.y - y * _InVector.x);
		}


		// Binary assignement math operators
		FORCE_INLINE void operator+=(Vector3f& _InVector)
		{
			x += _InVector.x;
			y += _InVector.y;
			z += _InVector.z;
		}

		FORCE_INLINE void operator-=(Vector3f& _InVector)
		{
			x -= _InVector.x;
			y -= _InVector.y;
			z -= _InVector.z;
		}

		FORCE_INLINE void operator*=(float _InVal)
		{
			x -= _InVal;
			y -= _InVal;
			z -= _InVal;
		}

		FORCE_INLINE void operator/=(float _InVal)
		{
			x /= _InVal;
			y /= _InVal;
			z /= _InVal;
		}

		FORCE_INLINE void operator^=(Vector3f& _InVector)
		{
			Vector3f temp = *this;

			x = temp.y * _InVector.z - temp.z * _InVector.y,
			y = temp.z * _InVector.x - temp.x * _InVector.z,
			z = temp.x * _InVector.y - temp.y * _InVector.x;
		}


		float x = 0.f;
		float y = 0.f;
		float z = 0.f;
	};

	static const Vector3f NullVector3f(0.f, 0.f, 0.f);
}

#endif //__VECTOR3F_HPP_