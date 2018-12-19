#ifndef __MATRIX2X2_HPP_
#define __MATRIX2X2_HPP_


namespace DadEngine::Math
{
    class Vector2f;

    class Matrix2x2
    {

        public:
        Matrix2x2() = default;

        Matrix2x2(Vector2f _InVectors[2U]);

        Matrix2x2(float _In11, float _In12, float _In21, float _In22);

        Matrix2x2(float _InData[4U]);


        // Standard matrix functions
        void SetIdentity();

        void Transpose();

        void Inverse();

        float Determinant();

        void Rotation(float _InAngle);

        void Scale(float _InScaleX, float _InScaleY);


        // Binary math operators
        Matrix2x2 operator+(Matrix2x2 &_InMatrix);

        Matrix2x2 operator-(Matrix2x2 &_InMatrix);

        Matrix2x2 operator*(float &_InFactor);

        Vector2f operator*(Vector2f &_InVector);

        Matrix2x2 operator*(Matrix2x2 &_InMatrix);

        Matrix2x2 operator/(float &_InFactor);

        Matrix2x2 operator/(Matrix2x2 &_InMatrix);

        // Binary assignement math operators
        void operator+=(Matrix2x2 &_InMatrix);

        void operator-=(Matrix2x2 &_InMatrix);

        void operator*=(float &_InFactor);

        Vector2f operator*=(Vector2f &_InVector);

        void operator*=(Matrix2x2 &_InMatrix);

        void operator/=(float &_InFactor);

        void operator/=(Matrix2x2 &_InMatrix);


        float m_11 = 1.f, m_12 = 0.f;
        float m_21 = 0.f, m_22 = 1.f;
    };


    namespace Test
    {
        void TestMatrix2x2();
    }
} // namespace DadEngine::Math

#endif //__MATRIX2X2_HPP_