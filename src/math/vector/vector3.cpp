#include "vector/vector3.hpp"

#include "constants.hpp"

namespace DadEngine
{
    Vector3::Vector3(float _x, float _y, float _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }


    // Standard vector functions
    void Vector3::Normalize()
    {
        float length = Length();
        *this /= length;
    }

    float Vector3::Length() const
    {
        return std::sqrt(SqLength());
    }

    float Vector3::SqLength() const
    {
        return x * x + y * y + z * z;
    }

    float Vector3::Angle(Vector3 &_vector) const
    {
        Vector3 tempVec = _vector / (Length() * _vector.Length());

        return std::acos(Dot(tempVec));
    }

    float Vector3::Dot(Vector3 &_vector) const
    {
        return x * _vector.x + y * _vector.y + z * _vector.z;
    }

    Vector3 Vector3::Lerp(Vector3 &_from, Vector3 &_to, float _factor)
    {
        return Vector3(_from.x + _factor * (_to.x - _from.x),
                       _from.y + _factor * (_to.y - _from.y),
                       _from.z + _factor * (_to.z - _from.z));
    }

    // Unary operators
    Vector3 Vector3::operator-() const
    {
        return Vector3(-x, -y, -z);
    }

    // Binary math operators
    Vector3 Vector3::operator+(Vector3 &_vector) const
    {
        return Vector3(x + _vector.x, y + _vector.y, z + _vector.z);
    }

    Vector3 Vector3::operator-(Vector3 &_vector) const
    {
        return Vector3(x - _vector.x, y - _vector.y, z - _vector.z);
    }

    Vector3 Vector3::operator*(float _val) const
    {
        return Vector3(x * _val, y * _val, z * _val);
    }

    Vector3 Vector3::operator/(float _val) const
    {
        return Vector3(x / _val, y / _val, z / _val);
    }

    Vector3 Vector3::operator^(Vector3 &_vector) const
    {
        return Vector3(y * _vector.z - z * _vector.y,
                       z * _vector.x - x * _vector.z,
                       x * _vector.y - y * _vector.x);
    }


    // Binary assignement math operators
    void Vector3::operator+=(Vector3 &_vector)
    {
        x += _vector.x;
        y += _vector.y;
        z += _vector.z;
    }

    void Vector3::operator+=(const Vector3 &_vector)
    {
        x += _vector.x;
        y += _vector.y;
        z += _vector.z;
    }

    void Vector3::operator-=(Vector3 &_vector)
    {
        x -= _vector.x;
        y -= _vector.y;
        z -= _vector.z;
    }

    void Vector3::operator-=(const Vector3 &_vector)
    {
        x -= _vector.x;
        y -= _vector.y;
        z -= _vector.z;
    }

    void Vector3::operator*=(float _val)
    {
        x -= _val;
        y -= _val;
        z -= _val;
    }

    void Vector3::operator/=(float _val)
    {
        x /= _val;
        y /= _val;
        z /= _val;
    }

    void Vector3::operator^=(Vector3 &_vector)
    {
        Vector3 temp = *this;

        x = temp.y * _vector.z - temp.z * _vector.y,
        y = temp.z * _vector.x - temp.x * _vector.z,
        z = temp.x * _vector.y - temp.y * _vector.x;
    }
} // namespace DadEngine
