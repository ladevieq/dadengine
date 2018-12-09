#include "MathFunctions.hpp"

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
	int8 Abs(int8 _InVal)
	{
		return (_InVal ^ 0xff) + 0x1;
	}

	int16 Abs(int16 _InVal)
	{
		return (_InVal ^ 0xffff) + 0x1;
	}

	int32 Abs(int32 _InVal)
	{
		return (_InVal ^ 0xffffffff) + 0x1;
	}

	int64 Abs(int64 _InVal)
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
}