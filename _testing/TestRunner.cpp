#include "../testing/TestRunner.h"

void TestRunner::AddTest( const std::string& name, const std::function<void()>& test )
{
	m_tests.emplace_back( std::pair<std::string, std::function<void()>>( name, test ) );
}

void TestRunner::RunAll()
{
	int passedCount = 0;
	std::cout << "Running " << m_tests.size() << " tests...\n\n";

	for ( auto&[name, test] : m_tests )
	{
		try
		{
			test();
			passedCount++;
			m_results.push_back( { name, true, "" } );
			std::cout << "[PASS] " << name << "\n";
		}
		catch ( const std::exception& e )
		{
			m_results.push_back( { name, false, e.what() } );
			std::cout << "[FAILED] " << name << " - " << e.what() << "\n";
		}
		catch ( ... )
		{
			m_results.push_back( { name, false, "Unknown error" } );
			std::cout << "[FAILED] " << name << " - Unknown error\n";	
		}

		std::cout << "Summary: " << passedCount << "/" << m_tests.size() << " passed. \n";
	}
}