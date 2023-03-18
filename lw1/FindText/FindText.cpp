/*
 В случае, когда искомая строка в файле найдена, приложение возвращает нулевое значение
и выводит в стандартный выводной поток номера всех строк(по одному номеру в каждой строке),
содержащих искомую строку.В противном случае программа возвращает 1 и выводит в стандартный поток вывода «Text not found».

поиск указанной строки в файле. Формат командной строки: findtext.exe “Евгений Онегин.txt” “Я к Вам пишу”

При осуществлении поиска регистр символов имеет значение (это упрощает поиск). Слова «Онегин» и «онегин» являются разными.
Программа должна корректно обрабатывать ошибки, связанные с файловыми операциями.
В комплекте с программой должны обязательно поставляться файлы, позволяющие проверить корректность её работы в автоматическом режиме.
*/

#include <fstream>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

using namespace std;

ofstream outputFileName("output.txt");

struct Args
{
	string inputFileName;
	string searchText;
};

optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 3)
	{
		cout << "Invalid arguments count\n";
		cout << "Usage: FindText.exe <input file name> <input phrase to find>\n";
		return std::nullopt; // пустой optional объект
	}
	Args args;
	args.inputFileName = argv[1];
	args.searchText = argv[2];

	return args;
}

int OpenFile(string inputFileName)
{
	std::ifstream input;
	input.open(inputFileName);
	if (!input.is_open())
	{
		std::cout << "Failed to open " << inputFileName << " file for reading\n";
		return 1;
	}

	input.open(inputFileName);
	if (!input.is_open())
	{
		cout << "Failed to open " << inputFileName << " file for reading\n";
		return 1;
	}
}


/*
int OpenOutputFile()
{
	if (!outputFileName.is_open())
	{
		cout << "Failed to open output file for writing\n";
		return 1;
	}
}
*/

bool FindText(string& searchText)
{
	int lineCounter = 0;
	vector<int> lineNumbers;
	bool found = false;
	

	ifstream input;

	while (!input.eof())
	{
		string s;

		while (getline(input, s))
		{
			lineCounter++;

			if (s.find(searchText) != std::string::npos)
			{
				lineNumbers.push_back(lineCounter);
				if (outputFileName.is_open())
				{
					outputFileName << to_string(lineCounter) << '\n';
				}
				found = true;
			}
		}
	}
	if (!found)
	{
		std::cout << "Text not found" << std::endl;
		return 0;
	}

	for (int i = 0; i < lineNumbers.size(); i++)
	{
		cout << lineNumbers[i] << endl;
	}
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	OpenFile(args->inputFileName);
	FindText(args->searchText);


	

	if (input.bad())
	{
		std::cout << "Failed to read data from input file\n";
		return 1;
	}
}
