
#include "../_testing/tests/Vector2_test.h"
#include "../_testing/tests/Vector3_test.h"

#include "../_testing/tests/Vector_test.h"
#include "../_testing/tests/Matrix_test.h"

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

	runner.AddTest( "Vector: Constructor test", Testing::Tests::Vector_test::Constructor_Test );
	runner.AddTest( "Vector: Comparison test", Testing::Tests::Vector_test::Comparison_Test );
	runner.AddTest( "Vector: Addition test", Testing::Tests::Vector_test::Addition_Test );
	runner.AddTest( "Vector: Subtraction test", Testing::Tests::Vector_test::Subtraction_Test );
	runner.AddTest( "Vector: Scalar multiplication test", Testing::Tests::Vector_test::ScalarMultiplication_Test );
	runner.AddTest( "Vector: Length test", Testing::Tests::Vector_test::Length_Test );
	runner.AddTest( "Vector: Normalisation test", Testing::Tests::Vector_test::Normalisation_Test );
	runner.AddTest( "Vector: Dot product test", Testing::Tests::Vector_test::DotProduct_Test );
	runner.AddTest( "Vector: Cross product test", Testing::Tests::Vector_test::CrossProduct_Test );

	runner.AddTest( "Matix: Contructor test", Testing::Tests::Matrix_test::Constructor_Test );
	runner.AddTest( "Matix: Scalar multiplication test", Testing::Tests::Matrix_test::Matrix_Scalar_Multiplication_Test );
	runner.AddTest( "Matix: Matrix multiplication test", Testing::Tests::Matrix_test::Matrix_Multiplication_Test );
	runner.AddTest( "Matix: Matrix vector multiplication test", Testing::Tests::Matrix_test::Matrix_Vector_Multiplication_Test );
	runner.AddTest( "Matix: Matrix transposition test", Testing::Tests::Matrix_test::Matrix_Transposition_Test );
	runner.AddTest( "Matix: Matrix determinant test", Testing::Tests::Matrix_test::Matrix_Determinant_Test );
	runner.AddTest( "Matix: Matrix inverse test", Testing::Tests::Matrix_test::Matrix_Inverse_Test );

	runner.RunAll();

	return 0;
}