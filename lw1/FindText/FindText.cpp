/*
 В случае, когда искомая строка в файле найдена, приложение возвращает нулевое значение
и выводит в стандартный выводной поток номера всех строк(по одному номеру в каждой строке),
содержащих искомую строку.В противном случае программа возвращает 1 и выводит в стандартный поток вывода «Text not found».

поиск указанной строки в файле. Формат командной строки: findtext.exe “Евгений Онегин.txt” “Я к Вам пишу”

При осуществлении поиска регистр символов имеет значение (это упрощает поиск). Слова «Онегин» и «онегин» являются разными.
Программа должна корректно обрабатывать ошибки, связанные с файловыми операциями.
В комплекте с программой должны обязательно поставляться файлы, позволяющие проверить корректность её работы в автоматическом режиме.
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
		return std::nullopt; // пустой optional объект
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

	// Проверка правильности аргументов командной строки
	if (!args)
	{
		return 1;
	}

	//Открыть входной файл
	std::ifstream input;
	input.open(args->inputFileName);
	if (!input.is_open())
	{
		std::cout << "Failed to open " << args->inputFileName << " file for reading\n";
		return 1;
	}

	bool found = false;
// считать построчно файл
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

