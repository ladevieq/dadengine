#include "matrix/matrix2x2.hpp"

#include "constants.hpp"
#include "vector/vector2.hpp"

#include <limits>


namespace DadEngine
{
    Matrix2x2::Matrix2x2(std::array<Vector2, 2> _vectors)
    {
        m_11 = _vectors[0U].x, m_12 = _vectors[1U].x;
        m_21 = _vectors[0U].y, m_22 = _vectors[1U].y;
    }

    Matrix2x2::Matrix2x2(float _11, float _12, float _21, float _22)
    {
        m_11 = _11, m_12 = _12;
        m_21 = _21, m_22 = _22;
    }

    Matrix2x2::Matrix2x2(std::array<float, 4> _data)
    {
        m_11 = _data[0U], m_12 = _data[1U];
        m_21 = _data[2U], m_22 = _data[3U];
    }


    // Standard matrix functions
    void Matrix2x2::SetIdentity()
    {
        m_11 = 1.f, m_12 = 0.f;
        m_21 = 0.f, m_22 = 1.f;
    }

    void Matrix2x2::Transpose()
    {
        Matrix2x2 temp = *this;

        m_12 = temp.m_21;
        m_21 = temp.m_12;
    }

    void Matrix2x2::Inverse()
    {
        Matrix2x2 temp    = *this;
        float determinant = Determinant();

        if (determinant > std::numeric_limits<decltype(determinant)>::epsilon()
            || determinant < std::numeric_limits<decltype(determinant)>::epsilon()) {
            determinant = 1.f / determinant;

            m_11 = determinant * temp.m_22, m_12 = determinant * -temp.m_12;
            m_21 = determinant * -temp.m_21, m_22 = determinant * temp.m_11;
        }
    }

    float Matrix2x2::Determinant() const
    {
        return m_11 * m_22 - m_12 * m_21;
    }

    void Matrix2x2::Rotation(float _angle)
    {
        m_11 = std::cos(_angle), m_12 = -std::sin(_angle);
        m_12 = std::sin(_angle), m_12 = std::cos(_angle);
    }

    void Matrix2x2::Scale(float _scaleX, float _scaleY)
    {
        m_11 = _scaleX, m_12 = 0.f;
        m_21 = 0.f, m_22 = _scaleY;
    }


    // Binary math operators
    Matrix2x2 Matrix2x2::operator+(Matrix2x2 &_matrix) const
    {
        Matrix2x2 result;

        result.m_11 = m_11 + _matrix.m_11, result.m_12 = m_12 + _matrix.m_12;
        result.m_21 = m_21 + _matrix.m_21, result.m_22 = m_22 + _matrix.m_22;

        return result;
    }

    Matrix2x2 Matrix2x2::operator-(Matrix2x2 &_matrix) const
    {
        Matrix2x2 result;

        result.m_11 = m_11 - _matrix.m_11, result.m_12 = m_12 - _matrix.m_12;
        result.m_21 = m_21 - _matrix.m_21, result.m_22 = m_22 - _matrix.m_22;

        return result;
    }

    Matrix2x2 Matrix2x2::operator*(float &_factor) const
    {
        Matrix2x2 result;

        result.m_11 = m_11 * _factor, result.m_12 = m_12 * _factor;
        result.m_21 = m_21 * _factor, result.m_22 = m_22 * _factor;

        return result;
    }

    Vector2 Matrix2x2::operator*(Vector2 &_vector) const
    {
        return Vector2(m_11 * _vector.x + m_12 * _vector.y,
                       m_21 * _vector.x + m_22 * _vector.y);
    }

    Matrix2x2 Matrix2x2::operator*(Matrix2x2 &_matrix) const
    {
        Matrix2x2 result;

        result.m_11 = m_11 * _matrix.m_11 + m_12 * _matrix.m_21;
        result.m_12 = m_11 * _matrix.m_12 + m_12 * _matrix.m_22;
        result.m_21 = m_21 * _matrix.m_11 + m_22 * _matrix.m_21;
        result.m_22 = m_22 * _matrix.m_22 + m_21 * _matrix.m_12;

        return result;
    }

    Matrix2x2 Matrix2x2::operator/(float &_factor) const
    {
        Matrix2x2 result;

        result.m_11 = m_11 / _factor, result.m_12 = m_12 / _factor;
        result.m_21 = m_21 / _factor, result.m_22 = m_22 / _factor;

        return result;
    }

    Matrix2x2 Matrix2x2::operator/(Matrix2x2 &_matrix) const
    {
        Matrix2x2 result;

        _matrix.Inverse();

        result = *this * _matrix;

        return result;
    }

    // Binary assignement math operators
    void Matrix2x2::operator+=(Matrix2x2 &_matrix)
    {
        m_11 += _matrix.m_11, m_12 += _matrix.m_12;
        m_21 += _matrix.m_21, m_22 += _matrix.m_22;
    }

    void Matrix2x2::operator-=(Matrix2x2 &_matrix)
    {
        m_11 -= _matrix.m_11, m_12 -= _matrix.m_12;
        m_21 -= _matrix.m_21, m_22 -= _matrix.m_22;
    }

    void Matrix2x2::operator*=(float &_factor)
    {
        m_11 *= _factor, m_12 *= _factor;
        m_21 *= _factor, m_22 *= _factor;
    }

    Vector2 Matrix2x2::operator*=(Vector2 &_vector) const
    {
        return Vector2(m_11 * _vector.x + m_12 * _vector.y,
                       m_21 * _vector.x + m_22 * _vector.y);
    }

    void Matrix2x2::operator*=(Matrix2x2 &_matrix)
    {
        Matrix2x2 temp = *this;

        m_11 = temp.m_11 * _matrix.m_11 + temp.m_12 * _matrix.m_21;
        m_12 = temp.m_11 * _matrix.m_12 + temp.m_12 * _matrix.m_22;
        m_21 = temp.m_21 * _matrix.m_11 + temp.m_22 * _matrix.m_21;
        m_22 = temp.m_22 * _matrix.m_22 + temp.m_21 * _matrix.m_12;
    }

    void Matrix2x2::operator/=(float &_factor)
    {
        m_11 /= _factor, m_12 /= _factor;
        m_21 /= _factor, m_22 /= _factor;
    }

    void Matrix2x2::operator/=(Matrix2x2 &_matrix)
    {
        _matrix.Inverse();

        *this *= _matrix;
    }
} // namespace DadEngine
