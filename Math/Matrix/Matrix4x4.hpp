#ifndef __MATRIX4X4_HPP_
#define __MATRIX4X4_HPP_


namespace DadEngine::Math
{
    class Vector3f;
    class Vector4f;

    class Matrix4x4
    {

        public:
        Matrix4x4() = default;

        Matrix4x4(Vector4f _InVectors[4U]);

        Matrix4x4(float _In11,
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
                  float _In44);

        Matrix4x4(float _InData[16U]);


        // Standard matrix functions
        void SetIdentity();

        void Transpose();

        void Inverse();

        float Determinant();

        void Translation(Vector3f _InTranslation);

        void Orthographic();

        void Perpespective(float _InNear, float _InFar, float _InFov);

        void LookAt(Vector3f &_InEyePosition, Vector3f &_InTargetPosition, Vector3f &_InUp);


        // Binary math operators
        Matrix4x4 operator+(Matrix4x4 &_InMatrix);

        Matrix4x4 operator-(Matrix4x4 &_InMatrix);

        Matrix4x4 operator*(float &_InFactor);

        Vector4f operator*(Vector4f &_InVector);

        Matrix4x4 operator*(Matrix4x4 &_InMatrix);

        Matrix4x4 operator/(float &_InFactor);

        Matrix4x4 operator/(Matrix4x4 &_InMatrix);


        // Binary assignement math operators
        void operator+=(Matrix4x4 &_InMatrix);

        void operator-=(Matrix4x4 &_InMatrix);

        void operator*=(float &_InFactor);

        Vector4f operator*=(Vector4f &_InVector);

        void operator*=(Matrix4x4 &_InMatrix);

        void operator/=(float &_InFactor);

        void operator/=(Matrix4x4 &_InMatrix);


        float m_11 = 1.f, m_12 = 0.f, m_13 = 0.f, m_14 = 0.f;
        float m_21 = 0.f, m_22 = 1.f, m_23 = 0.f, m_24 = 0.f;
        float m_31 = 0.f, m_32 = 0.f, m_33 = 1.f, m_34 = 0.f;
        float m_41 = 0.f, m_42 = 0.f, m_43 = 0.f, m_44 = 1.f;
    };


    namespace Test
    {
        void TestMatrix4x4();
    }
} // namespace DadEngine::Math

#endif //__MATRIX4X4_HPP_