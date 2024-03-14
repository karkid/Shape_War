#pragma once
#include <iostream>

class Vector2
{
public:
    double x = 0.0f;
    double y = 0.0f;

    Vector2() {}

    Vector2(double _x, double _y): x(_x), y(_y)
    {
    }

    bool operator ==(const Vector2& rhs) const;
    bool operator !=(const Vector2& rhs) const;

    Vector2 operator +(const Vector2& rhs) const;
    Vector2 operator -(const Vector2& rhs) const;
    Vector2 operator *(const Vector2& rhs) const;
    Vector2 operator /(const Vector2& rhs) const;

    void operator +=(const Vector2& rhs);
    void operator -=(const Vector2& rhs);
    void operator *=(const Vector2& rhs);
    void operator /=(const Vector2& rhs);

    void operator *(const double n);
    void operator /(const double n);

    friend inline std::ostream& operator<<(std::ostream& os, const Vector2& v);

    double dot_product(const Vector2& rhs) const;
    double cross_product(const Vector2& rhs) const;
    void normalize();
    double length() const;
};

inline std::ostream& operator<<(std::ostream& os, const Vector2& v)
{
    os << '(' << v.x << ',' << v.y << ')';
    return os;
}