#ifndef __MATRIX4X4_HPP_
#define __MATRIX4X4_HPP_


namespace DadEngine
{
    class Vector3;
    class Vector4;

    class Matrix4x4
    {

        public:
        Matrix4x4() = default;

        Matrix4x4(Vector4 _vectors[4U]);

        Matrix4x4(float _11,
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
                  float _44);

        Matrix4x4(float _data[16U]);


        // Standard matrix functions
        void SetIdentity();

        void Transpose();

        void Inverse();

        float Determinant();

        void Translation(Vector3 _translation);

        void Orthographic();

        void Perpespective(float _near, float _far, float _fov);

        void LookAt(Vector3 &_eyePosition, Vector3 &_targetPosition, Vector3 &_up);


        // Binary math operators
        Matrix4x4 operator+(Matrix4x4 &_matrix);

        Matrix4x4 operator-(Matrix4x4 &_matrix);

        Matrix4x4 operator*(float &_factor);

        Vector4 operator*(Vector4 &_vector);

        Matrix4x4 operator*(Matrix4x4 &_matrix);

        Matrix4x4 operator/(float &_factor);

        Matrix4x4 operator/(Matrix4x4 &_matrix);


        // Binary assignement math operators
        void operator+=(Matrix4x4 &_matrix);

        void operator-=(Matrix4x4 &_matrix);

        void operator*=(float &_factor);

        Vector4 operator*=(Vector4 &_vector);

        void operator*=(Matrix4x4 &_matrix);

        void operator/=(float &_factor);

        void operator/=(Matrix4x4 &_matrix);


        float m_11 = 1.f, m_12 = 0.f, m_13 = 0.f, m_14 = 0.f;
        float m_21 = 0.f, m_22 = 1.f, m_23 = 0.f, m_24 = 0.f;
        float m_31 = 0.f, m_32 = 0.f, m_33 = 1.f, m_34 = 0.f;
        float m_41 = 0.f, m_42 = 0.f, m_43 = 0.f, m_44 = 1.f;
    };
} // namespace DadEngine

#endif //__MATRIX4X4_HPP_

