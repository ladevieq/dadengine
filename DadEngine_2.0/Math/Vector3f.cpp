#include "Vector3f.hpp"

#include "MathFunctions.hpp"

namespace DadEngine::Math
{
	float Vector3f::Length()
	{
		return Square(SqLength());
	}

	float Vector3f::Angle(Vector3f& _InVector)
	{
		return Acos(Dot(_InVector / (Length() * _InVector.Length())));
	}
}