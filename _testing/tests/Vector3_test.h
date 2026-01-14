#pragma once

#include "../TestRunner.h"
#include "Vector3.h"

namespace Testing::Tests::Vector3_test
{
	void Constructor_test()
	{
		Vector3 v1;
		CHECK( v1.x == 0.0f && v1.y == 0.0f && v1.z == 0.0f );

		Vector3 v2( 3.0f, 12.0f, 5.0f );
		CHECK( v2.x == 3.0f && v2.y == 12.0f && v2.z == 5.0f );
	}

	void Addition_Test()
	{
		Vector3 v1( 3.0f, 3.0f, 3.0f ), v2( 1.0f, 1.0f, 1.0f );
		Vector3 result = v1 + v2;
		CHECK( TestRunner::NearlyEqual( 4.0f, result.x ) );
		CHECK( TestRunner::NearlyEqual( 4.0f, result.y ) );
		CHECK( TestRunner::NearlyEqual( 4.0f, result.z ) );
	}

	void Subtraction_Test()
	{
		Vector3 v1( 3.0f, 3.0f, 3.0f ), v2( 1.0f, 1.0f, 1.0f );
		Vector3 result = v1 - v2;
		CHECK( TestRunner::NearlyEqual( 2.0f, result.x ) );
		CHECK( TestRunner::NearlyEqual( 2.0f, result.y ) );
		CHECK( TestRunner::NearlyEqual( 2.0f, result.z ) );
	}

	void ScalarMultiplication_Test()
	{
		Vector3 v1( 3.0f, 3.0f, 3.0f );
		float scalar = 4.0f;
		Vector3 result = v1 * scalar;
		CHECK( TestRunner::NearlyEqual( 12.0f, result.x ) );
		CHECK( TestRunner::NearlyEqual( 12.0f, result.y ) );
		CHECK( TestRunner::NearlyEqual( 12.0f, result.z ) );
	}

	void Length_Test()
	{
		Vector3 v1( 1.0f, 2.0f, 3.0f );
		CHECK( TestRunner::NearlyEqual( 14.0f, v1.GetLengthSq() ) );
		CHECK( TestRunner::NearlyEqual( std::sqrt( 14.0f ), v1.GetLength() ) );
	}

	void Normalisation_Test()
	{
		Vector3 v1( 3.0f, 4.0f, 5.0f );
		Vector3 result = v1.GetNormalised();
		CHECK( TestRunner::NearlyEqual( result.GetLength(), 1.0f ) );
	}
}