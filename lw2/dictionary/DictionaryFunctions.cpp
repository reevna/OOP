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
	dictionaryFile.close();

	return dictionary;
}

bool Translation(Dictionary& dictionary)
{
	std::string inputWord;

	User user;

	while (true)
	{
		getline(std::cin, user.keyWord);
		if (user.keyWord == EXIT_TEXT)
			break;
		ProcessInputWord(user, dictionary);
	}

	return dictionary.changed;
}


void ProcessInputWord(User& user, Dictionary& dictionary)
{
	// слова нет в словаре
	std::vector<std::string> translations = FindTranslation(dictionary, user.keyWord);
	if (translations.size() == 0)
	{
		std::cout << "There is no \'" << user.keyWord << "\' in dictionary yet." << std::endl;
		std::cout << "Write the translation or press enter to skip." << std::endl;
		getline(std::cin, user.valueWord);
		if (user.valueWord.size() != 0)
		{
			AddTranslation(user, dictionary);
		}
		else
		{
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
	if (user.keyWord.length() == 0)
	{
		std::cout << "Write next word or press \"...\" to exit." << std::endl;
	}
}	


std::vector<std::string> FindTranslation(const Dictionary& dictionary, const std::string& inputWord)
{
	std::vector<std::string> translations;

	//	transform(inputWord.begin(), inputWord.end(), inputWord.begin(),
	//	[](unsigned char c) { return std::tolower(c); });
	
	std::string lowerInputWord = inputWord;
		

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
	if (user.keyWord.length() != 0 && FindTranslation(dictionary, user.valueWord).size() == 0)
	{
		dictionary.dict.emplace(user.keyWord, user.valueWord);
		dictionary.changed = true;
		std::cout << "Translation for \"" << user.keyWord << "\" has been saved as \"" << user.valueWord << "\"." << std::endl;
		std::cout << "Write next word or press \"...\" to exit." << std::endl;
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
		std::cout << "Dictionary has been saved to file " << dictionary.fileName << std::endl;
	}
}


