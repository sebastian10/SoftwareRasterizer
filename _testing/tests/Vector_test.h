#pragma once

#include "../TestRunner.h"
#include "Vector.h"

#include <algorithm>

namespace Testing::Tests::Vector_test
{
	void Constructor_Test()
	{
		Vec<2, int> v1;
		CHECK( v1.x() == 0 && v1.y() == 0 );

		Vec<3> v2( 3.0f, 2.0f, 1.0f );
		CHECK( v2.x() == 3.0f && v2.y() == 2.0f && v2.z() == 1.0f);

		Vec<2, int> v3( v1 );
	}

	void Comparison_Test()
	{
		Vec<3> v1( 3.0f, 3.0f, 3.0f ), v2( 1.0f, 1.0f, 1.0f ), v3( 3.0f, 3.0f, 3.0f );

		CHECK( !( v1 == v2 ) );
		CHECK( v1 != v2 );
		CHECK( v1 == v3 );
	}

	void Addition_Test()
	{
		Vec<3> v1( 3.0f, 3.0f, 3.0f ), v2( 1.0f, 1.0f, 1.0f );
		Vec<3> result = v1 + v2;
		CHECK( TestRunner::NearlyEqual( 4.0f, result.x() ) );
		CHECK( TestRunner::NearlyEqual( 4.0f, result.y() ) );
		CHECK( TestRunner::NearlyEqual( 4.0f, result.z() ) );
	}

	void Subtraction_Test()
	{
		Vec<3> v1( 3.0f, 3.0f, 3.0f ), v2( 1.0f, 1.0f, 1.0f );
		Vec<3> result = v1 - v2;
		CHECK( TestRunner::NearlyEqual( 2.0f, result.x() ) );
		CHECK( TestRunner::NearlyEqual( 2.0f, result.y() ) );
		CHECK( TestRunner::NearlyEqual( 2.0f, result.z() ) );
		CHECK( -v1 == Vec<3>( -3.0f, -3.0f, -3.0f ) );
	}

	void ScalarMultiplication_Test()
	{
		Vec<3> v1( 3.0f, 3.0f, 3.0f );
		float scalar = 4.0f;
		Vec<3> result = v1 * scalar;
		CHECK( TestRunner::NearlyEqual( 12.0f, result.x() ) );
		CHECK( TestRunner::NearlyEqual( 12.0f, result.y() ) );
		CHECK( TestRunner::NearlyEqual( 12.0f, result.z() ) );
	}

	void Length_Test()
	{
		Vec<3> v1( 1.0f, 2.0f, 3.0f );
		CHECK( TestRunner::NearlyEqual( 14.0f, v1.GetLengthSq() ) );
		CHECK( TestRunner::NearlyEqual( std::sqrt( 14.0f ), v1.GetLength() ) );
	}

	void Normalisation_Test()
	{
		Vec<3> v1( 3.0f, 4.0f, 5.0f );
		Vec<3> result = v1.GetNormalised();
		CHECK( TestRunner::NearlyEqual( result.GetLength(), 1.0f ) );
	}

	void DotProduct_Test()
	{
		Vec<3> v1( 1.0f, 2.0f, 3.0f );
		Vec<3> v2( 4.0f, 5.0f, 6.0f );

		CHECK( v1.Dot(v2) == 32 );
	}

	void CrossProduct_Test()
	{
		Vec<3> v1( 4.0f, 0.0f, 0.0f );
		Vec<3> v2( 2.0f, 0.0f, 0.0f );
		Vec<3> product1 = v1.Cross( v2 );

		CHECK( product1.x() == 0 && product1.y() == 0 && product1.z() == 0);

		Vec<3> v3( 3.0f, 0.0f, 0.0f );
		Vec<3> v4( 0.0f, 5.0f, 0.0f );
		Vec<3> product2 = v3.Cross( v4 );

		CHECK( product2.x() == 0 && product2.y() == 0 && product2.z() == 15);
		CHECK( v3.Cross( v4 ) == -v4.Cross( v3 ) );

	}
}
