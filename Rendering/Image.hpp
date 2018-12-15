#ifndef __IMAGE_HPP_
#define __IMAGE_HPP_

// #include "../Core/Core.hpp"
#include <stdint.h>

namespace DadEngine::Rendering
{
	struct Extent2D
	{
        uint32_t width;
        uint32_t height;
	};

	class Image
	{

	public:

		Image() = default;

		Image(Extent2D & _InImageSize)
			:m_ImageSize(_InImageSize)
		{}

		Extent2D& GetImageSize() { return m_ImageSize; }


	protected:
		
		Extent2D m_ImageSize;

	};
}

#endif //__IMAGE_HPP_