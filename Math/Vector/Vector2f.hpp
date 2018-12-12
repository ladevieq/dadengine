#ifndef __VECTOR2F_HPP_
#define __VECTOR2F_HPP_


namespace DadEngine::Math
{
    class Vector2f
    {

        public:
        Vector2f() = default;

        Vector2f(float _InX, float _InY);


        // Standard vector functions
        void Normalize();

        void Reflect();

        void Projection();

        float Length();

        float SqLength();

        float Angle(Vector2f &_InVector);

        float Dot(Vector2f &_InVector);

        Vector2f Lerp(Vector2f &_InFrom, Vector2f &_InTo, float _InFactor);

        // Unary operators
        Vector2f operator-();

        // Binary math operators
        Vector2f operator+(Vector2f &_InVector);

        Vector2f operator-(Vector2f &_InVector);

        Vector2f operator*(float _InVal);

        Vector2f operator/(float _InVal);

        float operator^(Vector2f &_InVector);


        // Binary assignement math operators
        void operator+=(Vector2f &_InVector);

        void operator-=(Vector2f &_InVector);

        void operator*=(float _InVal);

        void operator/=(float _InVal);


        float x = 0.f;
        float y = 0.f;
    };
} // namespace DadEngine::Math

#endif //__VECTOR2F_HPP_