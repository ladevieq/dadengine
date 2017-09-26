#ifndef __CONSTANTS_HPP_
#define __CONSTANTS_HPP_

#define _PI 3.141592653589793
#define _2PI 6.283185307179586
#define _PI2 1.570796326794896

#define EULER_CONSTANT 2.718281828459045

#define FLOAT_EPSILON 1.192092896e-07F
#define DOUBLE_EPSILON 2.2204460492503131e-016

#define RADTODEG(x) x * 180.0 / 3.141592653589793
#define DEGTORAD(x) x * 3.141592653589793 / 180.0

#define MAX(x, y)
#define MIN(x, y)

namespace DadEngine::Math::Test
{
	FORCE_INLINE void TestMathConstants()
	{
		double y = DEGTORAD(180.0);

		y = RADTODEG(y);

		y = 0.f;
	}
}

#endif // !__CONSTANTS_HPP_
