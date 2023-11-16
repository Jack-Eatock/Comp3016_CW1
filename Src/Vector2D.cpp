#include "../Headers/Vector2D.h"

/// <summary>
/// Provides a usefull interface for handling two dimensional vectors.
/// Perfect for moving objects in a two dimensional world.
/// </summary>

Vector2D::Vector2D() 
{
	X = 0.0f;
	Y = 0.0f;
}

Vector2D::Vector2D(float x, float y)
{
	X = x;
	Y = y;
}

// Add a vector2d to this vector2d
Vector2D& Vector2D::Add(const Vector2D& vec)
{
	X += vec.X;
	Y += vec.Y;
	return *this; // Returns self
}

// Subtract a vector2d to this vector2d
Vector2D& Vector2D::Subtract(const Vector2D& vec)
{
	X -= vec.X;
	Y -= vec.Y;
	return *this; // Returns self
}

// Multiply a vector2d to this vector2d
Vector2D& Vector2D::Multiply(const Vector2D& vec)
{
	X *= vec.X;
	Y *= vec.Y;
	return *this; // Returns self
}

// Divide a vector2d to this vector2d
Vector2D& Vector2D::Divide(const Vector2D& vec)
{
	X /= vec.X;
	Y /= vec.Y;
	return *this; // Returns self
}

/// <summary>
/// Returns a normalised version of this vector.
/// </summary>
/// <returns></returns>
Vector2D& Vector2D::Normalise()
{
	Vector2D* tmp = new Vector2D(X, Y);
	float length = sqrt((X * X) + (Y * Y));
	if (length != 0) {
		tmp->X = X / length;
		tmp->Y = Y / length;
	}
	return *tmp;
}

Vector2D& operator+(Vector2D& v1, const Vector2D v2)
{
	return v1.Add(v2);
}

Vector2D& operator-(Vector2D& v1, const Vector2D v2)
{
	return v1.Subtract(v2);
}

Vector2D& operator*(Vector2D& v1, const Vector2D v2)
{
	return v1.Multiply(v2);
}

Vector2D& operator/(Vector2D& v1, const Vector2D v2)
{
	return v1.Divide(v2);
}

Vector2D& Vector2D::operator+=(const Vector2D& vec) 
{
	return this->Add(vec);
}

Vector2D& Vector2D::operator-=(const Vector2D& vec)
{
	return this->Subtract(vec);
}

Vector2D& Vector2D::operator*= (const Vector2D & vec)
{
	return this->Multiply(vec);
}

Vector2D& Vector2D::operator/=(const Vector2D& vec)
{
	return this->Divide(vec);
}

std::ostream& operator<<(std::ostream& stream, const Vector2D& vec)
{
	stream << "(" << vec.X << "," << vec.Y << ")";
	return stream;
}