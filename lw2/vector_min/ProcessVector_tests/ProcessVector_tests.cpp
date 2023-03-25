#include <iostream>
#pragma once
#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../vector/ProcessVector.h"

SCENARIO("Processing of empty vector gives empty vector")
{
	std::vector<double> v = {};
	std::vector<double> result = {};
	ProcessVector(v);
	CHECK(v == result);
}

SCENARIO("Processing of vector with one element gives vector with one element")
{
	std::vector<double> v = { 1.222 };
	std::vector<double> result = { 1.493};
	ProcessVector(v);
	CHECK(v == result);
}

SCENARIO("Processing of vector with multiple elements gives vector with multiple elements")
{
	std::vector<double> v = { 1.2, 2.4, 3.5 };
	std::vector<double> result = { 1.44, 2.88, 4.2	};
	ProcessVector(v);
	CHECK(v.size() == result.size());
	CHECK(v == result);
}

SCENARIO("Processing of vector with negative number gives vector with negative number")
{
	std::vector<double> v = { 5.3, -1.2 };
	std::vector<double> result = { -6.36, 1.44 };
	ProcessVector(v);
	CHECK(v.size() == result.size());
	CHECK(v == result);
}
