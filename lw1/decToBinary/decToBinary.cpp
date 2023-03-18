/*
–азработайте программу dec2bin.exe, выполн€ющую перевод числа из дес€тичной системы в двоичную и вывод результата
в стандартный поток вывода.‘ормат командной строки : bin2dec.exe <число в дес€тичной системе>
¬ходной параметр задаетс€ в виде целого числа без знака, заданного в двоичной системе в диапазоне от 0 до 232 - 1.
¬ыводимое число в двоичной не должно содержать незначащих нулевых бит.
Ќапример, в результате вызова
bin2dec.exe 253
в стандартный поток вывода должно быть выведено число 11111101.
ƒл€ перевода числа из дес€тичной системы в двоичную систему используйте арифметические операции и операции манипулировани€ битами.
¬ том случае, когда в качестве входного параметра указано некорректное дес€тичное число,
программа должна вывести соответствующее сообщение об ошибке.
¬ комплекте с программой должны об€зательно поставл€тьс€ файлы, позвол€ющие проверить ее работу в автоматическом режиме.
158 - 10011110

*/

#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>
#include <vector>

using namespace std;

struct Args
{
	string inputNumber;
};

optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Invalid arguments count\n";//TODO:: use const EOLN
		cout << "Enter number to convert to binary\n";
		return std::nullopt; 
	}
	Args args;
	args.inputNumber = argv[1];

	return args;
}

void PrintByBits(unsigned int m)
{
	if (m)
	{
		PrintByBits(m >> 1);
		std::cout << (m & 1);
	}
}

vector<int> bits;//TODO: глобальные переменные - зло

void toBinary(unsigned int n)
{
	//TODO: возможно, добавить €вное округление
	if (n / 2 != 0)
	{
		toBinary(n / 2);
	}
	bits.push_back(n % 2);
}

void PrintArithmetical()
{
	for (int i = 0; i < bits.size(); i++)
	{
		cout << bits[i];
	}
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	//TODO: проверить, что args не пустой и далее брать значени€ из него
	std::stringstream inputString{ argv[1] }; //TODO: istream, rename inputString->input
	int inputInt;//TODO: это число, можно так назвать

	if (inputString >> inputInt)
	{
		//TODO: на -1 не работает
		PrintByBits(inputInt);//TODO: на нуле не работает 
		cout << '\n';
		toBinary(inputInt);
		PrintArithmetical();
	}
	else
	{
		cout << "You have entered not a number\n";
		//TODO: return EXIST_FAILED const
	}

	return 0;
}
