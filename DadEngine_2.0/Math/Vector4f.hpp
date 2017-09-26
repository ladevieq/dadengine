#ifndef __VECTOR4F_HPP_
#define __VECTOR4F_HPP_

#include "../Core/Core.hpp"
#include "Constants.hpp"

namespace DadEngine::Math
{
	class Vector4f
	{

	public:

		Vector4f() = default;

		Vector4f(float _InX, float _InY, float _InZ, float _InW)
		{
			x = _InX;
			y = _InY;
			z = _InZ;
			w = _InW;
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

		float Angle(Vector4f& _InVector);

		FORCE_INLINE float Dot(Vector4f& _InVector)
		{
			return x * _InVector.x + y * _InVector.y + z * _InVector.z;
		}

		FORCE_INLINE Vector4f& Lerp(Vector4f& _InFrom, Vector4f& _InTo, float _InFactor)
		{
			x = _InFrom.x + _InFactor * (_InTo.x - _InFrom.x);
			y = _InFrom.y + _InFactor * (_InTo.y - _InFrom.y);
			z = _InFrom.z + _InFactor * (_InTo.z - _InFrom.z);
			w = _InFrom.w + _InFactor * (_InTo.w - _InFrom.w);
		}

		// Unary operators
		FORCE_INLINE Vector4f operator-()
		{
			return Vector4f(-x, -y, -z, -w);
		}

		// Binary math operators
		FORCE_INLINE Vector4f operator+(Vector4f& _InVector)
		{
			return Vector4f(x + _InVector.x, y + _InVector.y, z + _InVector.z, w + _InVector.w);
		}

		FORCE_INLINE Vector4f operator-(Vector4f& _InVector)
		{
			return Vector4f(x - _InVector.x, y - _InVector.y, z - _InVector.z, w + _InVector.w);
		}

		FORCE_INLINE Vector4f operator*(float _InVal)
		{
			return Vector4f(x *_InVal, y * _InVal, z * _InVal, w + _InVal);
		}

		FORCE_INLINE Vector4f operator/(float _InVal)
		{
			return Vector4f(x / _InVal, y / _InVal, z / _InVal, w / _InVal);
		}

		FORCE_INLINE Vector4f operator^(Vector4f& _InVector)
		{
			return Vector4f(y * _InVector.z - z * _InVector.y,
							z * _InVector.x - x * _InVector.z,
							x * _InVector.y - y * _InVector.x,
							x * _InVector.y - y * _InVector.x);
		}


		// Binary assignement math operators
		FORCE_INLINE void operator+=(Vector4f& _InVector)
		{
			x += _InVector.x;
			y += _InVector.y;
			z += _InVector.z;
		}

		FORCE_INLINE void operator-=(Vector4f& _InVector)
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

		FORCE_INLINE void operator^=(Vector4f& _InVector)
		{
			Vector4f temp = *this;

			x = temp.y * _InVector.z - temp.z * _InVector.y,
			y = temp.z * _InVector.x - temp.x * _InVector.z,
			z = temp.x * _InVector.y - temp.y * _InVector.x;
		}


		float x = 0.f;
		float y = 0.f;
		float z = 0.f;
		float w = 0.f;
	};
}

#endif //__VECTOR4F_HPP_