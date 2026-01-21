#pragma once

#include <cmath>

template<typename T>
class Vector2_
{
public:
	T x;
	T y;
private:
public:
	Vector2_()
		: x( (T)0.0f ), y( (T)0.0f )
	{
	}
	Vector2_( T x, T y )
		: x( x ), y( y )
	{}
	Vector2_( const Vector2_<float>& other )
		: x( (T) other.x ), y( (T) other.y )
	{}
	bool operator==( const Vector2_& rhs ) const
	{
		return ( x == rhs.x && y == rhs.y );
	}
	Vector2_ operator+( const Vector2_& rhs ) const
	{
		return Vector2_( x + rhs.x, y + rhs.y );
	}
	Vector2_ operator+=( const Vector2_& rhs )
	{
		return *this = *this + rhs;
	}
	Vector2_ operator-() const
	{
		return Vector2_( -x, -y );
	}
	Vector2_ operator-( const Vector2_& rhs ) const
	{
		return Vector2_( x - rhs.x, y - rhs.y );
	}
	Vector2_ operator-=( const Vector2_& rhs )
	{
		return *this = *this - rhs;
	}
	Vector2_ operator*( const T rhs ) const
	{
		return Vector2_( x * rhs, y * rhs );
	}
	Vector2_ operator*=( const T rhs )
	{
		return *this = *this * rhs;
	}
	Vector2_ operator/( T rhs ) const
	{
		return Vector2_( x / rhs, y / rhs );
	}
	Vector2_ operator/=( const T rhs )
	{
		return *this = *this / rhs;
	}
	T GetLengthSq() const
	{
		return x * x + y * y;
	}
	T GetLength() const
	{
		return (T)std::sqrt( GetLengthSq() );
	}
	Vector2_ GetNormalised() const
	{
		const T length = GetLength();
		if ( length != (T)0 )
		{
			return *this / length;
		}
		return *this;
	}
	Vector2_& Normalise() 
	{
		return *this = GetNormalised();
	}
private:
};

typedef Vector2_<float> Vector2;
typedef Vector2_<int> Vector2Int;