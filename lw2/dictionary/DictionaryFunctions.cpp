#include "Dictionary.h"

std::optional<std::string> GetDictionaryFileName(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "The dictionary has not been set.\n";
		std::cout << "The default is defaultDictionary.txt.\n";
		return "defaultDictionary.txt";
	}

	return argv[1];
}

std::multimap<std::string, std::string> GetDictionaryFromFile(const std::string& fileName)
{
	std::multimap<std::string, std::string> dictionary;
	std::ifstream dictionaryFile(fileName);
	std::string fileStr, key, value;

	while (getline(dictionaryFile, fileStr))
	{
		std::vector<std::string> dictionaryPair;

		std::stringstream ss(fileStr);
		std::stringstream(fileStr) >> key >> value;

		dictionary.insert(std::pair<std::string, std::string>(key, value));
	}
	dictionaryFile.close();// сам закроетс€

	return dictionary;
}

bool Translation(Dictionary& dictionary)
{
	std::string inputWord;

	Input Input;

	while (true)
	{
		getline(std::cin, Input.keyWord);
		if (Input.keyWord == EXIT_TEXT)
		{
			break;
		}

		ProcessInputWord(Input, dictionary);
	}
	// нужно ли возвращать то, что вызывающий код может сам спросить 
	return dictionary.changed;
}
// ¬озможно стоит разделить функцию на другие  -  слишклм абстрактна€ 
void ProcessInputWord(Input& Input, Dictionary& dictionary)
{
	// слова нет в словаре
	std::vector<std::string> translations = FindTranslation(dictionary, Input.keyWord);
	if (translations.size() == 0)
	{
		std::cout << "There is no \'" << Input.keyWord << "\' in dictionary yet." << std::endl;
		std::cout << "Write the translation or press enter to skip." << std::endl;
		getline(std::cin, Input.valueWord);
		if (Input.valueWord.size() != 0)
		{
			AddTranslation(Input, dictionary);
		}
		else
		{// дубль кода
			std::cout << "Write next word or press \"...\" to exit." << std::endl;
		}
	}

	// слово есть в словаре
	else
	{
		std::cout << "The following translations were found for the word:" << std::endl;
		std::copy(translations.begin(), translations.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
		std::cout << "Write next word or press \"...\" to exit." << std::endl;
	}

	// пустой ввод
	if (Input.keyWord.length() == 0)
	{
		std::cout << "Write next word or press \"...\" to exit." << std::endl;
	}
}

std::vector<std::string> FindTranslation(const Dictionary& dictionary, const std::string& inputWord)
{
	std::vector<std::string> translations;

	std::string lowerInputWord = inputWord;

	std::transform(lowerInputWord.begin(), lowerInputWord.end(), lowerInputWord.begin(),
		[](unsigned char c) { return std::tolower(c); });

	// поиск в словаре должен быть быстрым lowerbound / upperboud возвращают два диапазона  
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

void AddTranslation(Input& Input, Dictionary& dictionary)
{
	if (Input.keyWord.length() != 0 && FindTranslation(dictionary, Input.valueWord).size() == 0)
	{
		dictionary.dict.emplace(Input.keyWord, Input.valueWord);
		dictionary.changed = true;
		std::cout << "Translation for \"" << Input.keyWord << "\" has been saved as \"" << Input.valueWord << "\"." << std::endl;
		std::cout << "Write next word or press \"...\" to exit." << std::endl;// дубль 
	}
}

void SaveDictionary(const Dictionary& dictionary, bool needSaving)
{
	std::cout << "The dictionary was changed. Would you like to save changes? (y/Y)" << std::endl;
	char save = std::cin.get();
	if (save == 'y' || save == 'Y' || needSaving)
	{
		std::ofstream newFile;
		newFile.open(dictionary.fileName, std::ios::trunc); // trunc removes old content from file
		for (auto it = dictionary.dict.begin(); it != dictionary.dict.end(); ++it)
		{
			newFile << (*it).first << " " << (*it).second << "\n";
		}
		std::cout << "Dictionary has been saved to file " << dictionary.fileName << std::endl;
	}
}
