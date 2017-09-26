#ifndef __MATRIX3X3_HPP_
#define __MATRIX3X3_HPP_

namespace DadEngine::Math
{
	class Matrix3x3
	{

	public:

		Matrix3x3() = default;

		Matrix3x3(Vector3f _InVectors[3U])
		{
			m_11 = _InVectors[0U].x, m_12 = _InVectors[1U].x, m_13 = _InVectors[2U].x;
			m_21 = _InVectors[0U].y, m_22 = _InVectors[1U].y, m_23 = _InVectors[2U].y;
			m_31 = _InVectors[0U].z, m_32 = _InVectors[1U].z, m_33 = _InVectors[2U].z;
		}

		Matrix3x3(	float _In11, float _In12, float _In13,
					float _In21, float _In22, float _In23,
					float _In31, float _In32, float _In33)
		{
			m_11 = _In11, m_12 = _In12, m_13 = _In13;
			m_21 = _In21, m_22 = _In22, m_23 = _In23;
			m_31 = _In31, m_32 = _In32, m_33 = _In33;
		}

		Matrix3x3(float _InData[9U])
		{
			m_11 = _InData[0U], m_12 = _InData[1U], m_13 = _InData[2U];
			m_21 = _InData[3U], m_22 = _InData[4U], m_23 = _InData[5U];
			m_31 = _InData[6U], m_32 = _InData[7U], m_33 = _InData[8U];
		}


		// Standard matrix functions
		FORCE_INLINE void SetIdentity()
		{
			m_11 = 1.f, m_12 = 0.f, m_13 = 0.f;
			m_21 = 0.f, m_22 = 1.f, m_23 = 0.f;
			m_31 = 0.f, m_32 = 0.f, m_33 = 1.f;
		}

		FORCE_INLINE void Transpose()
		{
			Matrix3x3 temp = *this;

			m_12 = m_21;
			m_13 = m_31;
			m_23 = m_32;

			m_21 = temp.m_12;
			m_31 = temp.m_13;
			m_32 = temp.m_23;
		}

		FORCE_INLINE void Inverse()
		{
			float cof11 = (m_22 * m_33 - m_23 * m_32), cof12 = -(m_21 * m_33 - m_23 * m_31), cof13 = (m_21 * m_32 - m_22 * m_31);
			float determinant = m_11 * cof11 + m_12 * cof12 + m_13 * cof13;

			if (determinant > FLOAT_EPSILON || determinant < FLOAT_EPSILON)
			{
				determinant = 1.f / determinant;
				float cof21 = -(m_12 * m_33 - m_13 * m_32),	cof22 = (m_11 * m_33 - m_13 * m_31),	cof23 = -(m_11 * m_32 - m_12 * m_31);
				float cof31 = (m_12 * m_23 - m_13 * m_22),	cof32 = -(m_11 * m_23 - m_13 * m_21),	cof33 = (m_11 * m_22 - m_12 * m_21);

				m_11 = cof11 * determinant, m_12 = cof12 * determinant, m_13 = cof13 * determinant;
				m_21 = cof21 * determinant, m_22 = cof22 * determinant, m_23 = cof23 * determinant;
				m_31 = cof31 * determinant, m_32 = cof32 * determinant, m_33 = cof33 * determinant;

				//Transpose();
			}
		}

		FORCE_INLINE float Determinant()
		{
			float cof11 = (m_22 * m_33 - m_23 * m_32), cof12 = -(m_21 * m_33 - m_23 * m_31), cof13 = (m_21 * m_32 - m_22 * m_31);

			return m_11 * cof11 + m_12 * cof12 + m_13 * cof13;
		}

		FORCE_INLINE void RotationX(float _InAngle)
		{
			float cos = Cos(_InAngle);
			float sin = Sin(_InAngle);

			m_11 = 1.f, m_12 = 0.f, m_13 = 0.f;
			m_21 = 0.f, m_22 = cos, m_23 = -sin;
			m_31 = 0.f, m_32 = sin, m_33 = cos;
		}

		FORCE_INLINE void RotationY(float _InAngle)
		{
			float cos = Cos(_InAngle);
			float sin = Sin(_InAngle);

			m_11 = cos, m_12 = 0.f, m_13 = sin;
			m_21 = 0.f, m_22 = 1.f, m_23 = 0.f;
			m_31 = -sin, m_32 = 0.f, m_33 = cos;
		}

		FORCE_INLINE void RotationZ(float _InAngle)
		{
			float cos = Cos(_InAngle);
			float sin = Sin(_InAngle);

			m_11 = cos, m_12 = -sin, m_13 = 0.f;
			m_21 = sin, m_22 = cos, m_23 = 0.f;
			m_31 = 0.f, m_32 = 0.f, m_33 = 1.f;

		}

		FORCE_INLINE void Rotation(float _InAngle, Vector3f _InAxis)
		{
			float cos = Cos(_InAngle);
			float sin = Sin(_InAngle);
			float cosLessOne = 1 - cos;

			m_11 = cos + (cosLessOne * _InAxis.x * _InAxis.x), m_12 = (cosLessOne * _InAxis.x * _InAxis.y) - (sin * _InAxis.z), m_13 = (cosLessOne * _InAxis.x * _InAxis.z) + (sin * _InAxis.y);
			m_21 = (cosLessOne * _InAxis.x * _InAxis.y) + (sin * _InAxis.z), m_22 = cos + (cosLessOne * _InAxis.y * _InAxis.y), m_23 = (cosLessOne * _InAxis.y * _InAxis.z) - (sin * _InAxis.x);
			m_31 = (cosLessOne * _InAxis.x * _InAxis.z) - (sin * _InAxis.y), m_32 = (cosLessOne * _InAxis.y * _InAxis.z) + (sin * _InAxis.x), m_33 = cos + (cosLessOne * _InAxis.z * _InAxis.z);
		}

		FORCE_INLINE void Scale(float _InScaleX, float _InScaleY, float _InScaleZ)
		{
			m_11 = _InScaleX, m_12 = 0.f, m_13 = 0.f;
			m_21 = 0.f, m_22 = _InScaleY, m_23 = 0.f;
			m_31 = 0.f, m_32 = 0.f, m_33 = _InScaleZ;
		}

		FORCE_INLINE void Translation(Vector2f _InTranslation)
		{
			m_11 = 0.f, m_12 = 0.f, m_13 = _InTranslation.x;
			m_21 = 0.f, m_22 = 0.f, m_23 = _InTranslation.y;
			m_31 = 0.f, m_32 = 0.f, m_33 = 1.f;
		}


		// Binary math operators
		FORCE_INLINE Matrix3x3 operator +(Matrix3x3& _InMatrix)
		{
			Matrix3x3 result;

			result.m_11 = m_11 + _InMatrix.m_11, result.m_12 = m_12 + _InMatrix.m_12, result.m_13 = m_13 + _InMatrix.m_13;
			result.m_21 = m_21 + _InMatrix.m_21, result.m_22 = m_22 + _InMatrix.m_22, result.m_23 = m_23 + _InMatrix.m_23;
			result.m_31 = m_31 + _InMatrix.m_31, result.m_32 = m_32 + _InMatrix.m_32, result.m_33 = m_33 + _InMatrix.m_33;

			return result;
		}

		FORCE_INLINE Matrix3x3 operator -(Matrix3x3& _InMatrix)
		{
			Matrix3x3 result;

			result.m_11 = m_11 - _InMatrix.m_11, result.m_12 = m_12 - _InMatrix.m_12, result.m_13 = m_13 - _InMatrix.m_13;
			result.m_21 = m_21 - _InMatrix.m_21, result.m_22 = m_22 - _InMatrix.m_22, result.m_23 = m_23 - _InMatrix.m_23;
			result.m_31 = m_31 - _InMatrix.m_31, result.m_32 = m_32 - _InMatrix.m_32, result.m_33 = m_33 - _InMatrix.m_33;

			return result;
		}

		FORCE_INLINE Matrix3x3 operator *(float& _InFactor)
		{
			Matrix3x3 result;

			result.m_11 = m_11 * _InFactor, result.m_12 = m_12 * _InFactor, result.m_13 = m_13 * _InFactor;
			result.m_21 = m_21 * _InFactor, result.m_22 = m_22 * _InFactor, result.m_23 = m_23 * _InFactor;
			result.m_31 = m_31 * _InFactor, result.m_32 = m_32 * _InFactor, result.m_33 = m_33 * _InFactor;

			return result;
		}

		FORCE_INLINE Vector3f operator *(Vector3f& _InVector)
		{
			return Vector3f(m_11 * _InVector.x + m_12 * _InVector.y + m_13 * _InVector.z,
							m_21 * _InVector.x + m_22 * _InVector.y + m_23 * _InVector.z,
							m_31 * _InVector.x + m_32 * _InVector.y + m_33 * _InVector.z);
		}

		FORCE_INLINE Matrix3x3 operator *(Matrix3x3& _InMatrix)
		{
			Matrix3x3 result;

			result.m_11 = m_11 * _InMatrix.m_11 + m_12 * _InMatrix.m_21 + m_13 * _InMatrix.m_31;
			result.m_12 = m_11 * _InMatrix.m_12 + m_12 * _InMatrix.m_22 + m_13 * _InMatrix.m_32;
			result.m_13 = m_11 * _InMatrix.m_13 + m_12 * _InMatrix.m_23 + m_13 * _InMatrix.m_33;
			result.m_21 = m_21 * _InMatrix.m_11 + m_22 * _InMatrix.m_21 + m_23 * _InMatrix.m_31;
			result.m_22 = m_21 * _InMatrix.m_12 + m_22 * _InMatrix.m_22 + m_23 * _InMatrix.m_32;
			result.m_23 = m_21 * _InMatrix.m_13 + m_22 * _InMatrix.m_23 + m_23 * _InMatrix.m_33;
			result.m_31 = m_31 * _InMatrix.m_11 + m_32 * _InMatrix.m_21 + m_33 * _InMatrix.m_31;
			result.m_32 = m_31 * _InMatrix.m_12 + m_32 * _InMatrix.m_22 + m_33 * _InMatrix.m_32;
			result.m_33 = m_31 * _InMatrix.m_13 + m_32 * _InMatrix.m_23 + m_33 * _InMatrix.m_33;

			return result;
		}

		FORCE_INLINE Matrix3x3 operator /(float& _InFactor)
		{
			Matrix3x3 result;

			result.m_11 = m_11 / _InFactor, result.m_12 = m_12 / _InFactor, result.m_13 = m_13 / _InFactor;
			result.m_21 = m_21 / _InFactor, result.m_22 = m_22 / _InFactor, result.m_23 = m_23 / _InFactor;
			result.m_31 = m_31 / _InFactor, result.m_32 = m_32 / _InFactor, result.m_33 = m_33 / _InFactor;

			return result;
		}

		FORCE_INLINE Matrix3x3 operator /(Matrix3x3& _InMatrix)
		{
			Matrix3x3 result;

			_InMatrix.Inverse();

			result = *this * _InMatrix;

			return result;
		}

		// Binary assignement math operators
		FORCE_INLINE void operator +=(Matrix3x3& _InMatrix)
		{
			m_11 += _InMatrix.m_11, m_12 += _InMatrix.m_12, m_13 += _InMatrix.m_13;
			m_21 += _InMatrix.m_21, m_22 += _InMatrix.m_22, m_23 += _InMatrix.m_23;
			m_31 += _InMatrix.m_31, m_32 += _InMatrix.m_32, m_33 += _InMatrix.m_33;
		}

		FORCE_INLINE void operator -=(Matrix3x3& _InMatrix)
		{
			m_11 -= _InMatrix.m_11, m_12 -= _InMatrix.m_12, m_13 -= _InMatrix.m_13;
			m_21 -= _InMatrix.m_21, m_22 -= _InMatrix.m_22, m_23 -= _InMatrix.m_23;
			m_31 -= _InMatrix.m_31, m_32 -= _InMatrix.m_32, m_33 -= _InMatrix.m_33;
		}

		FORCE_INLINE void operator *=(float& _InFactor)
		{
			m_11 *= _InFactor, m_12 *= _InFactor, m_13 *= _InFactor;
			m_21 *= _InFactor, m_22 *= _InFactor, m_23 *= _InFactor;
			m_31 *= _InFactor, m_32 *= _InFactor, m_33 *= _InFactor;
		}

		FORCE_INLINE Vector3f operator *=(Vector3f& _InVector)
		{
			return Vector3f(m_11 * _InVector.x + m_12 * _InVector.y + m_13 * _InVector.z,
							m_21 * _InVector.x + m_22 * _InVector.y + m_23 * _InVector.z,
							m_31 * _InVector.x + m_32 * _InVector.y + m_33 * _InVector.z);
		}

		FORCE_INLINE void operator *=(Matrix3x3& _InMatrix)
		{
			Matrix3x3 temp = *this;

			m_11 = temp.m_11 * _InMatrix.m_11 + temp.m_12 * _InMatrix.m_21 + temp.m_13 * _InMatrix.m_31;
			m_12 = temp.m_11 * _InMatrix.m_12 + temp.m_12 * _InMatrix.m_22 + temp.m_13 * _InMatrix.m_32;
			m_13 = temp.m_11 * _InMatrix.m_13 + temp.m_12 * _InMatrix.m_23 + temp.m_13 * _InMatrix.m_33;

			m_21 = temp.m_21 * _InMatrix.m_11 + temp.m_22 * _InMatrix.m_21 + temp.m_23 * _InMatrix.m_31;
			m_22 = temp.m_21 * _InMatrix.m_12 + temp.m_22 * _InMatrix.m_22 + temp.m_23 * _InMatrix.m_32;
			m_23 = temp.m_21 * _InMatrix.m_13 + temp.m_22 * _InMatrix.m_23 + temp.m_23 * _InMatrix.m_33;

			m_31 = temp.m_31 * _InMatrix.m_11 + temp.m_32 * _InMatrix.m_21 + temp.m_33 * _InMatrix.m_31;
			m_32 = temp.m_31 * _InMatrix.m_12 + temp.m_32 * _InMatrix.m_22 + temp.m_33 * _InMatrix.m_32;
			m_33 = temp.m_31 * _InMatrix.m_13 + temp.m_32 * _InMatrix.m_23 + temp.m_33 * _InMatrix.m_33;
		}

		FORCE_INLINE void operator /=(float& _InFactor)
		{
			m_11 /= _InFactor, m_12 /= _InFactor, m_13 /= _InFactor;
			m_21 /= _InFactor, m_22 /= _InFactor, m_23 /= _InFactor;
			m_31 /= _InFactor, m_32 /= _InFactor, m_33 /= _InFactor;
		}

		FORCE_INLINE void operator /=(Matrix3x3& _InMatrix)
		{
			_InMatrix.Inverse();

			*this *= _InMatrix;
		}


		float m_11 = 1.f, m_12 = 0.f, m_13 = 0.f;
		float m_21 = 0.f, m_22 = 1.f, m_23 = 0.f;
		float m_31 = 0.f, m_32 = 0.f, m_33 = 1.f;
	};

	namespace Test
	{
		FORCE_INLINE void TestMatrix3x3()
		{
			Matrix3x3 m(1, 5, 5,
						6, 3, 7,
						5, 8, 45);
			Matrix3x3 n(2, 0, 7,
						5, 0, 5,
						3, 7, 9);
			Vector3f v(10, 5, 20);
			Vector3f w;
			Matrix3x3 o;
			float det = 0.f;

			n.Transpose();
			m.Transpose();
			det = n.Determinant();
			m.Inverse();

			o = m * n;
			w = m * v;
		}
	}
}

#endif //__MATRIX3X3_HPP_