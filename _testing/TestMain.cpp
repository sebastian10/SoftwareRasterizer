
#include "../_testing/tests/Vector_test.h"
#include "../_testing/tests/Matrix_test.h"

int main()
{
	Testing::TestRunner runner;
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

	std::cout << "\nPress any key to exit..." << std::endl;
	std::cin.get();

	return 0;
}