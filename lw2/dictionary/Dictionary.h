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

// ������ ������ ������� , ������c���� � cpp 

const std::string EXIT_TEXT = "...";

struct Dictionary
{
	std::string fileName;
	std::multimap<std::string, std::string> dict;
	bool changed = false;
};

// �������� ����������� �������� �� ���������������� 
// ����� �������������� Word trtanslation  / input - ������� ��������� 
struct Input
{
	std::string keyWord;
	std::string valueWord;
};

std::optional<std::string> GetDictionaryFileName(int argc, char* argv[]);
std::multimap<std::string, std::string> GetDictionaryFromFile(const std::string& fileName);
//�������� �������� ������� ����������
bool Translation(Dictionary& dictionary);
// �������� �������� ������� ProcessInputWord
void ProcessInputWord(Input& Input, Dictionary& dictionary);
std::vector<std::string> FindTranslation(const Dictionary& dictionary, const std::string& inputWord);
// ���������� � ���������� � ��������� 
void AddTranslation(Input& Input, Dictionary& dictionary);
// ������ ���� ����� �� ��������� ? 
void SaveDictionary(const Dictionary& dictionary, bool needSaving = false);
