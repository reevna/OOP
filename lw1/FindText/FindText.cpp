/*
 � ������, ����� ������� ������ � ����� �������, ���������� ���������� ������� ��������
� ������� � ����������� �������� ����� ������ ���� �����(�� ������ ������ � ������ ������),
���������� ������� ������.� ��������� ������ ��������� ���������� 1 � ������� � ����������� ����� ������ �Text not found�.

����� ��������� ������ � �����. ������ ��������� ������: findtext.exe �������� ������.txt� �� � ��� ����

��� ������������� ������ ������� �������� ����� �������� (��� �������� �����). ����� ������� � ������� �������� �������.
��������� ������ ��������� ������������ ������, ��������� � ��������� ����������.
� ��������� � ���������� ������ ����������� ������������ �����, ����������� ��������� ������������ � ������ � �������������� ������.
*/

#include <iostream>
#include <fstream>
#include <optional>
#include <string>

using namespace std;

struct Args
{
	string inputFileName;
	string searchText;
};

optional<Args>ParseArgs(int argc, char* argv[])
{
	if (argc != 3)
	{
		cout << "Invalid arguments count\n";
		cout << "Usage: FindText.exe <input file name> <input phrase to find>\n";
		return std::nullopt; // ������ optional ������
	}
	Args args;
	args.inputFileName = argv[1];
	args.searchText = argv[2];
	return args;
}

/*
int OpenFile(std::ifstream input, )
{
	input.open(args->inputFileName);
	if (!input.is_open())
	{
		std::cout << "Failed to open " << args->inputFileName << " file for reading\n";
		return 1;
	}
}
*/



int main(int argc, char* argv[])
{
	int lineCounter = 0;
	auto args = ParseArgs(argc, argv);

	// �������� ������������ ���������� ��������� ������
	if (!args)
	{
		return 1;
	}

	//������� ������� ����
	std::ifstream input;
	input.open(args->inputFileName);
	if (!input.is_open())
	{
		std::cout << "Failed to open " << args->inputFileName << " file for reading\n";
		return 1;
	}

	bool found = false;
// ������� ��������� ����
	while (!input.eof())
	{
		string s;
	
		while (getline(input, s))
		{
			lineCounter++;
			
			if (s.find(args->searchText) != std::string::npos) {
				std::cout << lineCounter << '\n';
				found = true;
			}
		}

		if (!found) {
			std::cout << "Text not found" << std::endl;
			return 0;
		}
	}
}

