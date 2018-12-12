#ifndef __QUATERNION_HPP_
#define __QUATERNION_HPP_


namespace DadEngine::Math
{
    class Vector3f;
	class Matrix3x3;
    class Matrix4x4;

    class Quaternion
    {

        public:
        Quaternion() = default;

        Quaternion(float _InW, float _InX, float _InY, float _InZ);

        Quaternion(float _InAngle, Vector3f _InAxis);

        Quaternion Conjugate();

        // Binary math operators
        Quaternion operator*(Quaternion &_InQuat);

        // Binary assignement math operators
        void operator*=(Quaternion &_InQuat);

        Matrix3x3 GetRotationMatrix();

        Matrix4x4 GetRotationMatrixExtended();


        float w = 0.f; // Scalar part
        float x = 0.f; // -----------
        float y = 0.f; // Complex part
        float z = 0.f; // -----------
    };


    static const Quaternion IdentityQuaternion(1.f, 0.f, 0.f, 0.f);
} // namespace DadEngine::Math

#endif //__QUATERNION_HPP_