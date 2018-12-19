#ifndef __VECTOR4F_HPP_
#define __VECTOR4F_HPP_


namespace DadEngine::Math
{
	class Vector4f
	{

	public:

		Vector4f() = default;

		Vector4f(float _InX, float _InY, float _InZ, float _InW);


		// Standard vector functions
        void Normalize();

		float Length();

		float SqLength();

		float Angle(Vector4f& _InVector);

		float Dot(Vector4f &_InVector);

		Vector4f Lerp(Vector4f &_InFrom, Vector4f &_InTo, float _InFactor);

		// Unary operators
        Vector4f operator-();

		// Binary math operators
        Vector4f operator+(Vector4f &_InVector);

		Vector4f operator-(Vector4f &_InVector);

		Vector4f operator*(float _InVal);

		Vector4f operator/(float _InVal);

		Vector4f operator^(Vector4f &_InVector);


		// Binary assignement math operators
        void operator+=(Vector4f &_InVector);

		void operator-=(Vector4f &_InVector);

		void operator*=(float _InVal);

		void operator/=(float _InVal);

		void operator^=(Vector4f &_InVector);


		float x = 0.f;
		float y = 0.f;
		float z = 0.f;
		float w = 0.f;
	};
}

#endif //__VECTOR4F_HPP_