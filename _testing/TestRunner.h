#pragma once

#include <string>
#include <vector>
#include <functional>
#include <iostream>

// Custom assertion macro
#define CHECK(cond) if (!(cond)) throw std::runtime_error("Check failed: " #cond);

struct TestResult
{
	std::string name;
	bool passed;
	std::string message;
};

class TestRunner
{
public:
	void AddTest( const std::string& name, const std::function<void()>& test );
	void RunAll();
private:
	std::vector<std::pair<std::string, std::function<void()>>> m_tests;
	std::vector<TestResult> m_results;
};