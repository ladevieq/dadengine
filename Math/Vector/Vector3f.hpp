#ifndef __VECTOR3F_HPP_
#define __VECTOR3F_HPP_


namespace DadEngine::Math
{
	class Vector3f
	{

	public:

		Vector3f() = default;

		Vector3f(float _InX, float _InY, float _InZ);


		// Standard vector functions
		void Normalize();

		float Length();

		float SqLength();

		float Angle(Vector3f& _InVector);

		float Dot(Vector3f& _InVector);

		Vector3f Lerp(Vector3f& _InFrom, Vector3f& _InTo, float _InFactor);

		// Unary operators
		Vector3f operator-();

		// Binary math operators
		Vector3f operator+(Vector3f& _InVector);

		Vector3f operator-(Vector3f& _InVector);

		Vector3f operator*(float _InVal);

		Vector3f operator/(float _InVal);

		Vector3f operator^(Vector3f& _InVector);


		// Binary assignement math operators
		void operator+=(Vector3f& _InVector);

		void operator+=(const Vector3f& _InVector);

		void operator-=(Vector3f& _InVector);

		void operator-=(const Vector3f& _InVector);

		void operator*=(float _InVal);

		void operator/=(float _InVal);

		void operator^=(Vector3f &_InVector);


		float x = 0.f;
		float y = 0.f;
		float z = 0.f;
	};

	static const Vector3f NullVector3f(0.f, 0.f, 0.f);
}

#endif //__VECTOR3F_HPP_