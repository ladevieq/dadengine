#ifndef __MATRIX3X3_HPP_
#define __MATRIX3X3_HPP_


namespace DadEngine::Math
{
    class Vector2f;
    class Vector3f;

    class Matrix3x3
    {

        public:
        Matrix3x3() = default;

        Matrix3x3(Vector3f _InVectors[3U]);

        Matrix3x3(float _In11, float _In12, float _In13, float _In21, float _In22, float _In23, float _In31, float _In32, float _In33);

        Matrix3x3(float _InData[9U]);


        // Standard matrix functions
        void SetIdentity();

        void Transpose();

        void Inverse();

        float Determinant();

        void RotationX(float _InAngle);

        void RotationY(float _InAngle);

        void RotationZ(float _InAngle);

        void Rotation(float _InAngle, Vector3f _InAxis);

        void Scale(float _InScaleX, float _InScaleY, float _InScaleZ);

        void Translation(Vector2f _InTranslation);


        // Binary math operators
        Matrix3x3 operator+(Matrix3x3 &_InMatrix);

        Matrix3x3 operator-(Matrix3x3 &_InMatrix);

        Matrix3x3 operator*(float &_InFactor);

        Vector3f operator*(Vector3f &_InVector);

        Matrix3x3 operator*(Matrix3x3 &_InMatrix);

        Matrix3x3 operator/(float &_InFactor);

        Matrix3x3 operator/(Matrix3x3 &_InMatrix);

        // Binary assignement math operators
        void operator+=(Matrix3x3 &_InMatrix);

        void operator-=(Matrix3x3 &_InMatrix);

        void operator*=(float &_InFactor);

        Vector3f operator*=(Vector3f &_InVector);

        void operator*=(Matrix3x3 &_InMatrix);

        void operator/=(float &_InFactor);

        void operator/=(Matrix3x3 &_InMatrix);


        float m_11 = 1.f, m_12 = 0.f, m_13 = 0.f;
        float m_21 = 0.f, m_22 = 1.f, m_23 = 0.f;
        float m_31 = 0.f, m_32 = 0.f, m_33 = 1.f;
    };

    namespace Test
    {
        void TestMatrix3x3();
    }
} // namespace DadEngine::Math

#endif //__MATRIX3X3_HPP_