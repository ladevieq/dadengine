#ifndef __VECTOR3_HPP_
#define __VECTOR3_HPP_


namespace DadEngine
{
    class Vector3
    {

        public:
        Vector3() = default;

        Vector3(float _x, float _y, float _z);


        // Standard vector functions
        void Normalize();

        float Length();

        float SqLength();

        float Angle(Vector3 &_vector);

        float Dot(Vector3 &_vector);

        Vector3 Lerp(Vector3 &_from, Vector3 &_to, float _factor);

        // Unary operators
        Vector3 operator-();

        // Binary math operators
        Vector3 operator+(Vector3 &_vector);

        Vector3 operator-(Vector3 &_vector);

        Vector3 operator*(float _val);

        Vector3 operator/(float _val);

        Vector3 operator^(Vector3 &_vector);


        // Binary assignement math operators
        void operator+=(Vector3 &_vector);

        void operator+=(const Vector3 &_vector);

        void operator-=(Vector3 &_vector);

        void operator-=(const Vector3 &_vector);

        void operator*=(float _val);

        void operator/=(float _val);

        void operator^=(Vector3 &_vector);

        static inline Vector3 Zero()
        {
            return Vector3(0.f, 0.f, 0.f);
        }

        static inline Vector3 One()
        {
            return Vector3(1.f, 1.f, 1.f);
        }


        float x = 0.f;
        float y = 0.f;
        float z = 0.f;
    };
} // namespace DadEngine

#endif //__VECTOR3_HPP_
