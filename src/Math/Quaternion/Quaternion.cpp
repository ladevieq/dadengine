#include "Quaternion.hpp"

#include "../MathFunctions.hpp"
#include "../Vector/Vector3f.hpp"
#include "../Matrix/Matrix3x3.hpp"
#include "../Matrix/Matrix4x4.hpp"


namespace DadEngine::Math
{
    Quaternion::Quaternion(float _InW, float _InX, float _InY, float _InZ)
    {
        w = _InW;
        x = _InX;
        y = _InY;
        z = _InZ;
    }

    Quaternion::Quaternion(float _InAngle, Vector3f _InAxis)
    {
        float angle2 = _InAngle / 2.f;
        float sin2 = Sin(angle2);

        w = Cos(angle2);
        x = _InAxis.x * sin2;
        y = _InAxis.y * sin2;
        z = _InAxis.z * sin2;
    }

    Quaternion Quaternion::Conjugate()
    {
        return Quaternion(w, -x, -y, -z);
    }

    // Binary math operators
    Quaternion Quaternion::operator*(Quaternion &_InQuat)
    {
        return Quaternion(w * _InQuat.w - x * _InQuat.x - y * _InQuat.y - z * _InQuat.z,
                          w * _InQuat.x + x * _InQuat.w + y * _InQuat.z - z * _InQuat.y,
                          w * _InQuat.y - x * _InQuat.z + y * _InQuat.w + z * _InQuat.x,
                          w * _InQuat.z + x * _InQuat.y - y * _InQuat.x + z * _InQuat.w);
    }

    // Binary assignement math operators
    void Quaternion::operator*=(Quaternion &_InQuat)
    {
        Quaternion temp = *this;
        w = temp.w * _InQuat.w - temp.x * _InQuat.x - temp.y * _InQuat.y - temp.z * _InQuat.z;
        x = temp.w * _InQuat.x + temp.x * _InQuat.w + temp.y * _InQuat.z - temp.z * _InQuat.y;
        y = temp.w * _InQuat.y - temp.x * _InQuat.z + temp.y * _InQuat.w + temp.z * _InQuat.x;
        z = temp.w * _InQuat.z + temp.x * _InQuat.y - temp.y * _InQuat.x + temp.z * _InQuat.w;
    }

    Matrix3x3 Quaternion::GetRotationMatrix()
    {
        Matrix3x3 result;

        result.m_11 = 1 - (2 * y * y) - (2 * z * z);
        result.m_12 = (2 * x * y) - (2 * w * z);
        result.m_13 = (2 * x * z) + (2 * w * y);
        result.m_21 = (2 * x * y) + (2 * w * z);
        result.m_22 = 1 - (2 * x * x) - (2 * z * z);
        result.m_23 = (2 * y * z) - (2 * w * x);
        result.m_31 = (2 * x * z) - (2 * w * y);
        result.m_32 = (2 * y * z) + (2 * w * x);
        result.m_33 = 1 - (2 * x * x) - (2 * y * y);

        return result;
    }

    Matrix4x4 Quaternion::GetRotationMatrixExtended()
    {
        Matrix4x4 result;

        result.m_11 = 1 - (2 * y * y) - (2 * z * z);
        result.m_12 = (2 * x * y) - (2 * w * z);
        result.m_13 = (2 * x * z) + (2 * w * y);
        result.m_21 = (2 * x * y) + (2 * w * z);
        result.m_22 = 1 - (2 * x * x) - (2 * z * z);
        result.m_23 = (2 * y * z) - (2 * w * x);
        result.m_31 = (2 * x * z) - (2 * w * y);
        result.m_32 = (2 * y * z) + (2 * w * x);
        result.m_33 = 1 - (2 * x * x) - (2 * y * y);

        return result;
    }
} // namespace DadEngine::Math