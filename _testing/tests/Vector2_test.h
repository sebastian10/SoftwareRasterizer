#pragma once

#include "../TestRunner.h"
#include "Vector2.h"

namespace Testing::Tests::Vector2_test
{
	void Constructor_test()
	{
		Vector2 v1;
		CHECK( v1.x == 0.0f && v1.y == 0.0f );

		Vector2 v2( 3.0f, 12.0f );
		CHECK( v2.x == 3.0f && v2.y == 12.0f );
	}

	void Addition_Test()
	{
		Vector2 v1( 3.0f, 3.0f ), v2( 1.0f, 1.0f );
		Vector2 result = v1 + v2;
		CHECK( TestRunner::NearlyEqual( 4.0f, result.x ) );
		CHECK( TestRunner::NearlyEqual( 4.0f, result.y ) );
	}

	void Subtraction_Test()
	{
		Vector2 v1( 3.0f, 3.0f ), v2( 1.0f, 1.0f );
		Vector2 result = v1 - v2;
		CHECK( TestRunner::NearlyEqual( 2.0f, result.x ) );
		CHECK( TestRunner::NearlyEqual( 2.0f, result.y ) );
	}

	void ScalarMultiplication_Test()
	{
		Vector2 v1( 3.0f, 3.0f );
		float scalar = 4.0f;
		Vector2 result = v1 * scalar;
		CHECK( TestRunner::NearlyEqual( 12.0f, result.x ) );
		CHECK( TestRunner::NearlyEqual( 12.0f, result.y ) );
	}

	void Length_Test()
	{
		Vector2 v1( 3.0f, 4.0f );
		CHECK( TestRunner::NearlyEqual( 25.0f, v1.GetLengthSq() ) );
		CHECK( TestRunner::NearlyEqual( 5.0f, v1.GetLength() ) );
	}

	void Normalisation_Test()
	{
		Vector2 v1( 3.0f, 4.0f );
		Vector2 result = v1.GetNormalised();
		CHECK( TestRunner::NearlyEqual( result.GetLength(), 1.0f ) );
	}
}