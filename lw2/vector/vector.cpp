/*
������� 1. ������ ������ � ����������� vector.
20 ������
	������������ � ������������� ������ vector ���������� STL,
	� ����� � ��������� ����������� STL.
	������������ ���������,����������� ���������� ������� ����� � ��������� �������, ����������� ���������,
	�� ������������ ������ ����� � vector, �������������� ��� �������� ������� ������ ��������
	� ��������� � ����������� ����� ���������� ������(����������� ���������).
	� ��������� ������ ���� �������� �������, ����������� ���������� �������,
	��� ��������� � ����� ����������.
	��� ������������ ��������������� ������� ������ ���� ����������� �����,
	����������� ������������ �� ������ �� ��������� �������� ������ ������� ����������.
	
	2.������ ������� ������� ������ ���� ������� �� ����������� ������� ��������� �������
	����� 10 ������ �� ���������� ��������� ������� � ������� �����������
*/


#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <exception>
#include <optional>
#include <iomanip>

using namespace std;


optional<vector<float>> ParseVector(istream& input)
{
	string line;
	vector<float> numbers;
	if (getline(input, line))
	{
		stringstream stringIterator(line);
		copy(istream_iterator<float>(stringIterator), istream_iterator<float>(), inserter(numbers, numbers.end()));
	}
	if (numbers.empty() || input.fail())
	{
		return nullopt;
	}

	return numbers;
}


void MultiplyByMin(vector<float>& numbers)
{
	if (!numbers.empty())
	{
		auto minItem = *min_element(numbers.begin(), numbers.end());
		auto multiplyByMin = [minItem](float numbers) {
			return numbers * minItem;
		};
		transform(numbers.begin(), numbers.end(), numbers.begin(), multiplyByMin);
	}
}

void SortVector(std::vector<float>& numbers)
{
	sort(numbers.begin(), numbers.end());
}


void PrintVector(ostream& output, const vector<float>& numbers)
{
	for (int i = 0; i < numbers.size(); ++i)
	{
		output << fixed << setprecision(3) << numbers[i];
		if (i != numbers.size() - 1)
		{
			output << " ";
		}
	}
	output << std::endl;
}

int main()
{
	auto numbers = ParseVector(cin);
	if (!numbers.has_value())
	{
		return 1;
	}
	MultiplyByMin(numbers.value());
	SortVector(numbers.value());
	PrintVector(cout, numbers.value());
	return 0;
}
