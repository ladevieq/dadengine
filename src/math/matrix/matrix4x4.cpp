#include "matrix/matrix4x4.hpp"

#include "constants.hpp"
#include "vector/vector3.hpp"
#include "vector/vector4.hpp"

#include <limits>

namespace DadEngine
{
    // Matrix4x4::Matrix4x4(std::array<Vector4, 4> _vectors)
    // {
    //     m_11 = _vectors[0U].x, m_12 = _vectors[1U].x, m_13 = _vectors[2U].x,
    //     m_14 = _vectors[3U].x;
    //     m_21 = _vectors[0U].y, m_22 = _vectors[1U].y, m_23 = _vectors[2U].y,
    //     m_24 = _vectors[3U].y;
    //     m_31 = _vectors[0U].z, m_32 = _vectors[1U].z, m_33 = _vectors[2U].z,
    //     m_34 = _vectors[3U].z;
    //     m_41 = _vectors[0U].w, m_42 = _vectors[1U].w, m_43 = _vectors[2U].w,
    //     m_44 = _vectors[3U].w;
    // }

    Matrix4x4::Matrix4x4(float _11,
                         float _12,
                         float _13,
                         float _14,
                         float _21,
                         float _22,
                         float _23,
                         float _24,
                         float _31,
                         float _32,
                         float _33,
                         float _34,
                         float _41,
                         float _42,
                         float _43,
                         float _44)
    {
        m_11 = _11, m_12 = _12, m_13 = _13, m_14 = _14;
        m_21 = _21, m_22 = _22, m_23 = _23, m_24 = _24;
        m_31 = _31, m_32 = _32, m_33 = _33, m_34 = _34;
        m_41 = _41, m_42 = _42, m_43 = _43, m_44 = _44;
    }

    Matrix4x4::Matrix4x4(std::array<float, 16> _data)
    {
        m_11 = _data[0U], m_12 = _data[1U], m_13 = _data[2U], m_14 = _data[3U];
        m_21 = _data[4U], m_22 = _data[5U], m_23 = _data[6U], m_24 = _data[7U];
        m_31 = _data[8U], m_32 = _data[9U], m_33 = _data[10U], m_34 = _data[11U];
        m_41 = _data[12U], m_42 = _data[13U], m_43 = _data[14U], m_44 = _data[15U];
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

        if (determinant > std::numeric_limits<decltype(determinant)>::epsilon()
            || determinant < std::numeric_limits<decltype(determinant)>::epsilon()) {
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

            m_11 = determinant * det11, m_12 = determinant * det12,
            m_13 = determinant * det13, m_14 = determinant * det14;
            m_21 = determinant * det21, m_22 = determinant * det22,
            m_23 = determinant * det23, m_24 = determinant * det24;
            m_31 = determinant * det31, m_32 = determinant * det32,
            m_33 = determinant * det33, m_34 = determinant * det34;
            m_41 = determinant * det41, m_42 = determinant * det42,
            m_43 = determinant * det43, m_44 = determinant * det44;


            Transpose();
        }
    }

    float Matrix4x4::Determinant() const
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

    void Matrix4x4::Translation(Vector3 _translation)
    {
        m_11 = 0.f, m_12 = 0.f, m_13 = 0.f, m_14 = _translation.x;
        m_21 = 0.f, m_22 = 0.f, m_23 = 0.f, m_24 = _translation.y;
        m_31 = 0.f, m_32 = 0.f, m_33 = 0.f, m_34 = _translation.z;
        m_41 = 0.f, m_42 = 0.f, m_43 = 0.f, m_44 = 1.f;
    }

    void Matrix4x4::Orthographic()
    {}

    void Matrix4x4::PerspectiveRHNO(float _near, float _far, float _fov, float _aspect)
    {
        float radFov = static_cast<float>(DegToRad(static_cast<double>(_fov))) / 2.f;
        float halfTan = std::tan(radFov);
        float f       = _far - _near;

        m_11 = 1.f / (_aspect * halfTan);
        m_22 = 1.f / halfTan;
        m_33 = -(_far + _near) / f;
        m_34 = -1.f;
        m_43 = -(2.f * _far * _near) / f;
        m_44 = 0.f;
    }

    void Matrix4x4::LookAtRH(Vector3 &_eyePosition, Vector3 &_targetPosition, Vector3 &_up)
    {
        Vector3 z = (_targetPosition - _eyePosition);
        z.Normalize();
        Vector3 x = (_up ^ z);
        x.Normalize();
        Vector3 y = (z ^ x);

        m_11 = x.x;
        m_12 = y.x;
        m_13 = -z.x;
        m_14 = 0.f;
        m_21 = x.y;
        m_22 = y.y;
        m_23 = -z.y;
        m_24 = 0.f;
        m_31 = x.z;
        m_32 = y.z;
        m_33 = -z.z;
        m_34 = 0.f;
        m_41 = -x.Dot(_eyePosition);
        m_42 = -y.Dot(_eyePosition);
        m_43 = z.Dot(_eyePosition);
        m_44 = 1.f;
    }


    // Binary math operators
    Matrix4x4 Matrix4x4::operator+(Matrix4x4 &_matrix) const
    {
        Matrix4x4 result;

        result.m_11 = m_11 + _matrix.m_11, result.m_12 = m_12 + _matrix.m_12,
        result.m_13 = m_13 + _matrix.m_13, result.m_14 = m_14 + _matrix.m_14;
        result.m_21 = m_21 + _matrix.m_21, result.m_22 = m_22 + _matrix.m_22,
        result.m_23 = m_23 + _matrix.m_23, result.m_24 = m_24 + _matrix.m_24;
        result.m_31 = m_31 + _matrix.m_31, result.m_32 = m_32 + _matrix.m_32,
        result.m_33 = m_33 + _matrix.m_33, result.m_34 = m_34 + _matrix.m_34;
        result.m_41 = m_41 + _matrix.m_41, result.m_42 = m_42 + _matrix.m_42,
        result.m_43 = m_43 + _matrix.m_43, result.m_44 = m_44 + _matrix.m_44;

        return result;
    }

    Matrix4x4 Matrix4x4::operator-(Matrix4x4 &_matrix) const
    {
        Matrix4x4 result;

        result.m_11 = m_11 - _matrix.m_11, result.m_12 = m_12 - _matrix.m_12,
        result.m_13 = m_13 - _matrix.m_13, result.m_14 = m_14 - _matrix.m_14;
        result.m_21 = m_21 - _matrix.m_21, result.m_22 = m_22 - _matrix.m_22,
        result.m_23 = m_23 - _matrix.m_23, result.m_24 = m_24 - _matrix.m_24;
        result.m_31 = m_31 - _matrix.m_31, result.m_32 = m_32 - _matrix.m_32,
        result.m_33 = m_33 - _matrix.m_33, result.m_34 = m_34 - _matrix.m_34;
        result.m_41 = m_41 - _matrix.m_41, result.m_42 = m_42 - _matrix.m_42,
        result.m_43 = m_43 - _matrix.m_43, result.m_44 = m_44 - _matrix.m_44;

        return result;
    }

    Matrix4x4 Matrix4x4::operator*(float &_factor) const
    {
        Matrix4x4 result;

        result.m_11 = m_11 * _factor, result.m_12 = m_12 * _factor,
        result.m_13 = m_13 * _factor, result.m_14 = m_14 * _factor;
        result.m_21 = m_21 * _factor, result.m_22 = m_22 * _factor,
        result.m_23 = m_23 * _factor, result.m_24 = m_24 * _factor;
        result.m_31 = m_31 * _factor, result.m_32 = m_32 * _factor,
        result.m_33 = m_33 * _factor, result.m_34 = m_34 * _factor;
        result.m_41 = m_41 * _factor, result.m_42 = m_42 * _factor,
        result.m_43 = m_43 * _factor, result.m_44 = m_44 * _factor;

        return result;
    }

    Vector4 Matrix4x4::operator*(Vector4 &_vector) const
    {
        return Vector4(m_11 * _vector.x + m_12 * _vector.y + m_13 * _vector.z
                           + m_14 * _vector.w,
                       m_21 * _vector.x + m_22 * _vector.y + m_23 * _vector.z
                           + m_24 * _vector.w,
                       m_31 * _vector.x + m_32 * _vector.y + m_33 * _vector.z
                           + m_34 * _vector.w,
                       m_41 * _vector.x + m_42 * _vector.y + m_43 * _vector.z
                           + m_44 * _vector.w);
    }

    Matrix4x4 Matrix4x4::operator*(Matrix4x4 &_matrix) const
    {
        Matrix4x4 result;

        result.m_11 = m_11 * _matrix.m_11 + m_12 * _matrix.m_21
                      + m_13 * _matrix.m_31 + m_14 * _matrix.m_41;
        result.m_12 = m_11 * _matrix.m_12 + m_12 * _matrix.m_22
                      + m_13 * _matrix.m_32 + m_14 * _matrix.m_42;
        result.m_13 = m_11 * _matrix.m_13 + m_12 * _matrix.m_23
                      + m_13 * _matrix.m_33 + m_14 * _matrix.m_43;
        result.m_14 = m_11 * _matrix.m_14 + m_12 * _matrix.m_24
                      + m_13 * _matrix.m_34 + m_14 * _matrix.m_44;

        result.m_21 = m_21 * _matrix.m_11 + m_22 * _matrix.m_21
                      + m_23 * _matrix.m_31 + m_24 * _matrix.m_41;
        result.m_22 = m_21 * _matrix.m_12 + m_22 * _matrix.m_22
                      + m_23 * _matrix.m_32 + m_24 * _matrix.m_42;
        result.m_23 = m_21 * _matrix.m_13 + m_22 * _matrix.m_23
                      + m_23 * _matrix.m_33 + m_24 * _matrix.m_43;
        result.m_24 = m_21 * _matrix.m_14 + m_22 * _matrix.m_24
                      + m_23 * _matrix.m_34 + m_24 * _matrix.m_44;

        result.m_31 = m_31 * _matrix.m_11 + m_32 * _matrix.m_21
                      + m_33 * _matrix.m_31 + m_34 * _matrix.m_41;
        result.m_32 = m_31 * _matrix.m_12 + m_32 * _matrix.m_22
                      + m_33 * _matrix.m_32 + m_34 * _matrix.m_42;
        result.m_33 = m_31 * _matrix.m_13 + m_32 * _matrix.m_23
                      + m_33 * _matrix.m_33 + m_34 * _matrix.m_43;
        result.m_34 = m_31 * _matrix.m_14 + m_32 * _matrix.m_24
                      + m_33 * _matrix.m_34 + m_34 * _matrix.m_44;

        result.m_41 = m_41 * _matrix.m_11 + m_42 * _matrix.m_21
                      + m_43 * _matrix.m_31 + m_44 * _matrix.m_41;
        result.m_42 = m_41 * _matrix.m_12 + m_42 * _matrix.m_22
                      + m_43 * _matrix.m_32 + m_44 * _matrix.m_42;
        result.m_43 = m_41 * _matrix.m_13 + m_42 * _matrix.m_23
                      + m_43 * _matrix.m_33 + m_44 * _matrix.m_43;
        result.m_44 = m_41 * _matrix.m_14 + m_42 * _matrix.m_24
                      + m_43 * _matrix.m_34 + m_44 * _matrix.m_44;

        return result;
    }

    Matrix4x4 Matrix4x4::operator/(float &_factor) const
    {
        Matrix4x4 result;

        result.m_11 = m_11 / _factor, result.m_12 = m_12 / _factor,
        result.m_13 = m_13 / _factor, result.m_14 = m_14 / _factor;
        result.m_21 = m_21 / _factor, result.m_22 = m_22 / _factor,
        result.m_23 = m_23 / _factor, result.m_24 = m_24 / _factor;
        result.m_31 = m_31 / _factor, result.m_32 = m_32 / _factor,
        result.m_33 = m_33 / _factor, result.m_34 = m_34 / _factor;
        result.m_41 = m_41 / _factor, result.m_42 = m_42 / _factor,
        result.m_43 = m_43 / _factor, result.m_44 = m_44 / _factor;

        return result;
    }

    Matrix4x4 Matrix4x4::operator/(Matrix4x4 &_matrix) const
    {
        Matrix4x4 result;

        _matrix.Inverse();

        result = *this * _matrix;

        return result;
    }


    // Binary assignement math operators
    void Matrix4x4::operator+=(Matrix4x4 &_matrix)
    {
        m_11 += _matrix.m_11, m_12 += _matrix.m_12, m_13 += _matrix.m_13,
            m_14 += _matrix.m_14;
        m_21 += _matrix.m_21, m_22 += _matrix.m_22, m_23 += _matrix.m_23,
            m_24 += _matrix.m_24;
        m_31 += _matrix.m_31, m_32 += _matrix.m_32, m_33 += _matrix.m_33,
            m_34 += _matrix.m_34;
        m_41 += _matrix.m_41, m_42 += _matrix.m_42, m_43 += _matrix.m_43,
            m_44 += _matrix.m_44;
    }

    void Matrix4x4::operator-=(Matrix4x4 &_matrix)
    {
        m_11 -= _matrix.m_11, m_12 -= _matrix.m_12, m_13 -= _matrix.m_13,
            m_14 -= _matrix.m_14;
        m_21 -= _matrix.m_21, m_22 -= _matrix.m_22, m_23 -= _matrix.m_23,
            m_24 -= _matrix.m_24;
        m_31 -= _matrix.m_31, m_32 -= _matrix.m_32, m_33 -= _matrix.m_33,
            m_34 -= _matrix.m_34;
        m_41 -= _matrix.m_41, m_42 -= _matrix.m_42, m_43 -= _matrix.m_43,
            m_44 -= _matrix.m_44;
    }

    void Matrix4x4::operator*=(float &_factor)
    {
        m_11 *= _factor, m_12 *= _factor, m_13 *= _factor, m_14 *= _factor;
        m_21 *= _factor, m_22 *= _factor, m_23 *= _factor, m_24 *= _factor;
        m_31 *= _factor, m_32 *= _factor, m_33 *= _factor, m_34 *= _factor;
        m_41 *= _factor, m_42 *= _factor, m_43 *= _factor, m_44 *= _factor;
    }

    Vector4 Matrix4x4::operator*=(Vector4 &_vector) const
    {
        return Vector4(m_11 * _vector.x + m_12 * _vector.y + m_13 * _vector.z
                           + m_14 * _vector.w,
                       m_21 * _vector.x + m_22 * _vector.y + m_23 * _vector.z
                           + m_24 * _vector.w,
                       m_31 * _vector.x + m_32 * _vector.y + m_33 * _vector.z
                           + m_34 * _vector.w,
                       m_41 * _vector.x + m_42 * _vector.y + m_43 * _vector.z
                           + m_44 * _vector.w);
    }

    void Matrix4x4::operator*=(Matrix4x4 &_matrix)
    {
        Matrix4x4 temp = *this;

        m_11 = temp.m_11 * _matrix.m_11 + temp.m_12 * _matrix.m_21
               + temp.m_13 * _matrix.m_31 + temp.m_14 * _matrix.m_41;
        m_12 = temp.m_11 * _matrix.m_12 + temp.m_12 * _matrix.m_22
               + temp.m_13 * _matrix.m_32 + temp.m_14 * _matrix.m_42;
        m_13 = temp.m_11 * _matrix.m_13 + temp.m_12 * _matrix.m_23
               + temp.m_13 * _matrix.m_33 + temp.m_14 * _matrix.m_43;
        m_14 = temp.m_11 * _matrix.m_14 + temp.m_12 * _matrix.m_24
               + temp.m_13 * _matrix.m_34 + temp.m_14 * _matrix.m_44;

        m_21 = temp.m_21 * _matrix.m_11 + temp.m_22 * _matrix.m_21
               + temp.m_23 * _matrix.m_31 + temp.m_24 * _matrix.m_41;
        m_22 = temp.m_21 * _matrix.m_12 + temp.m_22 * _matrix.m_22
               + temp.m_23 * _matrix.m_32 + temp.m_24 * _matrix.m_42;
        m_23 = temp.m_21 * _matrix.m_13 + temp.m_22 * _matrix.m_23
               + temp.m_23 * _matrix.m_33 + temp.m_24 * _matrix.m_43;
        m_24 = temp.m_21 * _matrix.m_14 + temp.m_22 * _matrix.m_24
               + temp.m_23 * _matrix.m_34 + temp.m_24 * _matrix.m_44;

        m_31 = temp.m_31 * _matrix.m_11 + temp.m_32 * _matrix.m_21
               + temp.m_33 * _matrix.m_31 + temp.m_34 * _matrix.m_41;
        m_32 = temp.m_31 * _matrix.m_12 + temp.m_32 * _matrix.m_22
               + temp.m_33 * _matrix.m_32 + temp.m_34 * _matrix.m_42;
        m_33 = temp.m_31 * _matrix.m_13 + temp.m_32 * _matrix.m_23
               + temp.m_33 * _matrix.m_33 + temp.m_34 * _matrix.m_43;
        m_34 = temp.m_31 * _matrix.m_14 + temp.m_32 * _matrix.m_24
               + temp.m_33 * _matrix.m_34 + temp.m_34 * _matrix.m_44;

        m_41 = temp.m_41 * _matrix.m_11 + temp.m_42 * _matrix.m_21
               + temp.m_43 * _matrix.m_31 + temp.m_44 * _matrix.m_41;
        m_42 = temp.m_41 * _matrix.m_12 + temp.m_42 * _matrix.m_22
               + temp.m_43 * _matrix.m_32 + temp.m_44 * _matrix.m_42;
        m_43 = temp.m_41 * _matrix.m_13 + temp.m_42 * _matrix.m_23
               + temp.m_43 * _matrix.m_33 + temp.m_44 * _matrix.m_43;
        m_44 = temp.m_41 * _matrix.m_14 + temp.m_42 * _matrix.m_24
               + temp.m_43 * _matrix.m_34 + temp.m_44 * _matrix.m_44;
    }

    void Matrix4x4::operator/=(float &_factor)
    {
        m_11 /= _factor, m_12 /= _factor, m_13 /= _factor, m_14 /= _factor;
        m_21 /= _factor, m_22 /= _factor, m_23 /= _factor, m_24 /= _factor;
        m_31 /= _factor, m_32 /= _factor, m_33 /= _factor, m_34 /= _factor;
        m_41 /= _factor, m_42 /= _factor, m_43 /= _factor, m_44 /= _factor;
    }

    void Matrix4x4::operator/=(Matrix4x4 &_matrix)
    {
        _matrix.Inverse();

        *this *= _matrix;
    }
} // namespace DadEngine
