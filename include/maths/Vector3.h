#pragma once

#include <cmath>

template<typename T>
class Vector3_
{
public:
	T x;
	T y;
	T z;
private:
public:
	Vector3_()
		: x( 0.0f ), y( 0.0f ), z( 0.0f )
	{
	}
	Vector3_( T x, T y, T z )
		: x( x ), y( y ), z( z )
	{
	}
	Vector3_( const Vector3_<float>& other )
		: 
		x( (T) other.x ), 
		y( (T) other.y ),
		z( (T) other.z )
	{
	}
	Vector3_ operator+( const Vector3_& rhs ) const
	{
		return Vector3_( x + rhs.x, y + rhs.y, z + rhs.z );
	}
	Vector3_ operator+=( const Vector3_& rhs )
	{
		return *this = *this + rhs;
	}
	Vector3_ operator-( const Vector3_& rhs ) const
	{
		return Vector3_( x - rhs.x, y - rhs.y, z - rhs.z );
	}
	Vector3_ operator-=( const Vector3_& rhs )
	{
		return *this = *this - rhs;
	}
	Vector3_ operator*( const T rhs ) const
	{
		return Vector3_( x * rhs, y * rhs, z * rhs );
	}
	Vector3_ operator*=( const T rhs )
	{
		return *this = *this * rhs;
	}
	Vector3_ operator/( T rhs ) const
	{
		return Vector3_( x / rhs, y / rhs, z / rhs );
	}
	Vector3_ operator/=( const T rhs )
	{
		return *this = *this / rhs;
	}
	T GetLengthSq() const
	{
		return x * x + y * y + z * z;
	}
	T GetLength() const
	{
		return (T) std::sqrt( GetLengthSq() );
	}
	Vector3_ GetNormalised() const
	{
		const T length = GetLength();
		if ( length != (T) 0 )
		{
			return *this / length;
		}
		return *this;
	}
	Vector3_& Normalise()
	{
		return *this = GetNormalised();
	}
private:
};

typedef Vector3_<float> Vector3;
typedef Vector3_<int> Vector3Int;