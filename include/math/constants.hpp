#pragma once

#include <cmath>

inline constexpr double RadToDeg(double _x)
{
    return _x * 180.0 / M_PI;
}

inline constexpr float RadToDeg(float _x)
{
    return _x * 180.0 / M_PI;
}

inline constexpr float DegToRad(float _x)
{
    return _x * M_PI / 180.0;
}

inline constexpr double DegToRad(double _x)
{
    return _x * M_PI / 180.0;
}
