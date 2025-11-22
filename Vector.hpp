#pragma once

#include "Common.hpp"

template <class Type>
class Vector2
{
public:
    Type x;
    Type y;

    Vector2() : x(Type()), y(Type())
    {
    }

    Vector2(Type x, Type y) : x(x), y(y)
    {
    }

    Vector2 operator+(const Vector2& v) const
    {
        return Vector2<Type>(x + v.x, y + v.y);
    }

    Vector2 operator-(const Vector2& v) const
    {
        return Vector2<Type>(x - v.x, y - v.y);
    }

    Vector2 operator*(const Vector2& v) const
    {
        return Vector2<Type>(x * v.x, y * v.y);
    }

    Vector2 operator/(const Type& scalar)
    {
        return Vector2<Type>(x / scalar, y / scalar);
    }

    void makeAbsolute()
    {
        x = ::abs(x);
        y = ::abs(y);
    }
};

template <class Type>
class Vector
{
public:
    Type x;
    Type y;
    Type z;

    Vector() : x(Type()), y(Type()), z(Type())
    {
    }

    Vector(Type x, Type y, Type z) : x(x), y(y), z(z)
    {
    }

    Vector operator+(const Vector& v) const
    {
        return Vector<Type>(x + v.x, y + v.y, z + v.z);
    }

    Vector operator-(const Vector& v) const
    {
        return Vector<Type>(x - v.x, y - v.y, z - v.z);
    }

    Vector operator*(const Vector& v) const
    {
        return Vector<Type>(x * v.x, y * v.y, z * v.z);
    }

    Vector operator/(const Type& scalar)
    {
        return Vector<Type>(x / scalar, y / scalar, z / scalar);
    }

    void makeAbsolute()
    {
        x = ::abs(x);
        y = ::abs(y);
        z = ::abs(z);
    }
};
