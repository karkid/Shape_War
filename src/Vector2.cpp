#include "Vector2.h"

#include <math.h>

bool Vector2::operator==(const Vector2 &rhs) const
{
    return x == rhs.x && y == rhs.y;
}

bool Vector2::operator!=(const Vector2 &rhs) const
{
    return x != rhs.x || y != rhs.y;
}

Vector2 Vector2::operator+(const Vector2 &rhs) const
{
    return Vector2(x + rhs.x, y + rhs.y);
}

Vector2 Vector2::operator-(const Vector2 &rhs) const
{
    return Vector2(x - rhs.x, y - rhs.y);
}

Vector2 Vector2::operator*(const Vector2 &rhs) const
{
    return Vector2(x * rhs.x, y * rhs.y);
}

Vector2 Vector2::operator/(const Vector2 &rhs) const
{
    return Vector2(x / rhs.x, y / rhs.y);
}

void Vector2::operator+=(const Vector2 &rhs)
{
    x += rhs.x;
    y += rhs.y;
}

void Vector2::operator-=(const Vector2 &rhs)
{
    x -= rhs.x;
    y -= rhs.y;
}

void Vector2::operator*=(const Vector2 &rhs)
{
    x *= rhs.x;
    y *= rhs.y;
}

void Vector2::operator/=(const Vector2 &rhs)
{
    x /= rhs.x;
    y /= rhs.y;
}

void Vector2::operator*(const double n)
{
    x *= n;
    y *= n;
}

void Vector2::operator/(const double n)
{
    x /= n;
    y /= n;
}

double Vector2::dot_product(const Vector2 &rhs) const
{
    return (x * rhs.x + y * rhs.y);
}

double Vector2::cross_product(const Vector2 &rhs) const
{
    return (x * rhs.y - y * rhs.x);
}

void Vector2::normalize()
{
    double len = this->length();
    x /= len;
    y /= len;
}

double Vector2::length() const
{
    return std::sqrt(x*x + y*y);
}

double Vector2::distance(const Vector2 &to) const
{
    return std::abs(std::sqrt((x - to.x) * (x - to.x) + (y - to.y) * (y - to.y)));
}
