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

#include "Dictionary.h"

int main(int argc, char* argv[])
{
	std::cout << "Translates words from Russian into English and vice versa.\n";
	std::cout << "Input <word> to translate or '...' to exit." << std::endl;

	Dictionary dictionary;
	dictionary.fileName = *GetDictionaryFileName(argc, argv);
	dictionary.dict = GetDictionaryFromFile(dictionary.fileName);

	if (Translation(dictionary))
	{
		SaveDictionary(dictionary);
	}

	std::cout << "Thanks for using!" << std::endl;

	return 0;
}


/*
#ifndef PCH_H
#define PCH_H

#include <Windows.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <locale>
#include <map>
#include <stdio.h>
#include <string>
#include <strstream>
#include <tchar.h>
#include <vector>

#endif // PCH_H



using namespace std;

#pragma once


typedef std::multimap<std::string, std::string> Dictionary;

void ReadDictionaryFromFile(std::ifstream& input, Dictionary& dictionary);

void AddWordToDictionaryy(const std::string& word, const std::string& translationWord, Dictionary& dictionary, bool& dictionaryChange);

void SaveDictionaryToFile(std::ofstream& output, const Dictionary& dictionary);

std::vector<std::string> FindWordInDictionary(const std::string& word, Dictionary& dictionary);

bool CheckArgumentCount(const int argumentCount);

void Translation(const std::string& fileName, Dictionary& dictionary);

void AddNewWord(const std::string& word, Dictionary& dictionary, bool& dictionaryChange);

void HandleNewWord(const std::string& str, Dictionary& dictionary, bool& dictionaryChange);

void CompleteTranslation(const std::string& fileName, const Dictionary& dictionary);

std::string ToLowerCase(std::string str);



bool CheckArgumentCount(const int argumentCount)
{
	if (argumentCount > 2)
	{
		cout << "Invalid argument count" << endl;
		cout << "translator [<input dictionary>]" << endl;
		return false;
	}
	return true;
}

string ToLowerCase(string str)
{
	locale loc;
	for (auto& ch : str)
	{
		ch = tolower(ch, loc);
	}
	return str;
}

void ReadDictionaryFromFile(ifstream& input, Dictionary& dictionary)
{
	string word, translationWord;
	while (getline(input, word))
	{
		if (getline(input, translationWord))
		{
			auto foundWords = FindWordInDictionary(word, dictionary);
			bool dictionaryChange = false;
			if (foundWords.empty())
			{
				AddWordToDictionaryy(word, translationWord, dictionary, dictionaryChange);
			}
		}
	}
}

void Translation(const string& fileName, Dictionary& dictionary)
{
	bool dictionaryChange = false;
	string inputString;
	while (inputString != "...")
	{
		cout << ">";
		getline(cin, inputString);
		if (inputString != "...")
		{
			HandleNewWord(ToLowerCase(inputString), dictionary, dictionaryChange);
		}
	}
	if (dictionaryChange)
	{
		CompleteTranslation(fileName, dictionary);
	}
	else
	{
		cout << "До свидания." << endl;
	}
}

void HandleNewWord(const string& word, Dictionary& dictionary, bool& dictionaryChange)
{
	auto foundWords = FindWordInDictionary(word, dictionary);
	if (foundWords.empty())
	{
		AddNewWord(word, dictionary, dictionaryChange);
	}
	else
	{
		for (size_t i = 0; i < foundWords.size(); ++i)
		{
			cout << foundWords[i] << " ";
		}
		cout << endl;
	}
}

void CompleteTranslation(const string& fileName, const Dictionary& dictionary)
{
	char ch;
	cout << "В словарь были внесены изменения. Введите Y или y для сохранения перед выходом." << endl;
	cout << ">";
	cin >> ch;
	if (ch == 'Y' || ch == 'y')
	{
		ofstream output(fileName);
		SaveDictionaryToFile(output, dictionary);
		cout << "Изменения сохранены. До свидания." << endl;
	}
	else
	{
		cout << "Изменения не сохранены. До свидания." << endl;
	}
}

void AddNewWord(const string& word, Dictionary& dictionary, bool& dictionaryChange)
{
	cout << "Неизвестное слово \"" << word << "\". Введите перевод или пустую строку для отказа." << endl;
	cout << ">";
	string translation;
	getline(cin, translation);
	if (!translation.empty())
	{
		AddWordToDictionaryy(word, translation, dictionary, dictionaryChange);
		cout << "Слово \"" + word + "\" сохранено в словаре как \"" + translation + "\"." << endl;
	}
	else
	{
		cout << "Слово \"" + word + "\" проигнорировано." << endl;
	}
}

void AddWordToDictionaryy(const string& word, const string& translationWord, Dictionary& dictionary, bool& dictionaryChange)
{
	dictionary.insert({ word, translationWord });
	dictionary.insert({ translationWord, word });
	dictionaryChange = true;
}

void SaveDictionaryToFile(ofstream& output, const Dictionary& dictionary)
{
	auto it = dictionary.begin();
	for (it = dictionary.begin(); it != dictionary.end(); ++it)
	{
		output << (*it).first << endl
			   << (*it).second << endl;
	}
}

vector<string> FindWordInDictionary(const string& word, Dictionary& dictionary)
{
	auto translations = dictionary.equal_range(word) | boost::adaptors::map_values;
	return { translations.begin(), translations.end() };

	std::vector<std::string> translations;
	std::string lowerInputWord = inputWord;

	// transform(inputWord.begin(), inputWord.end(), inputWord.begin(), ::tolower);

	for (auto it = dictionary.dict.begin(); it != dictionary.dict.end(); ++it)
	{
		const std::string translationFirst = ((*it).first);
		const std::string translationSecond = ((*it).second);
		if (lowerInputWord == translationFirst)
			translations.push_back((*it).second);
		if (lowerInputWord == translationSecond)
			translations.push_back((*it).first);
	}
	return translations;


}

std::vector<std::string> FindTranslation(const Dictionary& dictionary, const std::string& inputWord)
{

}




using namespace std;

int main(int argc, char* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	if (!CheckArgumentCount(argc))
	{
		return 1;
	}

	string fileName;
	Dictionary dictionary;
	if (argc == 2)
	{
		fileName = argv[1];
		ifstream input(fileName);
		if (input.is_open())
		{
			ReadDictionaryFromFile(input, dictionary);
			input.close();
		}
	}
	else
	{
		fileName = "dictionary.txt";
	}

	Translation(fileName, dictionary);

	return 0;
}



*/




/*

#pragma once


#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <optional>
#include <sstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <windows.h>

const std::string EXIT_TEXT = "...";
const enum UserState {
	WAITING_FOR_WORD,
	WAITING_FOR_TRANSLATION
};

struct Dictionary
{
	std::string fileName;
	std::multimap<std::string, std::string> dict;
	bool changed = false;
};

struct User
{
	UserState state;
	std::string newWord;
	std::string prevWord;
};

std::optional<std::string> GetDictionaryFileName(int argc, char* argv[]);
std::multimap<std::string, std::string> GetDictionaryFromFile(const std::string& fileName);
bool Translation(Dictionary& dictionary);
void ProcessInputWord(User& user, Dictionary& dictionary);
UserState ProcessWordWaiting(User& user, Dictionary& dictionary);
UserState ProcessWordTranslation(User& user, Dictionary& dictionary);
std::vector<std::string> FindTranslation(const Dictionary& dictionary, const std::string& inputWord);
void AddTranslation(User& user, Dictionary& dictionary);
void SaveDictionary(const Dictionary& dictionary, bool needSaving = false);


	std::optional<std::string> GetDictionaryFileName(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "The dictionary has not been set.\n";
		std::cout << "The default is dictionary_common.txt.\n";
		return "dictionary_common.txt";
	}

	return argv[1];
}

std::multimap<std::string, std::string> GetDictionaryFromFile(const std::string& fileName)
{
	std::multimap<std::string, std::string> dictionary;
	std::string fileStr, key, value;
	std::ifstream dictionaryFile(fileName);
	while (getline(dictionaryFile, fileStr))
	{
		std::vector<std::string> dictionaryPair;

		std::stringstream ss(fileStr);
		std::stringstream(fileStr) >> key >> value;

		dictionary.insert(std::pair<std::string, std::string>(key, value));
	}
	dictionaryFile.close();

	return dictionary;
}

bool Translation(Dictionary& dictionary)
{
	std::string inputWord;
	User user;
	user.state = WAITING_FOR_WORD;

	while (true)
	{
		getline(std::cin, user.newWord);
		if (user.newWord == EXIT_TEXT)
			break;
		ProcessInputWord(user, dictionary);
	}

	return dictionary.changed;
}

void ProcessInputWord(User& user, Dictionary& dictionary)
{
	switch (user.state)
	{
	case WAITING_FOR_WORD:
		user.state = ProcessWordWaiting(user, dictionary);
		break;
	case WAITING_FOR_TRANSLATION:
		user.state = ProcessWordTranslation(user, dictionary);
		break;
	default:
		break;
	}
	user.prevWord = user.newWord;
}

UserState ProcessWordWaiting(User& user, Dictionary& dictionary)
{
	if (user.newWord.length() == 0)
	{
		return WAITING_FOR_WORD;
	}
	std::vector<std::string> translations = FindTranslation(dictionary, user.newWord);
	if (translations.size() == 0)
	{
		std::cout << "There is no \"" << user.newWord << "\" in dictionary yet." << std::endl;
		std::cout << "Write the translation or press enter to skip." << std::endl;
		return WAITING_FOR_TRANSLATION;
	}
	else
	{
		std::cout << "The following translations were found for the word:" << std::endl;
		std::copy(translations.begin(), translations.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
		std::cout << "Write the next word or press \"...\" to exit." << std::endl;
		return WAITING_FOR_WORD;
	}
}

UserState ProcessWordTranslation(User& user, Dictionary& dictionary)
{
	AddTranslation(user, dictionary);
	return WAITING_FOR_WORD;
}

std::vector<std::string> FindTranslation(const Dictionary& dictionary, const std::string& inputWord)
{
	std::vector<std::string> translations;
	std::string lowerInputWord = inputWord;


	//transform(inputWord.begin(), inputWord.end(), inputWord.begin(), ::tolower);



	for (auto it = dictionary.dict.begin(); it != dictionary.dict.end(); ++it)
	{
		const std::string translationFirst = ((*it).first);
	const std::string translationSecond = ((*it).second);
		if (lowerInputWord == translationFirst)
			translations.push_back((*it).second);
		if (lowerInputWord == translationSecond)
			translations.push_back((*it).first);
	}
	return translations;
}

void AddTranslation(User& user, Dictionary& dictionary)
{
	if (user.newWord.length() != 0 && FindTranslation(dictionary, user.prevWord).size() == 0)
	{
		dictionary.dict.emplace(user.prevWord, user.newWord);
		dictionary.changed = true;
		std::cout << "Translation for \"" << user.prevWord << "\" added." << std::endl;
		std::cout << "Write the next word or press \"...\" to exit." << std::endl;
	}
}

void SaveDictionary(const Dictionary& dictionary, bool needSaving)
{
	std::cout << "The dictionary was changed. Would you like to save changes? (y/Y)" << std::endl;
	char save = std::cin.get();
	if (save == 'y' || save == 'Y' || needSaving)
	{
		std::ofstream newFile;
		newFile.open(dictionary.fileName, std::ios::trunc);
		for (auto it = dictionary.dict.begin(); it != dictionary.dict.end(); ++it)
		{
			newFile << (*it).first << " " << (*it).second << "\n";
		}
		std::cout << "Dictionary has saved in file " << dictionary.fileName << std::endl;
	}
}








int main(int argc, char* argv[])
{
	std::cout << "Translates words from Russian into English and vice versa.\n";
	std::cout << "Input <word> to translate or '...' to exit." << std::endl;

	Dictionary dictionary;
	dictionary.fileName = *GetDictionaryFileName(argc, argv);
	dictionary.dict = GetDictionaryFromFile(dictionary.fileName);

	if (Translation(dictionary))
	{
		SaveDictionary(dictionary);
	}

	std::cout << "Thanks for using!" << std::endl;

	return 0;
}



*/













/*
#include <Windows.h>
#include <boost/algorithm/string.hpp>
#include <fstream>
#include <iostream>
#include <map>
#include <optional>
#include <sstream>
#include <vector>
using namespace std;

optional<string> GetDictionaryFileName(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "The dictionary was not been set.\n"; // TODO:: use const EOLN
		std::cout << "The default is default_dictionary.txt.\n";
		return "defaultDictionary.txt";
	}

	return argv[1];
}

/*

std::multimap<string, string> GetDictionaryFromFile(const string& fileName)
{

	ifstream dictionaryFile(fileName);
	multimap<string, string> dictionary;
	string fileStr;
	 std::vector<std::string> tokens;
	std::string token;
	 std::stringstream ss(fileStr);

	while (getline(ss, token, ' '))
	{
		tokens.push_back(token);
		dictionary.emplace(token[0], token[1]);
	}

	dictionaryFile.close();

	return dictionary;
}

*/

/*

std::multimap<string, string> GetDictionaryFromFile(const string& fileName)
{
c
	string fileStr;
	ifstream dictionaryFile(fileName);
	while (getline(dictionaryFile, fileStr))
	{
		vector<std::string> dictionaryPair;
	//	dictionaryPair = fileStr.split(string[]{ ' ' });
		boost::split(dictionaryPair, fileStr, [](char c) { return c == ' '; });
		dictionary.emplace(dictionaryPair[0], dictionaryPair[1]);
	}
	dictionaryFile.close();

	return dictionary;
}


multimap<string, string> GetDictionaryFromFile(const string& fileName)
{
	//	ReadDictionaryFromFile(ifstream & input, Dictionary & dictionary)
	multimap<string, string> dictionary;
	string fileStr;
	ifstream dictionaryFile(fileName);
	string word, translationWord;
	while (!fileName.eof())
	{
		//(!eof(dictionaryFile, fileStr))

		while (getline(fileStr, " "))
		{

			dictionary.emplace(word, translationWord);
		}
	}

	int main(int argc, char* argv[])
	{
		string fileName;
		fileName = *GetDictionaryFileName(argc, argv);
		setlocale(LC_ALL, "ru");
		string path = "defaultDictionary.txt";

		cout << "The Dictionary translates words from English into Russian and vice versa.\n";
		cout << "Input <word> to translate or '...' to exit." << endl;

		multimap<string, string> dictionary;

		fstream fileName;
		fileName.open(path, fstream::in | fstream::out | fstream::app); // можем и считывать и записывать через побитовое или

		if (!fileName.is_open())
		{
			cout << "Ошибка открытия файла" << endl;
		}
		else
		{
			string inputKey;

			cin >> inputKey;

			if (inputKey != "...")

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

					SetConsoleCP(1251);
					cin >> inputValue;
					//	fs << inputValue << "\n";
					SetConsoleCP(866);

					//	cin >> inputValue;
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
			}
			else
			{

				cout << "Сохранить новые слова в файл словаря? Введите 'Y' для сохранения и 'N' для отмены." << endl;
				string saveDictionary;
				cin >> saveDictionary;
				if (saveDictionary == "Y" || saveDictionary == "y")
				{
				}
				if (saveDictionary == "N" || saveDictionary == "n")
				{
				}
				cout << "Goodbye!" << endl;
			}

			/*
				if (value == 2)
			{
				while (!fs.eof())
				{
					inputKey = "";
					getline(fs, inputKey);

				//	fs >> msg;
					cout << inputKey << endl;
				}
			}
		
		}
		fs.close();
		return 0;
	}
		/*

		string inputKey;
		//	bool running = true;

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




		*/



	/*




	int main(int argc, char* argv[])
	{


		//auto args = GetDictionaryFileName(argc, argv);
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

	*/

	/*
	читать вход
	читать файл в map
	сравнение инпута и ключей из файла
	вывод ответа если ключ найден
	вывод предложения добавить слово, если ключа нет
	выход из программы
	предложение сохранить словать
	запись измененной map в файл


	Проверки:
	отсутствие словаря на входе
	есть словать - полный
	есть словарь - пустой




	*/
