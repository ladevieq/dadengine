#ifndef __MATH_FUNCTIONS_HPP_
#define __MATH_FUNCTIONS_HPP_

/*#include "Vector2f.hpp"
#include "Vector3f.hpp"
#include "Vector4f.hpp"*/
#include <stdint.h>

namespace DadEngine::Math
{
	float Cos(float _InVal);

	float Acos(float _InVal);

	float Sin(float _InVal);
	
	float Asin(float _InVal);

	float Tan(float _InVal);

	float Atan(float _InVal);

	float Atan2(float _InX, float _InY);

	float Pow();

	float Square(float _InVal);

	float Exp(float _InVal);

	float Log(float _InVal);

	void Factorial();


	void Clamp();

	// Absolute
    int8_t Abs(int8_t _InVal);

	int16_t Abs(int16_t _InVal);

	int32_t Abs(int32_t _InVal);

	int64_t Abs(int64_t _InVal);

	float Abs(float _InVal);

	double Abs(double _InVal);

	/*Vector2f Abs(Vector2f& _InVector);

	Vector3f Abs(Vector3f& _InVector);

	Vector4f Abs(Vector4f& _InVector);*/

	namespace Test
	{
        void TestMathFunctions();
	}
}

#endif //__MATH_FUNCTIONS_HPP_