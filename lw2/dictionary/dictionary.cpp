/*Вариант 2 – мини-словарь – 90 баллов
Разработайте программу - словарь, осуществляющую перевод слов и словосочетаний, поступающих со стандартного потока ввода,
с английского языка на русский с использованием заданного файла словаря и выводящую результат перевода в стандартный поток вывода.
Если вводимое слово или словосочетание, отсутствует в словаре, программа должна попросить пользователя ввести перевод и запомнить его,
в случае, если пользователь ввел непустую строку.Для выхода из диалога с программой пользователь должен ввести строку, состоящую из трех точек.
Перед выходом программа спрашивает о необходимости сохранить изменения в файле словаря, в том случае, если в словарь были добавлены фразы
во время текущей сессии работы с программой.Имя файла словаря передается программе с помощью параметра командной строки.Если файл словаря отсутствует,
то программа должна считать его пустым и предложить сохранить словарь по окончании работы, если туда были добавлены фразы.

Бонус 10 баллов за возможность распознавания слов, записанных в разном регистре
Дополнительно можно получить до 10 баллов, если программа будет способна осуществлять перевод английских слов,
вводимых пользователем в произвольном регистре символов.
Например, слова CaT, при известном переводе для слова cat. Регистр перевода теряться не должен.

Бонус 20 баллов за реализацию двунаправленного перевода
Дополнительно можно получить до 20 баллов, если программа сможет осуществлять и обратный перевод словосочетаний.
При этом необходимо поддержать возможность существования нескольких вариантов перевода одного и того же слова.
Например, после добавления слов «кошка»«cat» и «кот»«cat», программа должна иметь возможность перевести слово cat, выдав 2 возможных перевода.


*/

#include <iostream>
#include <map>
#include <vector>
#include <optional>
#include <sstream>
#include <fstream>

using namespace std;

struct Args
{
	string inputNumber;
};

optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Invalid arguments count\n"; // TODO:: use const EOLN
		cout << "Enter number to convert to binary\n";
		return std::nullopt;
	}
	Args args;
	args.inputNumber = argv[1];

	return args;
}



int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");

	auto args = ParseArgs(argc, argv);
	// TODO: проверить, что args не пустой и далее брать значения из него

	std::stringstream input{ argv[1] }; // TODO: istream, rename inputString->input
	int inputString;
	if (input >> inputString)
	{
		// тело функции
	}
	else
	{
		cout << "You have entered not a number\n";
		// TODO: return EXIST_FAILED const
	}







	multimap<string, string> dictionary;
	string inputKey;
	//	bool running = true;
	dictionary.emplace("Apple", "Яблоко");
	dictionary.emplace("Apple", "Яблоко2");
	dictionary.emplace("dog", "собака");
	dictionary.emplace("cat", "кот");

	cin >> inputKey;
	while (inputKey != "...")
	{

		if (dictionary.find(inputKey) != dictionary.end())
		{

			auto range = dictionary.equal_range(inputKey);
			for (auto i = range.first; i != range.second; ++i)
			{
				cout << i->second << '\n';

				continue;
			}
			cout << "\n";
			cin >> inputKey;
		}
		else
		{
			string inputValue;
			cout << "Неизвестное слово " << inputKey << ". Введите перевод или пустую строку для отказа." << endl;
			cin >> inputValue;
			if (inputValue != "")
			{
				dictionary.emplace(inputKey, inputValue);
				cout << "Слово '" << inputKey << "' сохранено в словаре как '" << inputValue << "'"
					 << "\n";
				cin >> inputKey;
			}
			else
			{
				cout << "Слово '" << inputValue << "' проигнорировано.";
				cin >> inputKey;
			}
			
		}
		continue;
	}

	return 0;
}

/*
читать вход
читать файл в map
сравнение инпута и ключей из файла
вывод ответа если ключ найден
вывод предложения добавить слово, если ключа нет
выход из программы
предложение сохранить словать
запись измененной map в файл





*/
