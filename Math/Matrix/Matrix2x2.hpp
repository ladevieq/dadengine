#ifndef __MATRIX2X2_HPP_
#define __MATRIX2X2_HPP_

#include "../Vector/Vector2f.hpp"

namespace DadEngine::Math
{
	class Matrix2x2
	{

	public:

		Matrix2x2() = default;

		Matrix2x2(Vector2f _InVectors[2U])
		{
			m_11 = _InVectors[0U].x, m_12 = _InVectors[1U].x;
			m_21 = _InVectors[0U].y, m_22 = _InVectors[1U].y;
		}

		Matrix2x2(float _In11, float _In12, float _In21, float _In22)
		{
			m_11 = _In11, m_12 = _In12;
			m_21 = _In21, m_22 = _In22;
		}

		Matrix2x2(float _InData[4U])
		{
			m_11 = _InData[0U], m_12 = _InData[1U];
			m_21 = _InData[2U], m_22 = _InData[3U];
		}


		// Standard matrix functions
		FORCE_INLINE void SetIdentity()
		{
			m_11 = 1.f, m_12 = 0.f;
			m_21 = 0.f, m_22 = 1.f;
		}

		FORCE_INLINE void Transpose()
		{
			Matrix2x2 temp = *this;

			m_12 = temp.m_21;
			m_21 = temp.m_12;
		}

		FORCE_INLINE void Inverse()
		{
			Matrix2x2 temp = *this;
			float determinant = Determinant();

			if (determinant > FLOAT_EPSILON || determinant < FLOAT_EPSILON)
			{
				determinant = 1.f / determinant;

				m_11 = determinant * temp.m_22, m_12 = determinant * -temp.m_12;
				m_21 = determinant * -temp.m_21, m_22 = determinant * temp.m_11;
			}
		}

		FORCE_INLINE float Determinant()
		{
			return m_11 * m_22 - m_12 * m_21;
		}

		FORCE_INLINE void Rotation(float _InAngle)
		{
			m_11 = Cos(_InAngle), m_12 = -Sin(_InAngle);
			m_12 = Sin(_InAngle), m_12 = Cos(_InAngle);
		}

		FORCE_INLINE void Scale(float _InScaleX, float _InScaleY)
		{
			m_11 = _InScaleX,	m_12 = 0.f;
			m_21 = 0.f,			m_22 = _InScaleY;
		}


		// Binary math operators
		FORCE_INLINE Matrix2x2 operator +(Matrix2x2& _InMatrix)
		{
			Matrix2x2 result;

			result.m_11 = m_11 + _InMatrix.m_11, result.m_12 = m_12 + _InMatrix.m_12;
			result.m_21 = m_21 + _InMatrix.m_21, result.m_22 = m_22 + _InMatrix.m_22;

			return result;
		}

		FORCE_INLINE Matrix2x2 operator -(Matrix2x2& _InMatrix)
		{
			Matrix2x2 result;

			result.m_11 = m_11 - _InMatrix.m_11, result.m_12 = m_12 - _InMatrix.m_12;
			result.m_21 = m_21 - _InMatrix.m_21, result.m_22 = m_22 - _InMatrix.m_22;

			return result;
		}

		FORCE_INLINE Matrix2x2 operator *(float& _InFactor)
		{
			Matrix2x2 result;

			result.m_11 = m_11 * _InFactor, result.m_12 = m_12 * _InFactor;
			result.m_21 = m_21 * _InFactor, result.m_22 = m_22 * _InFactor;

			return result;
		}

		FORCE_INLINE Vector2f operator *(Vector2f& _InVector)
		{
			return Vector2f(m_11 * _InVector.x + m_12 * _InVector.y, m_21 * _InVector.x + m_22 * _InVector.y);
		}

		FORCE_INLINE Matrix2x2 operator *(Matrix2x2& _InMatrix)
		{
			Matrix2x2 result;

			result.m_11 = m_11 * _InMatrix.m_11 + m_12 * _InMatrix.m_21;
			result.m_12 = m_11 * _InMatrix.m_12 + m_12 * _InMatrix.m_22;
			result.m_21 = m_21 * _InMatrix.m_11 + m_22 * _InMatrix.m_21;
			result.m_22 = m_22 * _InMatrix.m_22 + m_21 * _InMatrix.m_12;

			return result;
		}

		FORCE_INLINE Matrix2x2 operator /(float& _InFactor)
		{
			Matrix2x2 result;

			result.m_11 = m_11 / _InFactor, result.m_12 = m_12 / _InFactor;
			result.m_21 = m_21 / _InFactor, result.m_22 = m_22 / _InFactor;

			return result;
		}

		FORCE_INLINE Matrix2x2 operator /(Matrix2x2& _InMatrix)
		{
			Matrix2x2 result;

			_InMatrix.Inverse();

			result = *this * _InMatrix;

			return result;
		}

		// Binary assignement math operators
		FORCE_INLINE void operator +=(Matrix2x2& _InMatrix)
		{
			m_11 += _InMatrix.m_11, m_12 += _InMatrix.m_12;
			m_21 += _InMatrix.m_21, m_22 += _InMatrix.m_22;
		}

		FORCE_INLINE void operator -=(Matrix2x2& _InMatrix)
		{
			m_11 -= _InMatrix.m_11, m_12 -= _InMatrix.m_12;
			m_21 -= _InMatrix.m_21, m_22 -= _InMatrix.m_22;
		}

		FORCE_INLINE void operator *=(float& _InFactor)
		{
			m_11 *= _InFactor, m_12 *= _InFactor;
			m_21 *= _InFactor, m_22 *= _InFactor;
		}

		FORCE_INLINE Vector2f operator *=(Vector2f& _InVector)
		{
			return Vector2f(m_11 * _InVector.x + m_12 * _InVector.y, m_21 * _InVector.x + m_22 * _InVector.y);
		}

		FORCE_INLINE void operator *=(Matrix2x2& _InMatrix)
		{
			Matrix2x2 temp = *this;

			m_11 = temp.m_11 * _InMatrix.m_11 + temp.m_12 * _InMatrix.m_21;
			m_12 = temp.m_11 * _InMatrix.m_12 + temp.m_12 * _InMatrix.m_22;
			m_21 = temp.m_21 * _InMatrix.m_11 + temp.m_22 * _InMatrix.m_21;
			m_22 = temp.m_22 * _InMatrix.m_22 + temp.m_21 * _InMatrix.m_12;
		}

		FORCE_INLINE void operator /=(float& _InFactor)
		{
			m_11 /= _InFactor, m_12 /= _InFactor;
			m_21 /= _InFactor, m_22 /= _InFactor;
		}

		FORCE_INLINE void operator /=(Matrix2x2& _InMatrix)
		{
			_InMatrix.Inverse();

			*this *= _InMatrix;
		}


		float m_11 = 1.f, m_12 = 0.f;
		float m_21 = 0.f, m_22 = 1.f;
	};


	namespace Test
	{
		FORCE_INLINE static void TestMatrix2x2()
		{
			Matrix2x2 m(1, 5, 5, 6);
			Matrix2x2 n(2, 0, 7, 5);
			Vector2f v(10, 5);
			Vector2f w;
			Matrix2x2 o;
			float det = 0.f;

			n.Transpose();
			m.Transpose();
			det = n.Determinant();
			n.Inverse();

			o = m * n;
			w = m * v;
		}
	}
}

#endif //__MATRIX2X2_HPP_