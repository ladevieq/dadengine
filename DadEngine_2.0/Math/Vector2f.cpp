#include "Vector2f.hpp"

#include "MathFunctions.hpp"

namespace DadEngine::Math
{
	float Vector2f::Length()
	{
		return Square(SqLength());
	}

	float Vector2f::Angle(Vector2f& _InVector)
	{
		Vector2f tempVec = _InVector / (Length() * _InVector.Length());

		return Acos(Dot(tempVec));
	}
}