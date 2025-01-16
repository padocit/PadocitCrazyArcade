#include "PreCompiledHeader.h"
#include "Vec2.h"

Vec2::Vec2(int x, int y)
    : x(x), y(y)
{
}

bool Vec2::operator==(const Vec2& other)
{
    return this->x == other.x && this->y == other.y;
}

bool Vec2::operator!=(const Vec2& other)
{
    return !(*this == other);
}

Vec2 Vec2::operator+(const Vec2& other)
{
    return Vec2(x + other.x, y + other.y);
}

Vec2 Vec2::operator-(const Vec2& other)
{
    return Vec2(x - other.x, y - other.y);
}

Vec2 Vec2::operator*(const Vec2& other)
{
    return Vec2(x * other.x, y * other.y);
}

Vec2 Vec2::operator/(const Vec2& other)
{
    return Vec2(x / other.x, y / other.y);
}

Vec2& Vec2::operator+=(const Vec2& other)
{
    this->x += other.x;
    this->y += other.y;
    return *this;
}

Vec2& Vec2::operator-=(const Vec2& other)
{
    this->x -= other.x;
    this->y -= other.y;
    return *this;
}

Vec2& Vec2::operator*=(const Vec2& other)
{
    this->x *= other.x;
    this->y *= other.y;
    return *this;
}

Vec2& Vec2::operator/=(const Vec2& other)
{
    this->x /= other.x;
    this->y /= other.y;
    return *this;
}
