#ifndef __VECTOR4_HPP_
#define __VECTOR4_HPP_

namespace DadEngine
{
    class Vector4
    {

        public:
        Vector4() = default;

        Vector4(float _x, float _y, float _z, float _w);


        // Standard vector functions
        void Normalize();

        float Length() const;

        float SqLength() const;

        float Angle(Vector4 &_vector) const;

        float Dot(Vector4 &_vector) const;

        static Vector4 Lerp(Vector4 &_from, Vector4 &_to, float _factor);

        // Unary operators
        Vector4 operator-() const;

        // Binary math operators
        Vector4 operator+(Vector4 &_vector) const;

        Vector4 operator-(Vector4 &_vector) const;

        Vector4 operator*(float _val) const;

        Vector4 operator/(float _val) const;

        Vector4 operator^(Vector4 &_vector) const;


        // Binary assignement math operators
        void operator+=(Vector4 &_vector);

        void operator-=(Vector4 &_vector);

        void operator*=(float _val);

        void operator/=(float _val);

        void operator^=(Vector4 &_vector);


        float x = 0.f;
        float y = 0.f;
        float z = 0.f;
        float w = 0.f;
    };
} // namespace DadEngine

#endif //__VECTOR4_HPP_
