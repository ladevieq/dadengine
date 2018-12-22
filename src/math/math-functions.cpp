#include "math-functions.hpp"

#include <math.h>

namespace DadEngine::Math
{
	float Cos(float _InVal)
	{
		return cosf(_InVal);
	}

	float Acos(float _InVal)
	{
		return acosf(_InVal);
	}

	float Sin(float _InVal)
	{
		return sinf(_InVal);
	}

	float Asin(float _InVal)
	{
		return asinf(_InVal);
	}

	float Tan(float _InVal)
	{
		return tanf(_InVal);
	}

	float Atan(float _InVal)
	{
		return atanf(_InVal);
	}

	float Atan2(float _InX, float _InY)
	{
		return atan2f(_InX, _InY);
	}

	float Pow()
	{
		return 0.f;
	}

	float Square(float _InVal)
	{
		return sqrtf(_InVal);
	}

	float Exp(float _InVal)
	{
		return expf(_InVal);
	}

	float Log(float _InVal)
	{
		return logf(_InVal);
	}

	void Factorial()
	{

	}


	// Absolute
    int8_t Abs(int8_t _InVal)
	{
		return (_InVal ^ 0xff) + 0x1;
	}

	int16_t Abs(int16_t _InVal)
	{
		return (_InVal ^ 0xffff) + 0x1;
	}

	int32_t Abs(int32_t _InVal)
	{
		return (_InVal ^ 0xffffffff) + 0x1;
	}

	int64_t Abs(int64_t _InVal)
	{
		return (_InVal ^ 0xffffffffffffffff) + 0x1;
	}

	float Abs(float _InVal)
	{
		return fabsf(_InVal);//_InVector.x
	}

	double Abs(double _InVal)
	{
		return -_InVal;//_InVector.x
	}

	/*Vector2f Abs(Vector2f _InVector)
	{
		return Vector2f(Abs(_InVector.x), Abs(_InVector.y));
	}

	Vector3f Abs(Vector3f _InVector)
	{
		return Vector3f(Abs(_InVector.x), Abs(_InVector.y), Abs(_InVector.z));
	}

	Vector4f Abs(Vector4f _InVector)
	{
		return Vector4f(Abs(_InVector.x), Abs(_InVector.y), Abs(_InVector.z), Abs(_InVector.w));
	}*/

	namespace Test
	{
        void TestMathFunctions()
        {
            int64_t i = 100000000;

            i = Abs(i);

            i = 0;
        }
	}
}