#ifndef __COLOR_HPP_
#define __COLOR_HPP_

namespace DadEngine
{
    struct Color
    {
        Color() = default;

        Color(float _color[4])
            : r(_color[0]), g(_color[1]), b(_color[2]), a(_color[3])
        {
        }
        Color(float _r, float _g, float _b, float _a)
            : r(_r), g(_g), b(_b), a(_a)
        {
        }

        float r = 0.f;
        float g = 0.f;
        float b = 0.f;
        float a = 0.f;
    };
} // namespace DadEngine

#endif //__COLOR_HPP_

