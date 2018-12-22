#ifndef __LIGHT_HPP_
#define __LIGHT_HPP_

#include "../../math/math.hpp"

namespace DadEngine::Rendering
{
	class Light
	{
	public:

		float m_fDiffuseIntensity = 1.f;
		float m_fSpecularIntensity = 1.f;
		float m_fEmissiveIntensity = 1.f;
	};
}

#endif // !__LIGHT_HPP_