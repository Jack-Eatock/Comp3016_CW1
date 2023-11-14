#pragma once
#include <iostream>


class Vector2D 
{
public:
	float X;
	float Y;

	Vector2D();
	Vector2D(float x, float y);
	
	Vector2D& Add(const Vector2D& vec); // Add a vector2d to this vector2d
	Vector2D& Subtract(const Vector2D& vec); // Subtract a vector2d to this vector2d
	Vector2D& Multiply(const Vector2D& vec); // Multiply a vector2d to this vector2d
	Vector2D& Divide(const Vector2D& vec); // Divide a vector2d to this vector2d
	Vector2D& Normalise(); // Normalise the vector2D

	friend Vector2D& operator+(Vector2D& v1, const Vector2D v2);
	friend Vector2D& operator-(Vector2D& v1, const Vector2D v2);
	friend Vector2D& operator*(Vector2D& v1, const Vector2D v2);
	friend Vector2D& operator/(Vector2D& v1, const Vector2D v2);

	Vector2D& operator+=(const Vector2D& vec);
	Vector2D& operator-=(const Vector2D& vec);
	Vector2D& operator*=(const Vector2D& vec);
	Vector2D& operator/=(const Vector2D& vec);

	// Alow debugging in console.
	friend std::ostream& operator<<(std::ostream& stream, const Vector2D& vec);
};