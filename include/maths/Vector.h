#pragma once

#include <cmath>
#include <array>
#include <algorithm>
#include <assert.h>

template<int N, typename T = float>
class Vec
{
public:
	std::array<T, N> vec{};
private:
public:
	Vec()
		:
		vec(0)
	{
	}

	template<typename... Args> 
	requires(sizeof...(Args) == N )
	explicit Vec( Args... args )
		:
		vec{ static_cast<T>( args )... }
	{
	}

	Vec( T value )
	{
		vec.fill( value );
	}

	template<typename U>
	explicit Vec( const Vec<N, U>& other )
	{
		for ( int i = 0; i < N; i++ )
		{
			vec[i] = static_cast<T>( other[i] );
		}
	}

	T& x() requires( N >= 1 ) { return vec[0]; }
	T& y() requires( N >= 2 ) { return vec[1]; }
	T& z() requires( N >= 3 ) { return vec[2]; }
	T& w() requires( N >= 4 ) { return vec[3]; }

	const T& x() const requires( N >= 1 ) { return vec[0]; }
	const T& y() const requires( N >= 2 ) { return vec[1]; }
	const T& z() const requires( N >= 3 ) { return vec[2]; }
	const T& w() const requires( N >= 4 ) { return vec[3]; }

	T& operator[]( int i ) { return vec[i]; }
	const T& operator[]( int i ) const { return vec[i]; }

	bool operator==( const Vec& rhs ) const
	{
		for ( int i = 0; i < N; ++i )
		{
			if ( vec[i] != rhs[i] )
				return false;
		}

		return true;
	}

	bool operator!=( const Vec& rhs ) const
	{
		return !( *this == rhs );
	}

	Vec operator+( const Vec& rhs ) const
	{
		Vec result;
		for ( int i = 0; i < N; ++i )
		{
			result[i] = vec[i] + rhs.vec[i];
		}

		return result;
	}

	Vec operator+=( const Vec& rhs )
	{
		return *this = *this + rhs;
	}

	Vec operator-( const Vec& rhs ) const
	{
		Vec result;
		for ( int i = 0; i < N; ++i )
		{
			result[i] = vec[i] - rhs.vec[i];
		}

		return result;
	}

	Vec operator-=( const Vec& rhs )
	{
		return *this = *this - rhs;
	}

	Vec operator*( const T scalar ) const
	{
		Vec result;
		for ( int i = 0; i < N; ++i )
		{
			result[i] = vec[i] * scalar;
		}

		return result;
	}

	Vec operator*=( const T rhs )
	{
		return *this = *this * rhs;
	}

	Vec operator-() const
	{
		Vec v(*this);
		return v * -1;
	}

	Vec operator/( T scalar ) const
	{
		Vec result;
		for ( int i = 0; i < N; ++i )
		{
			result[i] = vec[i] / scalar;
		}

		return result;
	}

	Vec operator/=( const T rhs )
	{
		return *this = *this / rhs;
	}

	T GetLengthSq() const
	{
		T sum = 0;
		for ( T value : vec )
		{
			sum += value * value;
		}

		return sum;
	}

	T GetLength() const
	{
		return (T) std::sqrt( GetLengthSq() );
	}

	Vec GetNormalised() const
	{
		const T length = GetLength();
		if ( length != (T) 0 )
		{
			return *this / length;
		}
		return *this;
	}

	Vec& Normalise()
	{
		return *this = GetNormalised();
	}

	float Dot( const Vec& rhs ) const
	{
		assert( vec.size() == rhs.vec.size() );

		float sum = 0;
		for ( int i = 0; i < N; ++i )
		{
			sum += (*this)[i] * rhs[i];
		}

		return sum;
	}

	Vec Cross( const Vec& rhs ) const requires ( N == 3 )
	{
		return Vec(
			y() * rhs.z() - z() * rhs.y(),
			z() * rhs.x() - x() * rhs.z(),
			x() * rhs.y() - y() * rhs.x()
		);
	}
private:
};

using Vec2 = Vec<2, float>;
using Vei2 = Vec<2, int>;
using Vec3 = Vec<3, float>;
using Vei3 = Vec<3, int>;