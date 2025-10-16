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
		: x( 0 ), y( 0 ) 
	{}
	Vector2_( T x, T y )
		: x( x ), y( y )
	{}
	Vector2_ operator+( const Vector2_& rhs ) const
	{
		return Vector2_( x + rhs.x, y + rhs.y );
	}
	Vector2_ operator+=( const Vector2_& rhs )
	{
		return *this = *this + rhs;
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
	Vector2_ operator/( const T rhs ) const
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
	T GetLength()
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