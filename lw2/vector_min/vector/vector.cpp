#include <iostream>
#include "ProcessVector.h"
#pragma once


using namespace std;

int main()
{

	std::vector<double> numbers(istream_iterator<double>(cin), (istream_iterator<double>()));
	ProcessVector(numbers);
	std::sort(numbers.begin(), numbers.end());
	cout.precision(4);
	copy(numbers.begin(), numbers.end(), ostream_iterator<double>(cout, " "));


	return 0;
}
