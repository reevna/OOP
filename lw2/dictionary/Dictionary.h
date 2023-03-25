#pragma once
#include <fstream>
#include <iostream>
#include <map>
#include <optional>
#include <string>
#include <vector>
#include <sstream>
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

