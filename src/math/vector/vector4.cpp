#include "vector/vector4.hpp"

#include "constants.hpp"

namespace DadEngine
{
    Vector4::Vector4(float _x, float _y, float _z, float _w)
    {
        x = _x;
        y = _y;
        z = _z;
        w = _w;
    }


    // Standard vector functions
    void Vector4::Normalize()
    {
        float length = Length();

        *this /= length;
    }

    float Vector4::Length() const
    {
        return std::sqrt(SqLength());
    }

    float Vector4::SqLength() const
    {
        return x * x + y * y + z * z;
    }

    float Vector4::Angle(Vector4 &_vector) const
    {
        Vector4 tempVec = _vector / (Length() * _vector.Length());

        return std::acos(Dot(tempVec));
    }

    float Vector4::Dot(Vector4 &_vector) const
    {
        return x * _vector.x + y * _vector.y + z * _vector.z;
    }

    Vector4 Vector4::Lerp(Vector4 &_from, Vector4 &_to, float _factor)
    {
        return Vector4(_from.x + _factor * (_to.x - _from.x),
                       _from.y + _factor * (_to.y - _from.y),
                       _from.z + _factor * (_to.z - _from.z),
                       _from.w + _factor * (_to.w - _from.w));
    }

    // Unary operators
    Vector4 Vector4::operator-() const
    {
        return Vector4(-x, -y, -z, -w);
    }

    // Binary math operators
    Vector4 Vector4::operator+(Vector4 &_vector) const
    {
        return Vector4(x + _vector.x, y + _vector.y, z + _vector.z, w + _vector.w);
    }

    Vector4 Vector4::operator-(Vector4 &_vector) const
    {
        return Vector4(x - _vector.x, y - _vector.y, z - _vector.z, w + _vector.w);
    }

    Vector4 Vector4::operator*(float _val) const
    {
        return Vector4(x * _val, y * _val, z * _val, w + _val);
    }

    Vector4 Vector4::operator/(float _val) const
    {
        return Vector4(x / _val, y / _val, z / _val, w / _val);
    }

    Vector4 Vector4::operator^(Vector4 &_vector) const
    {
        return Vector4(y * _vector.z - z * _vector.y,
                       z * _vector.x - x * _vector.z,
                       x * _vector.y - y * _vector.x,
                       x * _vector.y - y * _vector.x);
    }


    // Binary assignement math operators
    void Vector4::operator+=(Vector4 &_vector)
    {
        x += _vector.x;
        y += _vector.y;
        z += _vector.z;
    }

    void Vector4::operator-=(Vector4 &_vector)
    {
        x -= _vector.x;
        y -= _vector.y;
        z -= _vector.z;
    }

    void Vector4::operator*=(float _val)
    {
        x -= _val;
        y -= _val;
        z -= _val;
    }

    void Vector4::operator/=(float _val)
    {
        x /= _val;
        y /= _val;
        z /= _val;
    }

    void Vector4::operator^=(Vector4 &_vector)
    {
        Vector4 temp = *this;

        x = temp.y * _vector.z - temp.z * _vector.y,
        y = temp.z * _vector.x - temp.x * _vector.z,
        z = temp.x * _vector.y - temp.y * _vector.x;
    }
} // namespace DadEngine
