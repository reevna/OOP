/*
������������ ��������� dec2bin.exe, ����������� ������� ����� �� ���������� ������� � �������� � ����� ����������
� ����������� ����� ������.������ ��������� ������ : bin2dec.exe <����� � ���������� �������>
������� �������� �������� � ���� ������ ����� ��� �����, ��������� � �������� ������� � ��������� �� 0 �� 232 - 1.
��������� ����� � �������� �� ������ ��������� ���������� ������� ���.
��������, � ���������� ������
bin2dec.exe 253
� ����������� ����� ������ ������ ���� �������� ����� 11111101.
��� �������� ����� �� ���������� ������� � �������� ������� ����������� �������������� �������� � �������� ��������������� ������.
� ��� ������, ����� � �������� �������� ��������� ������� ������������ ���������� �����,
��������� ������ ������� ��������������� ��������� �� ������.
� ��������� � ���������� ������ ����������� ������������ �����, ����������� ��������� �� ������ � �������������� ������.
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

vector<int> bits;//TODO: ���������� ���������� - ���

void toBinary(unsigned int n)
{
	//TODO: ��������, �������� ����� ����������
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
	//TODO: ���������, ��� args �� ������ � ����� ����� �������� �� ����
	std::stringstream inputString{ argv[1] }; //TODO: istream, rename inputString->input
	int inputInt;//TODO: ��� �����, ����� ��� �������

	if (inputString >> inputInt)
	{
		//TODO: �� -1 �� ��������
		PrintByBits(inputInt);//TODO: �� ���� �� �������� 
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
