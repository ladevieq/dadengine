#ifndef __VECTOR2_HPP_
#define __VECTOR2_HPP_


namespace DadEngine
{
    class Vector2
    {

        public:
        Vector2() = default;

        Vector2(float _x, float _y);


        // Standard vector functions
        void Normalize();

        void Reflect();

        void Projection();

        float Length();

        float SqLength();

        float Angle(Vector2 &_vector);

        float Dot(Vector2 &_vector);

        Vector2 Lerp(Vector2 &_from, Vector2 &_to, float _factor);

        // Unary operators
        Vector2 operator-();

        // Binary math operators
        Vector2 operator+(Vector2 &_vector);

        Vector2 operator-(Vector2 &_vector);

        Vector2 operator*(float _val);

        Vector2 operator/(float _val);

        float operator^(Vector2 &_vector);


        // Binary assignement math operators
        void operator+=(Vector2 &_vector);

        void operator-=(Vector2 &_vector);

        void operator*=(float _val);

        void operator/=(float _val);


        float x = 0.f;
        float y = 0.f;
    };
} // namespace DadEngine

#endif //__VECTOR2_HPP_

