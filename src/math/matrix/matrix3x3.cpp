#include "matrix3x3.hpp"

#include "../constants.hpp"
#include "../vector/vector2.hpp"
#include "../vector/vector3.hpp"

#include <limits>

namespace DadEngine
{
    Matrix3x3::Matrix3x3(Vector3 _vectors[3U])
    {
        m_11 = _vectors[0U].x, m_12 = _vectors[1U].x, m_13 = _vectors[2U].x;
        m_21 = _vectors[0U].y, m_22 = _vectors[1U].y, m_23 = _vectors[2U].y;
        m_31 = _vectors[0U].z, m_32 = _vectors[1U].z, m_33 = _vectors[2U].z;
    }

    Matrix3x3::Matrix3x3(float _11, float _12, float _13, float _21, float _22, float _23, float _31, float _32, float _33)
    {
        m_11 = _11, m_12 = _12, m_13 = _13;
        m_21 = _21, m_22 = _22, m_23 = _23;
        m_31 = _31, m_32 = _32, m_33 = _33;
    }

    Matrix3x3::Matrix3x3(float _data[9U])
    {
        m_11 = _data[0U], m_12 = _data[1U], m_13 = _data[2U];
        m_21 = _data[3U], m_22 = _data[4U], m_23 = _data[5U];
        m_31 = _data[6U], m_32 = _data[7U], m_33 = _data[8U];
    }


    // Standard matrix functions
    void Matrix3x3::SetIdentity()
    {
        m_11 = 1.f, m_12 = 0.f, m_13 = 0.f;
        m_21 = 0.f, m_22 = 1.f, m_23 = 0.f;
        m_31 = 0.f, m_32 = 0.f, m_33 = 1.f;
    }

    void Matrix3x3::Transpose()
    {
        Matrix3x3 temp = *this;

        m_12 = m_21;
        m_13 = m_31;
        m_23 = m_32;

        m_21 = temp.m_12;
        m_31 = temp.m_13;
        m_32 = temp.m_23;
    }

    void Matrix3x3::Inverse()
    {
        float cof11 = (m_22 * m_33 - m_23 * m_32),
              cof12 = -(m_21 * m_33 - m_23 * m_31),
              cof13 = (m_21 * m_32 - m_22 * m_31);
        float determinant = m_11 * cof11 + m_12 * cof12 + m_13 * cof13;

        if (determinant > std::numeric_limits<decltype(determinant)>::epsilon() ||
            determinant < std::numeric_limits<decltype(determinant)>::epsilon())
        {
            determinant = 1.f / determinant;
            float cof21 = -(m_12 * m_33 - m_13 * m_32),
                  cof22 = (m_11 * m_33 - m_13 * m_31),
                  cof23 = -(m_11 * m_32 - m_12 * m_31);
            float cof31 = (m_12 * m_23 - m_13 * m_22),
                  cof32 = -(m_11 * m_23 - m_13 * m_21),
                  cof33 = (m_11 * m_22 - m_12 * m_21);

            m_11 = cof11 * determinant, m_12 = cof12 * determinant, m_13 = cof13 * determinant;
            m_21 = cof21 * determinant, m_22 = cof22 * determinant, m_23 = cof23 * determinant;
            m_31 = cof31 * determinant, m_32 = cof32 * determinant, m_33 = cof33 * determinant;

            // Transpose();
        }
    }

    float Matrix3x3::Determinant()
    {
        float cof11 = (m_22 * m_33 - m_23 * m_32),
              cof12 = -(m_21 * m_33 - m_23 * m_31),
              cof13 = (m_21 * m_32 - m_22 * m_31);

        return m_11 * cof11 + m_12 * cof12 + m_13 * cof13;
    }

    void Matrix3x3::RotationX(float _angle)
    {
        float cos = std::cos(_angle);
        float sin = std::sin(_angle);

        m_11 = 1.f, m_12 = 0.f, m_13 = 0.f;
        m_21 = 0.f, m_22 = cos, m_23 = -sin;
        m_31 = 0.f, m_32 = sin, m_33 = cos;
    }

    void Matrix3x3::RotationY(float _angle)
    {
        float cos = std::cos(_angle);
        float sin = std::sin(_angle);

        m_11 = cos, m_12 = 0.f, m_13 = sin;
        m_21 = 0.f, m_22 = 1.f, m_23 = 0.f;
        m_31 = -sin, m_32 = 0.f, m_33 = cos;
    }

    void Matrix3x3::RotationZ(float _angle)
    {
        float cos = std::cos(_angle);
        float sin = std::sin(_angle);

        m_11 = cos, m_12 = -sin, m_13 = 0.f;
        m_21 = sin, m_22 = cos, m_23 = 0.f;
        m_31 = 0.f, m_32 = 0.f, m_33 = 1.f;
    }

    void Matrix3x3::Rotation(float _angle, Vector3 _axis)
    {
        float cos = std::cos(_angle);
        float sin = std::sin(_angle);
        float cosLessOne = 1 - cos;

        m_11 = cos + (cosLessOne * _axis.x * _axis.x),
        m_12 = (cosLessOne * _axis.x * _axis.y) - (sin * _axis.z),
        m_13 = (cosLessOne * _axis.x * _axis.z) + (sin * _axis.y);
        m_21 = (cosLessOne * _axis.x * _axis.y) + (sin * _axis.z),
        m_22 = cos + (cosLessOne * _axis.y * _axis.y),
        m_23 = (cosLessOne * _axis.y * _axis.z) - (sin * _axis.x);
        m_31 = (cosLessOne * _axis.x * _axis.z) - (sin * _axis.y),
        m_32 = (cosLessOne * _axis.y * _axis.z) + (sin * _axis.x),
        m_33 = cos + (cosLessOne * _axis.z * _axis.z);
    }

    void Matrix3x3::Scale(float _scaleX, float _scaleY, float _scaleZ)
    {
        m_11 = _scaleX, m_12 = 0.f, m_13 = 0.f;
        m_21 = 0.f, m_22 = _scaleY, m_23 = 0.f;
        m_31 = 0.f, m_32 = 0.f, m_33 = _scaleZ;
    }

    void Matrix3x3::Translation(Vector2 _translation)
    {
        m_11 = 0.f, m_12 = 0.f, m_13 = _translation.x;
        m_21 = 0.f, m_22 = 0.f, m_23 = _translation.y;
        m_31 = 0.f, m_32 = 0.f, m_33 = 1.f;
    }


    // Binary math operators
    Matrix3x3 Matrix3x3::operator+(Matrix3x3 &_matrix)
    {
        Matrix3x3 result;

        result.m_11 = m_11 + _matrix.m_11, result.m_12 = m_12 + _matrix.m_12,
        result.m_13 = m_13 + _matrix.m_13;
        result.m_21 = m_21 + _matrix.m_21, result.m_22 = m_22 + _matrix.m_22,
        result.m_23 = m_23 + _matrix.m_23;
        result.m_31 = m_31 + _matrix.m_31, result.m_32 = m_32 + _matrix.m_32,
        result.m_33 = m_33 + _matrix.m_33;

        return result;
    }

    Matrix3x3 Matrix3x3::operator-(Matrix3x3 &_matrix)
    {
        Matrix3x3 result;

        result.m_11 = m_11 - _matrix.m_11, result.m_12 = m_12 - _matrix.m_12,
        result.m_13 = m_13 - _matrix.m_13;
        result.m_21 = m_21 - _matrix.m_21, result.m_22 = m_22 - _matrix.m_22,
        result.m_23 = m_23 - _matrix.m_23;
        result.m_31 = m_31 - _matrix.m_31, result.m_32 = m_32 - _matrix.m_32,
        result.m_33 = m_33 - _matrix.m_33;

        return result;
    }

    Matrix3x3 Matrix3x3::operator*(float &_factor)
    {
        Matrix3x3 result;

        result.m_11 = m_11 * _factor, result.m_12 = m_12 * _factor,
        result.m_13 = m_13 * _factor;
        result.m_21 = m_21 * _factor, result.m_22 = m_22 * _factor,
        result.m_23 = m_23 * _factor;
        result.m_31 = m_31 * _factor, result.m_32 = m_32 * _factor,
        result.m_33 = m_33 * _factor;

        return result;
    }

    Vector3 Matrix3x3::operator*(Vector3 &_vector)
    {
        return Vector3(m_11 * _vector.x + m_12 * _vector.y + m_13 * _vector.z,
                       m_21 * _vector.x + m_22 * _vector.y + m_23 * _vector.z,
                       m_31 * _vector.x + m_32 * _vector.y + m_33 * _vector.z);
    }

    Matrix3x3 Matrix3x3::operator*(Matrix3x3 &_matrix)
    {
        Matrix3x3 result;

        result.m_11 = m_11 * _matrix.m_11 + m_12 * _matrix.m_21 + m_13 * _matrix.m_31;
        result.m_12 = m_11 * _matrix.m_12 + m_12 * _matrix.m_22 + m_13 * _matrix.m_32;
        result.m_13 = m_11 * _matrix.m_13 + m_12 * _matrix.m_23 + m_13 * _matrix.m_33;
        result.m_21 = m_21 * _matrix.m_11 + m_22 * _matrix.m_21 + m_23 * _matrix.m_31;
        result.m_22 = m_21 * _matrix.m_12 + m_22 * _matrix.m_22 + m_23 * _matrix.m_32;
        result.m_23 = m_21 * _matrix.m_13 + m_22 * _matrix.m_23 + m_23 * _matrix.m_33;
        result.m_31 = m_31 * _matrix.m_11 + m_32 * _matrix.m_21 + m_33 * _matrix.m_31;
        result.m_32 = m_31 * _matrix.m_12 + m_32 * _matrix.m_22 + m_33 * _matrix.m_32;
        result.m_33 = m_31 * _matrix.m_13 + m_32 * _matrix.m_23 + m_33 * _matrix.m_33;

        return result;
    }

    Matrix3x3 Matrix3x3::operator/(float &_factor)
    {
        Matrix3x3 result;

        result.m_11 = m_11 / _factor, result.m_12 = m_12 / _factor,
        result.m_13 = m_13 / _factor;
        result.m_21 = m_21 / _factor, result.m_22 = m_22 / _factor,
        result.m_23 = m_23 / _factor;
        result.m_31 = m_31 / _factor, result.m_32 = m_32 / _factor,
        result.m_33 = m_33 / _factor;

        return result;
    }

    Matrix3x3 Matrix3x3::operator/(Matrix3x3 &_matrix)
    {
        Matrix3x3 result;

        _matrix.Inverse();

        result = *this * _matrix;

        return result;
    }

    // Binary assignement math operators
    void Matrix3x3::operator+=(Matrix3x3 &_matrix)
    {
        m_11 += _matrix.m_11, m_12 += _matrix.m_12, m_13 += _matrix.m_13;
        m_21 += _matrix.m_21, m_22 += _matrix.m_22, m_23 += _matrix.m_23;
        m_31 += _matrix.m_31, m_32 += _matrix.m_32, m_33 += _matrix.m_33;
    }

    void Matrix3x3::operator-=(Matrix3x3 &_matrix)
    {
        m_11 -= _matrix.m_11, m_12 -= _matrix.m_12, m_13 -= _matrix.m_13;
        m_21 -= _matrix.m_21, m_22 -= _matrix.m_22, m_23 -= _matrix.m_23;
        m_31 -= _matrix.m_31, m_32 -= _matrix.m_32, m_33 -= _matrix.m_33;
    }

    void Matrix3x3::operator*=(float &_factor)
    {
        m_11 *= _factor, m_12 *= _factor, m_13 *= _factor;
        m_21 *= _factor, m_22 *= _factor, m_23 *= _factor;
        m_31 *= _factor, m_32 *= _factor, m_33 *= _factor;
    }

    Vector3 Matrix3x3::operator*=(Vector3 &_vector)
    {
        return Vector3(m_11 * _vector.x + m_12 * _vector.y + m_13 * _vector.z,
                       m_21 * _vector.x + m_22 * _vector.y + m_23 * _vector.z,
                       m_31 * _vector.x + m_32 * _vector.y + m_33 * _vector.z);
    }

    void Matrix3x3::operator*=(Matrix3x3 &_matrix)
    {
        Matrix3x3 temp = *this;

        m_11 = temp.m_11 * _matrix.m_11 + temp.m_12 * _matrix.m_21 +
               temp.m_13 * _matrix.m_31;
        m_12 = temp.m_11 * _matrix.m_12 + temp.m_12 * _matrix.m_22 +
               temp.m_13 * _matrix.m_32;
        m_13 = temp.m_11 * _matrix.m_13 + temp.m_12 * _matrix.m_23 +
               temp.m_13 * _matrix.m_33;

        m_21 = temp.m_21 * _matrix.m_11 + temp.m_22 * _matrix.m_21 +
               temp.m_23 * _matrix.m_31;
        m_22 = temp.m_21 * _matrix.m_12 + temp.m_22 * _matrix.m_22 +
               temp.m_23 * _matrix.m_32;
        m_23 = temp.m_21 * _matrix.m_13 + temp.m_22 * _matrix.m_23 +
               temp.m_23 * _matrix.m_33;

        m_31 = temp.m_31 * _matrix.m_11 + temp.m_32 * _matrix.m_21 +
               temp.m_33 * _matrix.m_31;
        m_32 = temp.m_31 * _matrix.m_12 + temp.m_32 * _matrix.m_22 +
               temp.m_33 * _matrix.m_32;
        m_33 = temp.m_31 * _matrix.m_13 + temp.m_32 * _matrix.m_23 +
               temp.m_33 * _matrix.m_33;
    }

    void Matrix3x3::operator/=(float &_factor)
    {
        m_11 /= _factor, m_12 /= _factor, m_13 /= _factor;
        m_21 /= _factor, m_22 /= _factor, m_23 /= _factor;
        m_31 /= _factor, m_32 /= _factor, m_33 /= _factor;
    }

    void Matrix3x3::operator/=(Matrix3x3 &_matrix)
    {
        _matrix.Inverse();

        *this *= _matrix;
    }
} // namespace DadEngine
