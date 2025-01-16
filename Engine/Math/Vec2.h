#pragma once

#include "PreCompiledHeader.h"
#include "Core.h"

// integer (console)
class ENGINE_API Vec2
{
public:
	Vec2(int x = 0, int y = 0);
	~Vec2() = default;

	bool operator==(const Vec2& other);
	bool operator!=(const Vec2& other);

	Vec2 operator+(const Vec2& other);
	Vec2 operator-(const Vec2& other);
	Vec2 operator*(const Vec2& other);
	Vec2 operator/(const Vec2& other);

	Vec2& operator+=(const Vec2& other);
	Vec2& operator-=(const Vec2& other);
	Vec2& operator*=(const Vec2& other);
	Vec2& operator/=(const Vec2& other);


public:
	int x = 0;
	int y = 0;
};