#include "Matrix4x4.hpp"

#include "../Constants.hpp"
#include "../MathFunctions.hpp"
#include "../Vector/Vector3f.hpp"
#include "../Vector/Vector4f.hpp"

namespace DadEngine::Math
{
    Matrix4x4::Matrix4x4(Vector4f _InVectors[4U])
    {
        m_11 = _InVectors[0U].x, m_12 = _InVectors[1U].x, m_13 = _InVectors[2U].x,
        m_14 = _InVectors[3U].x;
        m_21 = _InVectors[0U].y, m_22 = _InVectors[1U].y, m_23 = _InVectors[2U].y,
        m_24 = _InVectors[3U].y;
        m_31 = _InVectors[0U].z, m_32 = _InVectors[1U].z, m_33 = _InVectors[2U].z,
        m_34 = _InVectors[3U].z;
        m_41 = _InVectors[0U].w, m_42 = _InVectors[1U].w, m_43 = _InVectors[2U].w,
        m_44 = _InVectors[3U].w;
    }

    Matrix4x4::Matrix4x4(float _In11,
                         float _In12,
                         float _In13,
                         float _In14,
                         float _In21,
                         float _In22,
                         float _In23,
                         float _In24,
                         float _In31,
                         float _In32,
                         float _In33,
                         float _In34,
                         float _In41,
                         float _In42,
                         float _In43,
                         float _In44)
    {
        m_11 = _In11, m_12 = _In12, m_13 = _In13, m_14 = _In14;
        m_21 = _In21, m_22 = _In22, m_23 = _In23, m_24 = _In24;
        m_31 = _In31, m_32 = _In32, m_33 = _In33, m_34 = _In34;
        m_41 = _In41, m_42 = _In42, m_43 = _In43, m_44 = _In44;
    }

    Matrix4x4::Matrix4x4(float _InData[16U])
    {
        m_11 = _InData[0U], m_12 = _InData[1U], m_13 = _InData[2U], m_14 = _InData[3U];
        m_21 = _InData[4U], m_22 = _InData[5U], m_23 = _InData[6U], m_24 = _InData[7U];
        m_31 = _InData[8U], m_32 = _InData[9U], m_33 = _InData[10U], m_34 = _InData[11U];
        m_41 = _InData[12U], m_42 = _InData[13U], m_43 = _InData[14U], m_44 = _InData[15U];
    }


    // Standard matrix functions
    void Matrix4x4::SetIdentity()
    {
        m_11 = 1.f, m_12 = 0.f, m_13 = 0.f, m_14 = 0.f;
        m_21 = 0.f, m_22 = 1.f, m_23 = 0.f, m_24 = 0.f;
        m_31 = 0.f, m_32 = 0.f, m_33 = 1.f, m_34 = 0.f;
        m_41 = 0.f, m_42 = 0.f, m_43 = 0.f, m_44 = 1.f;
    }

    void Matrix4x4::Transpose()
    {
        Matrix4x4 temp = *this;

        m_12 = m_21;
        m_13 = m_31;
        m_14 = m_41;
        m_23 = m_32;
        m_24 = m_42;
        m_34 = m_43;

        m_21 = temp.m_12;
        m_31 = temp.m_13;
        m_32 = temp.m_23;
        m_41 = temp.m_14;
        m_42 = temp.m_24;
        m_43 = temp.m_34;
    }

    void Matrix4x4::Inverse()
    {
        // Same determinants precalculated
        float det111 = m_33 * m_44 - m_34 * m_43;
        float det112 = m_23 * m_44 - m_24 * m_43;
        float det113 = m_13 * m_44 - m_14 * m_43;
        float det114 = m_23 * m_34 - m_24 * m_33;
        float det115 = m_13 * m_34 - m_14 * m_33;
        float det116 = m_13 * m_24 - m_14 * m_23;

        float det11 = (m_22 * det111) - (m_32 * det112) + (m_42 * det114);
        float det21 = -((m_12 * det111) - (m_32 * det113) + (m_42 * det115));
        float det31 = (m_12 * det112) - (m_22 * det113) + (m_42 * det116);
        float det41 = -((m_12 * det114) - (m_22 * det115) + (m_32 * det116));

        float determinant = m_11 * det11 + m_21 * det21 + m_31 * det31 + m_41 * det41;

        if (determinant > FLOAT_EPSILON || determinant < FLOAT_EPSILON)
        {
            // float m_11 = 1.f, m_12 = 0.f, m_13 = 0.f, m_14 = 0.f;
            // float m_21 = 0.f, m_22 = 1.f, m_23 = 0.f, m_24 = 0.f;
            // float m_31 = 0.f, m_32 = 0.f, m_33 = 1.f, m_34 = 0.f;
            // float m_41 = 0.f, m_42 = 0.f, m_43 = 0.f, m_44 = 1.f;

            determinant = 1.f / determinant;
            float det12 = -((m_21 * det111) - (m_31 * det112) + (m_41 * det114));
            float det22 = (m_11 * det111) - (m_31 * det113) + (m_41 * det115);
            float det32 = -((m_11 * det112) - (m_21 * det113) + (m_41 * det116));
            float det42 = +(m_11 * det114) - (m_21 * det115) + (m_31 * det116);

            // Same cofactors precalculated
            float det221 = m_31 * m_42 - m_32 * m_41;
            float det222 = m_21 * m_42 - m_22 * m_41;
            float det223 = m_11 * m_42 - m_12 * m_41;
            float det224 = m_21 * m_32 - m_22 * m_31;
            float det225 = m_11 * m_32 - m_12 * m_31;
            float det226 = m_11 * m_22 - m_12 * m_21;

            float det13 = (m_24 * det221) - (m_34 * det222) + (m_44 * det224);
            float det23 = -((m_14 * det221) - (m_34 * det223) + (m_44 * det225));
            float det33 = (m_14 * det222) - (m_24 * det223) + (m_44 * det226);
            float det43 = -((m_14 * det224) - (m_24 * det225) + (m_34 * det226));

            float det14 = -((m_23 * det221) - (m_33 * det222) + (m_43 * det224));
            float det24 = (m_13 * det221) - (m_33 * det223) + (m_43 * det225);
            float det34 = -((m_13 * det222) - (m_23 * det223) + (m_43 * det226));
            float det44 = (m_13 * det224) - (m_23 * det225) + (m_33 * det226);

            m_11 = determinant * det11, m_12 = determinant * det12, m_13 = determinant * det13,
            m_14 = determinant * det14;
            m_21 = determinant * det21, m_22 = determinant * det22, m_23 = determinant * det23,
            m_24 = determinant * det24;
            m_31 = determinant * det31, m_32 = determinant * det32, m_33 = determinant * det33,
            m_34 = determinant * det34;
            m_41 = determinant * det41, m_42 = determinant * det42, m_43 = determinant * det43,
            m_44 = determinant * det44;


            Transpose();
        }
    }

    float Matrix4x4::Determinant()
    {
        // Same determinants precalculated
        float det111 = m_33 * m_44 - m_34 * m_43;
        float det112 = m_23 * m_44 - m_24 * m_43;
        float det113 = m_13 * m_44 - m_14 * m_43;
        float det114 = m_23 * m_34 - m_24 * m_33;
        float det115 = m_13 * m_34 - m_14 * m_33;
        float det116 = m_13 * m_24 - m_14 * m_23;

        float det11 = (m_22 * det111) - (m_32 * det112) + (m_42 * det114);
        float det21 = -((m_12 * det111) - (m_32 * det113) + (m_42 * det115));
        float det31 = (m_12 * det112) - (m_22 * det113) + (m_42 * det116);
        float det41 = -((m_12 * det114) - (m_22 * det115) + (m_32 * det116));

        return m_11 * det11 + m_21 * det21 + m_31 * det31 + m_41 * det41;
    }

    void Matrix4x4::Translation(Vector3f _InTranslation)
    {
        m_11 = 0.f, m_12 = 0.f, m_13 = 0.f, m_14 = _InTranslation.x;
        m_21 = 0.f, m_22 = 0.f, m_23 = 0.f, m_24 = _InTranslation.y;
        m_31 = 0.f, m_32 = 0.f, m_33 = 0.f, m_34 = _InTranslation.z;
        m_41 = 0.f, m_42 = 0.f, m_43 = 0.f, m_44 = 1.f;
    }

    void Matrix4x4::Orthographic()
    {
    }

    void Matrix4x4::Perpespective(float _InNear, float _InFar, float _InFov)
    {
        float s = 1 / Tan((_InFov * 0.5f) * ((float)_PI / 180.0f));
        float f = _InFar - _InNear;

        m_11 = s;
        m_22 = s;
        m_33 = -_InFar / f;
        m_34 = -1.f;
        m_43 = -(_InFar * _InNear) / f;
        m_44 = 0.f;
    }

    void Matrix4x4::LookAt(Vector3f &_InEyePosition, Vector3f &_InTargetPosition, Vector3f &_InUp)
    {
        Vector3f z = (_InEyePosition - _InTargetPosition);
        z.Normalize();
        Vector3f x = (_InUp ^ z);
        x.Normalize();
        Vector3f y = (z ^ x);

        m_11 = x.x;
        m_12 = y.x;
        m_13 = z.x;
        m_14 = 0.f;
        m_21 = x.y;
        m_22 = y.y;
        m_23 = z.y;
        m_24 = 0.f;
        m_31 = x.z;
        m_32 = y.z;
        m_33 = z.z;
        m_34 = 0.f;
        m_41 = -x.Dot(_InEyePosition);
        m_42 = -y.Dot(_InEyePosition);
        m_43 = -z.Dot(_InEyePosition);
        m_44 = 1.f;
    }


    // Binary math operators
    Matrix4x4 Matrix4x4::operator+(Matrix4x4 &_InMatrix)
    {
        Matrix4x4 result;

        result.m_11 = m_11 + _InMatrix.m_11, result.m_12 = m_12 + _InMatrix.m_12,
        result.m_13 = m_13 + _InMatrix.m_13, result.m_14 = m_14 + _InMatrix.m_14;
        result.m_21 = m_21 + _InMatrix.m_21, result.m_22 = m_22 + _InMatrix.m_22,
        result.m_23 = m_23 + _InMatrix.m_23, result.m_24 = m_24 + _InMatrix.m_24;
        result.m_31 = m_31 + _InMatrix.m_31, result.m_32 = m_32 + _InMatrix.m_32,
        result.m_33 = m_33 + _InMatrix.m_33, result.m_34 = m_34 + _InMatrix.m_34;
        result.m_41 = m_41 + _InMatrix.m_41, result.m_42 = m_42 + _InMatrix.m_42,
        result.m_43 = m_43 + _InMatrix.m_43, result.m_44 = m_44 + _InMatrix.m_44;

        return result;
    }

    Matrix4x4 Matrix4x4::operator-(Matrix4x4 &_InMatrix)
    {
        Matrix4x4 result;

        result.m_11 = m_11 - _InMatrix.m_11, result.m_12 = m_12 - _InMatrix.m_12,
        result.m_13 = m_13 - _InMatrix.m_13, result.m_14 = m_14 - _InMatrix.m_14;
        result.m_21 = m_21 - _InMatrix.m_21, result.m_22 = m_22 - _InMatrix.m_22,
        result.m_23 = m_23 - _InMatrix.m_23, result.m_24 = m_24 - _InMatrix.m_24;
        result.m_31 = m_31 - _InMatrix.m_31, result.m_32 = m_32 - _InMatrix.m_32,
        result.m_33 = m_33 - _InMatrix.m_33, result.m_34 = m_34 - _InMatrix.m_34;
        result.m_41 = m_41 - _InMatrix.m_41, result.m_42 = m_42 - _InMatrix.m_42,
        result.m_43 = m_43 - _InMatrix.m_43, result.m_44 = m_44 - _InMatrix.m_44;

        return result;
    }

    Matrix4x4 Matrix4x4::operator*(float &_InFactor)
    {
        Matrix4x4 result;

        result.m_11 = m_11 * _InFactor, result.m_12 = m_12 * _InFactor,
        result.m_13 = m_13 * _InFactor, result.m_14 = m_14 * _InFactor;
        result.m_21 = m_21 * _InFactor, result.m_22 = m_22 * _InFactor,
        result.m_23 = m_23 * _InFactor, result.m_24 = m_24 * _InFactor;
        result.m_31 = m_31 * _InFactor, result.m_32 = m_32 * _InFactor,
        result.m_33 = m_33 * _InFactor, result.m_34 = m_34 * _InFactor;
        result.m_41 = m_41 * _InFactor, result.m_42 = m_42 * _InFactor,
        result.m_43 = m_43 * _InFactor, result.m_44 = m_44 * _InFactor;

        return result;
    }

    Vector4f Matrix4x4::operator*(Vector4f &_InVector)
    {
        return Vector4f(
            m_11 * _InVector.x + m_12 * _InVector.y + m_13 * _InVector.z + m_14 * _InVector.w,
            m_21 * _InVector.x + m_22 * _InVector.y + m_23 * _InVector.z + m_24 * _InVector.w,
            m_31 * _InVector.x + m_32 * _InVector.y + m_33 * _InVector.z + m_34 * _InVector.w,
            m_41 * _InVector.x + m_42 * _InVector.y + m_43 * _InVector.z + m_44 * _InVector.w);
    }

    Matrix4x4 Matrix4x4::operator*(Matrix4x4 &_InMatrix)
    {
        Matrix4x4 result;

        result.m_11 = m_11 * _InMatrix.m_11 + m_12 * _InMatrix.m_21 + m_13 * _InMatrix.m_31 +
                      m_14 * _InMatrix.m_41;
        result.m_12 = m_11 * _InMatrix.m_12 + m_12 * _InMatrix.m_22 + m_13 * _InMatrix.m_32 +
                      m_14 * _InMatrix.m_42;
        result.m_13 = m_11 * _InMatrix.m_13 + m_12 * _InMatrix.m_23 + m_13 * _InMatrix.m_33 +
                      m_14 * _InMatrix.m_43;
        result.m_14 = m_11 * _InMatrix.m_14 + m_12 * _InMatrix.m_24 + m_13 * _InMatrix.m_34 +
                      m_14 * _InMatrix.m_44;

        result.m_21 = m_21 * _InMatrix.m_11 + m_22 * _InMatrix.m_21 + m_23 * _InMatrix.m_31 +
                      m_24 * _InMatrix.m_41;
        result.m_22 = m_21 * _InMatrix.m_12 + m_22 * _InMatrix.m_22 + m_23 * _InMatrix.m_32 +
                      m_24 * _InMatrix.m_42;
        result.m_23 = m_21 * _InMatrix.m_13 + m_22 * _InMatrix.m_23 + m_23 * _InMatrix.m_33 +
                      m_24 * _InMatrix.m_43;
        result.m_24 = m_21 * _InMatrix.m_14 + m_22 * _InMatrix.m_24 + m_23 * _InMatrix.m_34 +
                      m_24 * _InMatrix.m_44;

        result.m_31 = m_31 * _InMatrix.m_11 + m_32 * _InMatrix.m_21 + m_33 * _InMatrix.m_31 +
                      m_34 * _InMatrix.m_41;
        result.m_32 = m_31 * _InMatrix.m_12 + m_32 * _InMatrix.m_22 + m_33 * _InMatrix.m_32 +
                      m_34 * _InMatrix.m_42;
        result.m_33 = m_31 * _InMatrix.m_13 + m_32 * _InMatrix.m_23 + m_33 * _InMatrix.m_33 +
                      m_34 * _InMatrix.m_43;
        result.m_34 = m_31 * _InMatrix.m_14 + m_32 * _InMatrix.m_24 + m_33 * _InMatrix.m_34 +
                      m_34 * _InMatrix.m_44;

        result.m_41 = m_41 * _InMatrix.m_11 + m_42 * _InMatrix.m_21 + m_43 * _InMatrix.m_31 +
                      m_44 * _InMatrix.m_41;
        result.m_42 = m_41 * _InMatrix.m_12 + m_42 * _InMatrix.m_22 + m_43 * _InMatrix.m_32 +
                      m_44 * _InMatrix.m_42;
        result.m_43 = m_41 * _InMatrix.m_13 + m_42 * _InMatrix.m_23 + m_43 * _InMatrix.m_33 +
                      m_44 * _InMatrix.m_43;
        result.m_44 = m_41 * _InMatrix.m_14 + m_42 * _InMatrix.m_24 + m_43 * _InMatrix.m_34 +
                      m_44 * _InMatrix.m_44;

        return result;
    }

    Matrix4x4 Matrix4x4::operator/(float &_InFactor)
    {
        Matrix4x4 result;

        result.m_11 = m_11 / _InFactor, result.m_12 = m_12 / _InFactor,
        result.m_13 = m_13 / _InFactor, result.m_14 = m_14 / _InFactor;
        result.m_21 = m_21 / _InFactor, result.m_22 = m_22 / _InFactor,
        result.m_23 = m_23 / _InFactor, result.m_24 = m_24 / _InFactor;
        result.m_31 = m_31 / _InFactor, result.m_32 = m_32 / _InFactor,
        result.m_33 = m_33 / _InFactor, result.m_34 = m_34 / _InFactor;
        result.m_41 = m_41 / _InFactor, result.m_42 = m_42 / _InFactor,
        result.m_43 = m_43 / _InFactor, result.m_44 = m_44 / _InFactor;

        return result;
    }

    Matrix4x4 Matrix4x4::operator/(Matrix4x4 &_InMatrix)
    {
        Matrix4x4 result;

        _InMatrix.Inverse();

        result = *this * _InMatrix;

        return result;
    }


    // Binary assignement math operators
    void Matrix4x4::operator+=(Matrix4x4 &_InMatrix)
    {
        m_11 += _InMatrix.m_11, m_12 += _InMatrix.m_12, m_13 += _InMatrix.m_13, m_14 += _InMatrix.m_14;
        m_21 += _InMatrix.m_21, m_22 += _InMatrix.m_22, m_23 += _InMatrix.m_23, m_24 += _InMatrix.m_24;
        m_31 += _InMatrix.m_31, m_32 += _InMatrix.m_32, m_33 += _InMatrix.m_33, m_34 += _InMatrix.m_34;
        m_41 += _InMatrix.m_41, m_42 += _InMatrix.m_42, m_43 += _InMatrix.m_43, m_44 += _InMatrix.m_44;
    }

    void Matrix4x4::operator-=(Matrix4x4 &_InMatrix)
    {
        m_11 -= _InMatrix.m_11, m_12 -= _InMatrix.m_12, m_13 -= _InMatrix.m_13, m_14 -= _InMatrix.m_14;
        m_21 -= _InMatrix.m_21, m_22 -= _InMatrix.m_22, m_23 -= _InMatrix.m_23, m_24 -= _InMatrix.m_24;
        m_31 -= _InMatrix.m_31, m_32 -= _InMatrix.m_32, m_33 -= _InMatrix.m_33, m_34 -= _InMatrix.m_34;
        m_41 -= _InMatrix.m_41, m_42 -= _InMatrix.m_42, m_43 -= _InMatrix.m_43, m_44 -= _InMatrix.m_44;
    }

    void Matrix4x4::operator*=(float &_InFactor)
    {
        m_11 *= _InFactor, m_12 *= _InFactor, m_13 *= _InFactor, m_14 *= _InFactor;
        m_21 *= _InFactor, m_22 *= _InFactor, m_23 *= _InFactor, m_24 *= _InFactor;
        m_31 *= _InFactor, m_32 *= _InFactor, m_33 *= _InFactor, m_34 *= _InFactor;
        m_41 *= _InFactor, m_42 *= _InFactor, m_43 *= _InFactor, m_44 *= _InFactor;
    }

    Vector4f Matrix4x4::operator*=(Vector4f &_InVector)
    {
        return Vector4f(
            m_11 * _InVector.x + m_12 * _InVector.y + m_13 * _InVector.z + m_14 * _InVector.w,
            m_21 * _InVector.x + m_22 * _InVector.y + m_23 * _InVector.z + m_24 * _InVector.w,
            m_31 * _InVector.x + m_32 * _InVector.y + m_33 * _InVector.z + m_34 * _InVector.w,
            m_41 * _InVector.x + m_42 * _InVector.y + m_43 * _InVector.z + m_44 * _InVector.w);
    }

    void Matrix4x4::operator*=(Matrix4x4 &_InMatrix)
    {
        Matrix4x4 temp = *this;

        m_11 = temp.m_11 * _InMatrix.m_11 + temp.m_12 * _InMatrix.m_21 +
               temp.m_13 * _InMatrix.m_31 + temp.m_14 * _InMatrix.m_41;
        m_12 = temp.m_11 * _InMatrix.m_12 + temp.m_12 * _InMatrix.m_22 +
               temp.m_13 * _InMatrix.m_32 + temp.m_14 * _InMatrix.m_42;
        m_13 = temp.m_11 * _InMatrix.m_13 + temp.m_12 * _InMatrix.m_23 +
               temp.m_13 * _InMatrix.m_33 + temp.m_14 * _InMatrix.m_43;
        m_14 = temp.m_11 * _InMatrix.m_14 + temp.m_12 * _InMatrix.m_24 +
               temp.m_13 * _InMatrix.m_34 + temp.m_14 * _InMatrix.m_44;

        m_21 = temp.m_21 * _InMatrix.m_11 + temp.m_22 * _InMatrix.m_21 +
               temp.m_23 * _InMatrix.m_31 + temp.m_24 * _InMatrix.m_41;
        m_22 = temp.m_21 * _InMatrix.m_12 + temp.m_22 * _InMatrix.m_22 +
               temp.m_23 * _InMatrix.m_32 + temp.m_24 * _InMatrix.m_42;
        m_23 = temp.m_21 * _InMatrix.m_13 + temp.m_22 * _InMatrix.m_23 +
               temp.m_23 * _InMatrix.m_33 + temp.m_24 * _InMatrix.m_43;
        m_24 = temp.m_21 * _InMatrix.m_14 + temp.m_22 * _InMatrix.m_24 +
               temp.m_23 * _InMatrix.m_34 + temp.m_24 * _InMatrix.m_44;

        m_31 = temp.m_31 * _InMatrix.m_11 + temp.m_32 * _InMatrix.m_21 +
               temp.m_33 * _InMatrix.m_31 + temp.m_34 * _InMatrix.m_41;
        m_32 = temp.m_31 * _InMatrix.m_12 + temp.m_32 * _InMatrix.m_22 +
               temp.m_33 * _InMatrix.m_32 + temp.m_34 * _InMatrix.m_42;
        m_33 = temp.m_31 * _InMatrix.m_13 + temp.m_32 * _InMatrix.m_23 +
               temp.m_33 * _InMatrix.m_33 + temp.m_34 * _InMatrix.m_43;
        m_34 = temp.m_31 * _InMatrix.m_14 + temp.m_32 * _InMatrix.m_24 +
               temp.m_33 * _InMatrix.m_34 + temp.m_34 * _InMatrix.m_44;

        m_41 = temp.m_41 * _InMatrix.m_11 + temp.m_42 * _InMatrix.m_21 +
               temp.m_43 * _InMatrix.m_31 + temp.m_44 * _InMatrix.m_41;
        m_42 = temp.m_41 * _InMatrix.m_12 + temp.m_42 * _InMatrix.m_22 +
               temp.m_43 * _InMatrix.m_32 + temp.m_44 * _InMatrix.m_42;
        m_43 = temp.m_41 * _InMatrix.m_13 + temp.m_42 * _InMatrix.m_23 +
               temp.m_43 * _InMatrix.m_33 + temp.m_44 * _InMatrix.m_43;
        m_44 = temp.m_41 * _InMatrix.m_14 + temp.m_42 * _InMatrix.m_24 +
               temp.m_43 * _InMatrix.m_34 + temp.m_44 * _InMatrix.m_44;
    }

    void Matrix4x4::operator/=(float &_InFactor)
    {
        m_11 /= _InFactor, m_12 /= _InFactor, m_13 /= _InFactor, m_14 /= _InFactor;
        m_21 /= _InFactor, m_22 /= _InFactor, m_23 /= _InFactor, m_24 /= _InFactor;
        m_31 /= _InFactor, m_32 /= _InFactor, m_33 /= _InFactor, m_34 /= _InFactor;
        m_41 /= _InFactor, m_42 /= _InFactor, m_43 /= _InFactor, m_44 /= _InFactor;
    }

    void Matrix4x4::operator/=(Matrix4x4 &_InMatrix)
    {
        _InMatrix.Inverse();

        *this *= _InMatrix;
    }

    namespace Test
    {
        void TestMatrix4x4()
        {
            Matrix4x4 m(1, 5, 5, 8, 6, 3, 7, 9, 5, 8, 5, 4, 8, 9, 7, 2);
            Matrix4x4 n(2, 0, 7, 5, 5, 0, 5, 1, 3, 7, 9, 4, 6, 7, 2, 9);
            Vector4f v(10, 5, 20, 2);
            Vector4f w;
            Matrix4x4 o;
            float det = 0.f;

            // n.Transpose();
            // m.Transpose();
            det = n.Determinant();
            m.Inverse();

            o = m * n;
            w = m * v;
        }
    } // namespace Test
} // namespace DadEngine::Math