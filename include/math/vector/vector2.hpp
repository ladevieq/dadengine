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

        float Length() const;

        float SqLength() const;

        float Angle(Vector2 &_vector) const;

        float Dot(Vector2 &_vector) const;

        static Vector2 Lerp(Vector2 &_from, Vector2 &_to, float _factor);

        // Unary operators
        Vector2 operator-() const;

        // Binary math operators
        Vector2 operator+(Vector2 &_vector) const;

        Vector2 operator-(Vector2 &_vector) const;

        Vector2 operator*(float _val) const;

        Vector2 operator/(float _val) const;

        float operator^(Vector2 &_vector) const;


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
