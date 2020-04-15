#ifndef __QUATERNION_HPP_
#define __QUATERNION_HPP_


namespace DadEngine
{
    class Vector3;
    class Matrix3x3;
    class Matrix4x4;

    class Quaternion
    {

        public:
        Quaternion() = default;

        Quaternion(float _w, float _x, float _y, float _z);

        Quaternion(float _angle, Vector3 _axis);

        Quaternion Conjugate() const;

        // Binary math operators
        Quaternion operator*(Quaternion &_quat) const;

        // Binary assignement math operators
        void operator*=(Quaternion &_quat);

        Matrix3x3 GetRotationMatrix() const;

        Matrix4x4 GetRotationMatrixExtended() const;

        static inline Quaternion Identity()
        {
            return Quaternion { 1.f, 0.f, 0.f, 0.f };
        }


        float w = 0.f; // Scalar part
        float x = 0.f; // -----------
        float y = 0.f; // Complex part
        float z = 0.f; // -----------
    };
} // namespace DadEngine

#endif //__QUATERNION_HPP_
