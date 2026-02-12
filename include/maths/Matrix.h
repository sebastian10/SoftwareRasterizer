#pragma once

#include <array>
#include "maths/maths.h"

template<int N, typename T = float>
class Mat
{
public:
	// row column
	std::array<T, N * N> mat{};
private:
public:
	T& operator()( int row, int col )
	{
		return mat[row * N + col];
	}

	const T& operator()( int row, int col ) const
	{
		return mat[row * N + col];
	}

	bool operator==( const Mat& other ) const
	{
		if ( mat.size() != other.mat.size() )
			return false;

		for ( int i = 0; i < mat.size(); i++ )
		{
			if ( mat[i] != other.mat[i] )
				return false;
		}

		return true;
	}

	static Mat Identity()
	{
		Mat m;
		for ( int i = 0; i < N; ++i )
		{
			m( i, i ) = T( 1 );
		}
		return m;
	}

	Mat operator*( const T scalar ) const
	{
		Mat result;

		for ( int i = 0; i < mat.size(); i++ )
		{
			result.mat[i] = mat[i] * scalar;
		}

		return result;
	}

	Mat operator*( const Mat& rhs ) const
	{
		Mat result;

		for ( int row = 0; row < N; ++row )
		{
			for ( int column = 0; column < N; ++column )
			{
				result( row, column ) = T(0);
				for ( int i = 0; i < N; ++i )
				{
					result( row, column ) += ( *this )( row, i ) * rhs( i, column );
				}
			}
		}

		return result;
	}

	Vec<N, T> operator*( const Vec<N, T>& vec ) const
	{
		Vec<N, T> result;

		for ( int r = 0; r < N; ++r )
		{
			T sum = 0;
			for ( int c = 0; c < N; ++c )
				sum += vec[c] * ( *this )( r, c );

			result[r] = sum;
		}
		return result;
	}

	Mat<N, T> Transposed() const
	{
		Mat<N, T> result;

		for ( int r = 0; r < N; ++r )
		{
			for ( int c = 0; c < N; ++c )
			{
				result( r, c ) = ( *this )( c, r );
			}
		}
		
		return result;
	}

	// 2x2 determinant
	T Determinant() const requires( N == 2 )
	{
		// ad - bc
		return ( *this )( 0, 0 ) * ( *this )( 1, 1 ) - ( *this )( 0, 1 ) * ( *this )( 1, 0 );
	}

	static T Det2x2( T a, T b, T c, T d )
	{
		return a * d - b * c;
	}

	// 3x3 determinant
	T Determinant() const requires( N == 3 )
	{
		// a(ei?fh)?b(di?fg)+c(dh?eg)
		const T a = ( *this )( 0, 0 );
		const T b = ( *this )( 0, 1 );
		const T c = ( *this )( 0, 2 );

		const T d = ( *this )( 1, 0 );
		const T e = ( *this )( 1, 1 );
		const T f = ( *this )( 1, 2 );

		const T g = ( *this )( 2, 0 );
		const T h = ( *this )( 2, 1 );
		const T i = ( *this )( 2, 2 );

		return a * ( e * i - f * h ) - b * ( d * i - f * g ) + c * ( d * h - e * g );
	}

	//// return submatrix, by removing row and column
	//Mat<N-1, T> Submatrix( int row, int colum ) const
	//{
	//	Mat<N - 1, T> result;

	//	int i = 0;
	//	for ( int r = 0; r < N; ++r )
	//	{
	//		if ( r == row )
	//			continue;

	//		for ( int c = 0; c < N; ++c )
	//		{
	//			if ( c == column )
	//				continue;

	//			result.mat[i] = ( *this )( r, c );
	//			i++;
	//		}
	//	}

	//	return result;
	//}

	Mat<2, T> Inversed() const requires( N == 2 )
	{
		T det = Determinant();

		assert( std::abs( det ) > Rasterizer::Maths::epsilon );
		
		// adjugate matrix
		// a b =  d -b
		// c d   -c  a
		Mat<2, T> adj;

		adj( 0, 0 ) = ( *this )( 1, 1 );
		adj( 0, 1 ) = -( *this )( 0, 1 );
		adj( 1, 0 ) = -( *this )( 1, 0 );
		adj( 1, 1 ) = ( *this )( 0, 0 );

		return adj * ( (T)1 / det );
	}

	Mat<3, T> Inversed() const requires( N == 3 )
	{
		T det = Determinant();

		assert( std::abs( det ) > Rasterizer::Maths::epsilon );

		Mat<3, T> comatrix;

		//comatrix( 0, 0 ) = Mat<2, T>{ ( *this )( 1,1 ), ( *this )( 1,2 ), ( *this )( 2,1 ), ( *this )( 2,2 ) }.Determinant();
		//comatrix( 0, 1 ) = -(Mat<2, T>{ ( *this )( 1,0 ), ( *this )( 1,2 ), ( *this )( 2,0 ), ( *this )( 2,2 ) }.Determinant());
		//comatrix( 0, 2 ) = Mat<2, T>{ ( *this )( 1,0 ), ( *this )( 1,1 ), ( *this )( 2,0 ), ( *this )( 2,1 ) }.Determinant();

		//comatrix( 1, 0 ) = -(Mat<2, T>{ ( *this )( 0,1 ), ( *this )( 0,2 ), ( *this )( 2,1 ), ( *this )( 2,2 ) }.Determinant());
		//comatrix( 1, 1 ) = Mat<2, T>{ ( *this )( 0,0 ), ( *this )( 0,2 ), ( *this )( 2,0 ), ( *this )( 2,2 ) }.Determinant();
		//comatrix( 1, 2 ) = -(Mat<2, T>{ ( *this )( 0,0 ), ( *this )( 0,1 ), ( *this )( 2,0 ), ( *this )( 2,1 ) }.Determinant());

		//comatrix( 2, 0 ) = Mat<2, T>{ ( *this )( 0,1 ), ( *this )( 0,2 ), ( *this )( 1,1 ), ( *this )( 1,2 ) }.Determinant();
		//comatrix( 2, 1 ) = -(Mat<2, T>{ ( *this )( 0,0 ), ( *this )( 0,2 ), ( *this )( 1,0 ), ( *this )( 1,2 ) }.Determinant());
		//comatrix( 2, 2 ) = Mat<2, T>{ ( *this )( 0,0 ), ( *this )( 0,1 ), ( *this )( 1,0 ), ( *this )( 1,1 ) }.Determinant();

		comatrix( 0, 0 ) = Det2x2( ( *this )( 1, 1 ), ( *this )( 1, 2 ), ( *this )( 2, 1 ), ( *this )( 2, 2 ) );
		comatrix( 0, 1 ) = -( Det2x2( ( *this )( 1, 0 ), ( *this )( 1, 2 ), ( *this )( 2, 0 ), ( *this )( 2, 2 ) ) );
		comatrix( 0, 2 ) = Det2x2( ( *this )( 1, 0 ), ( *this )( 1, 1 ), ( *this )( 2, 0 ), ( *this )( 2, 1 ) );

		comatrix( 1, 0 ) = -( Det2x2( ( *this )( 0, 1 ), ( *this )( 0, 2 ), ( *this )( 2, 1 ), ( *this )( 2, 2 ) ) );
		comatrix( 1, 1 ) = Det2x2( ( *this )( 0, 0 ), ( *this )( 0, 2 ), ( *this )( 2, 0 ), ( *this )( 2, 2 ) );
		comatrix( 1, 2 ) = -( Det2x2( ( *this )( 0, 0 ), ( *this )( 0, 1 ), ( *this )( 2, 0 ), ( *this )( 2, 1 ) ) );

		comatrix( 2, 0 ) = Det2x2( ( *this )( 0, 1 ), ( *this )( 0, 2 ), ( *this )( 1, 1 ), ( *this )( 1, 2 ) );
		comatrix( 2, 1 ) = -( Det2x2( ( *this )( 0, 0 ), ( *this )( 0, 2 ), ( *this )( 1, 0 ), ( *this )( 1, 2 ) ) );
		comatrix( 2, 2 ) = Det2x2( ( *this )( 0, 0 ), ( *this )( 0, 1 ), ( *this )( 1, 0 ), ( *this )( 1, 1 ) );

		return comatrix.Transposed() * ( (T)1 / det );
	}
private:
};

using Mat3 = Mat<3, float>;