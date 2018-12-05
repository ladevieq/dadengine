#ifndef __TRANSFORM3D_HPP_
#define __TRANSFORM3D_HPP_

namespace DadEngine::Math
{
	class Transform3D
	{

	public:

		Transform3D() = default;

		Matrix4x4 GetTransformMatrix()
		{
			Matrix4x4 rotation = m_Rotation.GetRotationMatrixExtended();
			Matrix4x4 position;
			position.m_14 = m_Position.x;
			position.m_24 = m_Position.y;
			position.m_34 = m_Position.z;
			Matrix4x4 scale;
			scale.m_12 = m_Scale.x;
			scale.m_22 = m_Scale.y;
			scale.m_33 = m_Scale.z;

			Matrix4x4 result = position * rotation;
			result *= scale;

			return result;
		}


		Vector3f m_Position = NullVector3f;
		Vector3f m_Scale = NullVector3f;
		Quaternion m_Rotation = IdentityQuaternion;
	};
}

#endif //!__TRANSFORM3D_HPP_