/*
Задание 1. Основы работы с контейнером vector.
20 баллов
	Ознакомьтесь с возможностями класса vector библиотеки STL,
	а также с основными алгоритмами STL.
	Разработайте программу,выполняющую считывание массива чисел с плавающей запятой, разделяемых пробелами,
	из стандартного потока ввода в vector, обрабатывающую его согласно заданию Вашего варианта
	и выводящую в стандартный поток полученный массив(разделенный пробелами).
	В программе должны быть выделены функции, выполняющие считывание массива,
	его обработку и вывод результата.
	Для тестирования разрабатываемых функций должны быть разработаны тесты,
	проверяющие корректность их работы на некотором разумном наборе входных параметров.
	
	2.Каждый элемент массива должен быть умножен на минимальный элемент исходного массива
	Бонус 10 баллов за сортировку элементов массива в порядке возрастания
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
