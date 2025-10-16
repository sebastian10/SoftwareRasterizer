#pragma once

#include <cmath>

template<typename T>
class Vector2
{
public:
	T x;
	T y;
private:
public:
	Vector2() 
		: x( 0 ), y( 0 ) 
	{}
	Vector2( T x, T y )
		: x( x ), y( y )
	{}
	Vector2 operator+( const Vector2& rhs ) const
	{
		return Vector2( x + rhs.x, y + rhs.y );
	}
	Vector2 operator+=( const Vector2& rhs )
	{
		return *this = *this + rhs;
	}
	Vector2 operator-( const Vector2& rhs ) const
	{
		return Vector2( x - rhs.x, y - rhs.y );
	}
	Vector2 operator-=( const Vector2& rhs )
	{
		return *this = *this - rhs;
	}
	Vector2 operator*( const T rhs ) const
	{
		return Vector2( x * rhs, y * rhs );
	}
	Vector2 operator*=( const T rhs )
	{
		return *this = *this * rhs;
	}
	Vector2 operator/( const T rhs ) const
	{
		return Vector2( x / rhs, y / rhs );
	}
	Vector2 operator/=( const T rhs )
	{
		return *this = *this / rhs;
	}
	T GetLengthSq() const
	{
		return x * x + y * y;
	}
	T GetLength()
	{
		return (T)std::sqrt( GetLengthSq() );
	}
	Vector2 GetNormalised() const
	{
		const T length = GetLength();
		if ( length != (T)0 )
		{
			return *this / length;
		}
		return *this;
	}
	Vector2& Normalise() 
	{
		return *this = GetNormalised();
	}
private:
};

typedef Vector2<float> Vector2;