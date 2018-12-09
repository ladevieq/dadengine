#ifndef __VECTOR2F_HPP_
#define __VECTOR2F_HPP_

#include "../../Core/Core.hpp"
#include "../Constants.hpp"

namespace DadEngine::Math
{
	class Vector2f
	{

	public:

		Vector2f() = default;

		Vector2f(float _InX, float _InY)
		{
			x = _InX;
			y = _InY;
		}


		// Standard vector functions
		FORCE_INLINE void Normalize()
		{
			float length = Length();

			LOG_ASSERT(length > FLOAT_EPSILON, "Vector length is null");

			*this /= length;
		}

		FORCE_INLINE void Reflect();

		FORCE_INLINE void Projection();

		float Length();

		FORCE_INLINE float SqLength()
		{
			return x * x + y * y;
		}

		float Angle(Vector2f& _InVector);

		FORCE_INLINE float Dot(Vector2f& _InVector)
		{
			return x * _InVector.x + y * _InVector.y;
		}

		FORCE_INLINE Vector2f& Lerp(Vector2f& _InFrom, Vector2f& _InTo, float _InFactor)
		{
			x = _InFrom.x + _InFactor * (_InTo.x - _InFrom.x);
			y = _InFrom.y + _InFactor * (_InTo.y - _InFrom.y);
		}

		// Unary operators
		FORCE_INLINE Vector2f operator-()
		{
			return Vector2f(-x, -y);
		}

		// Binary math operators
		FORCE_INLINE Vector2f operator+(Vector2f& _InVector)
		{
			return Vector2f(x + _InVector.x, y + _InVector.y);
		}

		FORCE_INLINE Vector2f operator-(Vector2f& _InVector)
		{
			return Vector2f(x - _InVector.x, y - _InVector.y);
		}

		FORCE_INLINE Vector2f operator*(float _InVal)
		{
			return Vector2f(x *_InVal, y * _InVal);
		}

		FORCE_INLINE Vector2f operator/(float _InVal)
		{
			return Vector2f(x / _InVal, y / _InVal);
		}

		FORCE_INLINE float operator^(Vector2f& _InVector)
		{
			return x * _InVector.y - y * _InVector.x;
		}


		// Binary assignement math operators
		FORCE_INLINE void operator+=(Vector2f& _InVector)
		{
			x += _InVector.x;
			y += _InVector.y;
		}

		FORCE_INLINE void operator-=(Vector2f& _InVector)
		{
			x -= _InVector.x;
			y -= _InVector.y;
		}

		FORCE_INLINE void operator*=(float _InVal)
		{
			x -= _InVal;
			y -= _InVal;
		}

		FORCE_INLINE void operator/=(float _InVal)
		{
			x /= _InVal;
			y /= _InVal;
		}


		float x = 0.f;
		float y = 0.f;
	};
}

#endif //__VECTOR2F_HPP_