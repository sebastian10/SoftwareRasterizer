#pragma once

#include "../TestRunner.h"
#include "Matrix.h"
#include "Vector.h"

namespace Testing::Tests::Matrix_test
{
	void Constructor_Test()
	{
		Mat<2, float> mat2;
		CHECK( mat2.mat.size() == 4);

		Mat<3> mat3 = {
			0,1,2,
			3,4,5,
			6,7,8
		};

		for ( int i = 0; i < 9; ++i )
		{
			CHECK( mat3.mat[i] == i );
		}

		Mat<2> id = Mat<2>::Identity();
		CHECK( id( 0, 0 ) == 1 && id( 0, 0 ) == 1 );
	}

	void Matrix_Scalar_Multiplication_Test()
	{
		Mat<3, int> A = {
			1,2,3,
			4,5,6,
			7,8,9
		};

		Mat<3, int> result = {
			2,4,6,
			8,10,12,
			14,16,18
		};

		CHECK( A * 2 == result );
	}

	void Matrix_Multiplication_Test()
	{
		Mat<3, int> A = {
			1,2,3,
			4,5,6,
			7,8,9
		};

		Mat<3, int> B = {
			9,8,7,
			6,5,4,
			3,2,1
		};

		Mat<3, int> result = {
			30,24,18,
			84,69,54,
			138,114,90
		};

		CHECK( A * B == result );
	}

	void Matrix_Vector_Multiplication_Test()
	{
		Mat<3, int> A = {
			1,2,3,
			4,5,6,
			7,8,9
		};

		Vec<3, int> v( 1, 2, 3 );

		Vec<3, int> result( 14, 32, 50 );

		CHECK( A * v == result );
	}

	void Matrix_Transposition_Test()
	{
		Mat<3, int> A = {
			1,2,3,
			4,5,6,
			7,8,9
		};

		Mat<3, int> At = {
			1,4,7,
			2,5,8,
			3,6,9
		};

		CHECK( A.Transposed() == At );
		CHECK( A.Transposed().Transposed() == A );
	}

	void Matrix_Determinant_Test()
	{
		Mat<2, int> A = {
			1,2,
			3,4
		};

		CHECK( A.Determinant() == -2 );

		Mat<3, int> B = {
			1,2,3,
			4,5,6,
			7,8,9
		};

		CHECK( B.Determinant() == 0 );
	}

	void Matrix_Inverse_Test()
	{
		Mat<2> A = {
			1.0f, 2.0f,
			3.0f, 4.0f
		};

		Mat<2> Ainv = {
			-2.0f, 1.0f,
			3.0f/2.0f, -1.0f/2.0f
		};

		CHECK( A.Inversed() == Ainv );
		CHECK( A.Inversed() * A == Mat<2>::Identity() );

		Mat<3> B = {
			1.0f, 2.0f, 3.0f,
			0.0f, 1.0f, 4.0f,
			5.0f, 6.0f, 0.0f
		};

		Mat<3> Binv = {
			-24.0f, 18.0f, 5.0f,
			20.0f, -15.0f, -4.0f,
			-5.0f, 4.0f, 1.0f
		};

		CHECK( B.Inversed( B.Determinant() ) == Binv );
		CHECK( B.Inversed( B.Determinant() ) * B == Mat<3>::Identity() );
	}
}