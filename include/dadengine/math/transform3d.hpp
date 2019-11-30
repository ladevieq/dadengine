#ifndef __TRANSFORM3D_HPP_
#define __TRANSFORM3D_HPP_

namespace DadEngine
{
    class Transform3D
    {

        public:
        Transform3D() = default;

        Matrix4x4 GetTransformMatrix()
        {
            Matrix4x4 rotation = m_rotation.GetRotationMatrixExtended();
            Matrix4x4 position;
            position.m_14 = m_position.x;
            position.m_24 = m_position.y;
            position.m_34 = m_position.z;
            Matrix4x4 scale;
            scale.m_12 = m_scale.x;
            scale.m_22 = m_scale.y;
            scale.m_33 = m_scale.z;

            Matrix4x4 result = position * rotation;
            result *= scale;

            return result;
        }


        Vector3 m_position = NullVector3;
        Vector3 m_scale = NullVector3;
        Quaternion m_rotation = IdentityQuaternion;
    };
} // namespace DadEngine

#endif //!__TRANSFORM3D_HPP_

