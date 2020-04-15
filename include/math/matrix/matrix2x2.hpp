#ifndef __MATRIX2X2_HPP_
#define __MATRIX2X2_HPP_


namespace DadEngine
{
    class Vector2;

    class Matrix2x2
    {

        public:
        Matrix2x2() = default;

        Matrix2x2(Vector2 _vectors[2U]);

        Matrix2x2(float _11, float _12, float _21, float _22);

        Matrix2x2(float _data[4U]);


        // Standard matrix functions
        void SetIdentity();

        void Transpose();

        void Inverse();

        float Determinant();

        void Rotation(float _angle);

        void Scale(float _scaleX, float _scaleY);


        // Binary math operators
        Matrix2x2 operator+(Matrix2x2 &_matrix);

        Matrix2x2 operator-(Matrix2x2 &_matrix);

        Matrix2x2 operator*(float &_factor);

        Vector2 operator*(Vector2 &_vector);

        Matrix2x2 operator*(Matrix2x2 &_matrix);

        Matrix2x2 operator/(float &_factor);

        Matrix2x2 operator/(Matrix2x2 &_matrix);

        // Binary assignement math operators
        void operator+=(Matrix2x2 &_matrix);

        void operator-=(Matrix2x2 &_matrix);

        void operator*=(float &_factor);

        Vector2 operator*=(Vector2 &_vector);

        void operator*=(Matrix2x2 &_matrix);

        void operator/=(float &_factor);

        void operator/=(Matrix2x2 &_matrix);


        float m_11 = 1.f, m_12 = 0.f;
        float m_21 = 0.f, m_22 = 1.f;
    };
} // namespace DadEngine

#endif //__MATRIX2X2_HPP_

