
#include "../_testing/tests/Vector2_test.h"

int main()
{
	Testing::TestRunner runner;
	runner.AddTest( "Vector2: Constructor test", Testing::Tests::Vector2_test::Constructor_test );
	runner.AddTest( "Vector2: Addition test", Testing::Tests::Vector2_test::Addition_Test );
	runner.AddTest( "Vector2: Subtraction test", Testing::Tests::Vector2_test::Subtraction_Test );
	runner.AddTest( "Vector2: Scalar multiplication test", Testing::Tests::Vector2_test::ScalarMultiplication_Test );
	runner.AddTest( "Vector2: Length test", Testing::Tests::Vector2_test::Length_Test );
	runner.AddTest( "Vector2: Normalisation test", Testing::Tests::Vector2_test::Normalisation_Test );

	runner.RunAll();

	return 0;
}