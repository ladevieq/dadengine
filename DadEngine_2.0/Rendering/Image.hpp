#ifndef __IMAGE_HPP_
#define __IMAGE_HPP_

#include "../Core/Core.hpp"

namespace DadEngine::Rendering
{
	struct Extent2D
	{
		uint32 width;
		uint32 height;
	};

	class Image
	{

	public:

		Image() = default;

		Image(Extent2D & _InImageSize)
			:m_ImageSize(_InImageSize)
		{}

		FORCE_INLINE Extent2D& GetImageSize() { return m_ImageSize; }


	protected:
		
		Extent2D m_ImageSize;

	};
}

#endif //!__IMAGE_HPP_