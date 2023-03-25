#include "ProcessVector.h"
#pragma once

void ProcessVector(std::vector<double>& numbers)
{
	if(!numbers.empty())
	{
		auto minItem = *min_element(numbers.begin(), numbers.end());
		auto multiplyByMin = [minItem](double numbers) {
			return numbers * minItem;
		};
		transform(numbers.begin(), numbers.end(), numbers.begin(), multiplyByMin);
	}
}