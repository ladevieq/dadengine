#include "Vector4f.hpp"

#include "MathFunctions.hpp"

namespace DadEngine::Math
{
	float Vector4f::Length()
	{
		return Square(SqLength());
	}
	
	float Vector4f::Angle(Vector4f& _InVector)
	{
		return Acos(Dot(_InVector / (Length() * _InVector.Length())));
	}
}