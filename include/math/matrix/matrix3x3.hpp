#ifndef __MATRIX3X3_HPP_
#define __MATRIX3X3_HPP_

#include <array>

namespace DadEngine
{
    class Vector2;
    class Vector3;

    class Matrix3x3
    {

        public:
        Matrix3x3() = default;

        Matrix3x3(std::array<Vector3, 3> _vectors);

        Matrix3x3(float _11, float _12, float _13, float _21, float _22, float _23, float _31, float _32, float _33);

        Matrix3x3(std::array<float, 9> _data);


        // Standard matrix functions
        void SetIdentity();

        void Transpose();

        void Inverse();

        float Determinant() const;

        void RotationX(float _angle);

        void RotationY(float _angle);

        void RotationZ(float _angle);

        void Rotation(float _angle, Vector3 _axis);

        void Scale(float _scaleX, float _scaleY, float _scaleZ);

        void Translation(Vector2 _translation);


        // Binary math operators
        Matrix3x3 operator+(Matrix3x3 &_matrix) const;

        Matrix3x3 operator-(Matrix3x3 &_matrix) const;

        Matrix3x3 operator*(float &_factor) const;

        Vector3 operator*(Vector3 &_vector) const;

        Matrix3x3 operator*(Matrix3x3 &_matrix) const;

        Matrix3x3 operator/(float &_factor) const;

        Matrix3x3 operator/(Matrix3x3 &_matrix) const;

        // Binary assignement math operators
        void operator+=(Matrix3x3 &_matrix);

        void operator-=(Matrix3x3 &_matrix);

        void operator*=(float &_factor);

        Vector3 operator*=(Vector3 &_vector) const;

        void operator*=(Matrix3x3 &_matrix);

        void operator/=(float &_factor);

        void operator/=(Matrix3x3 &_matrix);


        float m_11 = 1.f, m_12 = 0.f, m_13 = 0.f;
        float m_21 = 0.f, m_22 = 1.f, m_23 = 0.f;
        float m_31 = 0.f, m_32 = 0.f, m_33 = 1.f;
    };
} // namespace DadEngine

#endif //__MATRIX3X3_HPP_
