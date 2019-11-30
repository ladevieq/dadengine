#include "quaternion.hpp"

#include "../matrix/matrix3x3.hpp"
#include "../matrix/matrix4x4.hpp"
#include "../vector/vector3.hpp"

#include <cmath>


namespace DadEngine
{
    Quaternion::Quaternion(float _w, float _x, float _y, float _z)
    {
        w = _w;
        x = _x;
        y = _y;
        z = _z;
    }

    Quaternion::Quaternion(float _angle, Vector3 _axis)
    {
        float angle2 = _angle / 2.f;
        float sin2 = sin(angle2);

        w = cos(angle2);
        x = _axis.x * sin2;
        y = _axis.y * sin2;
        z = _axis.z * sin2;
    }

    Quaternion Quaternion::Conjugate()
    {
        return Quaternion(w, -x, -y, -z);
    }

    // Binary math operators
    Quaternion Quaternion::operator*(Quaternion &_quat)
    {
        return Quaternion(w * _quat.w - x * _quat.x - y * _quat.y - z * _quat.z,
                          w * _quat.x + x * _quat.w + y * _quat.z - z * _quat.y,
                          w * _quat.y - x * _quat.z + y * _quat.w + z * _quat.x,
                          w * _quat.z + x * _quat.y - y * _quat.x + z * _quat.w);
    }

    // Binary assignement math operators
    void Quaternion::operator*=(Quaternion &_quat)
    {
        Quaternion temp = *this;
        w = temp.w * _quat.w - temp.x * _quat.x - temp.y * _quat.y -
            temp.z * _quat.z;
        x = temp.w * _quat.x + temp.x * _quat.w + temp.y * _quat.z -
            temp.z * _quat.y;
        y = temp.w * _quat.y - temp.x * _quat.z + temp.y * _quat.w +
            temp.z * _quat.x;
        z = temp.w * _quat.z + temp.x * _quat.y - temp.y * _quat.x +
            temp.z * _quat.w;
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
} // namespace DadEngine
