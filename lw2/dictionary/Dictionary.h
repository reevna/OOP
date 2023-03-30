#pragma once
#include <fstream>
#include <iostream>
#include <map>
#include <optional>
#include <string>
#include <vector>
#include <sstream>
#include <windows.h>
#include <algorithm>

// убрать лишние инклюды , перемеcтить в cpp 

const std::string EXIT_TEXT = "...";

struct Dictionary
{
	std::string fileName;
	std::multimap<std::string, std::string> dict;
	bool changed = false;
};

// програма некорректно рабоатет со словосочетаниями 
// инпут переименоватьь Word trtanslation  / input - слишком абстракно 
struct Input
{
	std::string keyWord;
	std::string valueWord;
};

std::optional<std::string> GetDictionaryFileName(int argc, char* argv[]);
std::multimap<std::string, std::string> GetDictionaryFromFile(const std::string& fileName);
//поменять название функции транслэйшн
bool Translation(Dictionary& dictionary);
// поменять название функции ProcessInputWord
void ProcessInputWord(Input& Input, Dictionary& dictionary);
std::vector<std::string> FindTranslation(const Dictionary& dictionary, const std::string& inputWord);
// переменные и параметраы с маленькой 
void AddTranslation(Input& Input, Dictionary& dictionary);
// почему сэйв может не сохранять ? 
void SaveDictionary(const Dictionary& dictionary, bool needSaving = false);
