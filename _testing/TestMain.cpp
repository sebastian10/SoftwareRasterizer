
#include "../_testing/tests/Vector2_test.h"
#include "../_testing/tests/Vector3_test.h"

int main()
{
	Testing::TestRunner runner;
	runner.AddTest( "Vector2: Constructor test", Testing::Tests::Vector2_test::Constructor_test );
	runner.AddTest( "Vector2: Comparison test", Testing::Tests::Vector2_test::Comparison_Test );
	runner.AddTest( "Vector2: Addition test", Testing::Tests::Vector2_test::Addition_Test );
	runner.AddTest( "Vector2: Subtraction test", Testing::Tests::Vector2_test::Subtraction_Test );
	runner.AddTest( "Vector2: Scalar multiplication test", Testing::Tests::Vector2_test::ScalarMultiplication_Test );
	runner.AddTest( "Vector2: Length test", Testing::Tests::Vector2_test::Length_Test );
	runner.AddTest( "Vector2: Normalisation test", Testing::Tests::Vector2_test::Normalisation_Test );

	runner.AddTest( "Vector3: Constructor test", Testing::Tests::Vector3_test::Constructor_test );
	runner.AddTest( "Vector3: Comparison test", Testing::Tests::Vector3_test::Comparison_Test);
	runner.AddTest( "Vector3: Addition test", Testing::Tests::Vector3_test::Addition_Test );
	runner.AddTest( "Vector3: Subtraction test", Testing::Tests::Vector3_test::Subtraction_Test );
	runner.AddTest( "Vector3: Scalar multiplication test", Testing::Tests::Vector3_test::ScalarMultiplication_Test );
	runner.AddTest( "Vector3: Length test", Testing::Tests::Vector3_test::Length_Test );
	runner.AddTest( "Vector3: Normalisation test", Testing::Tests::Vector3_test::Normalisation_Test );
	runner.AddTest( "Vector3: Cross product test", Testing::Tests::Vector3_test::CrossProduct_Test );

	runner.RunAll();

	return 0;
}