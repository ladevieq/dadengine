#ifndef __IMAGE_HPP_
#define __IMAGE_HPP_

#include <cstdint>

namespace DadEngine
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

        Image(Extent2D &_imageSize) : m_imageSize(_imageSize)
        {
        }

        Extent2D &GetImageSize()
        {
            return m_imageSize;
        }


        protected:
        Extent2D m_imageSize;
    };
} // namespace DadEngine

#endif //__IMAGE_HPP_

