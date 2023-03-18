
#include <fstream>
#include <iomanip>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <vector>
#include <array>

using namespace std;

const int MATRIX_SIZE = 3;
const int ERROR = 1;
typedef double matrix[MATRIX_SIZE][MATRIX_SIZE];

using Matrix3x3 = array<array<double, 3>, 3>;

Matrix3x3 Multiply(const Matrix3x3& m1, const Matrix3x3& m2)
{
	Matrix3x3 result;
	return result;
}

struct CommandLineArgument
{
	string leftMatrix;
	string rightMatrix;
};

optional<CommandLineArgument> ParseArgs(int argc, char* argv[])
{
	if (argc != 3)
	{
		return nullopt;
	}
	CommandLineArgument argument;
	argument.leftMatrix = argv[1];
	argument.rightMatrix = argv[2];
	return argument;
}

vector<string> split(const string& line)
{
	stringstream ss(line);
	vector<string> result;
	string number;
	while (ss >> number)
	{
		result.push_back(number);
	}
	return result;
}

//Функции с заглавноц буквы
double stringToDouble(const string& value, bool& error)
{
	//использовать исключение,,?
	try
	{
		return stod(value);
	}
	catch (const exception&)
	{
		error = true;
		return 0;
	}
}
//упростить 
//в условиях if ... чтобы ф-ция возвращала bool
void ParseMatrixFromFile(istream& inputFile, matrix& result, bool& error)
{
	string line;
	int r = 0;
	while (!inputFile.eof())
	{
		getline(inputFile, line);
		#if 0
		std::istringstream strm;
		if (!(strm >> result[0] >> result[1] >> result[1]))
		{
			// ошибка
		}
		#endif

		if (line == "")
			return;
		auto row = split(line);
		if (row.size() != MATRIX_SIZE)
		{
			error = true;
			return;
		}
		for (int i = 0; i < MATRIX_SIZE; i++)
		{
			result[r][i] = stringToDouble(row[i], error);
			if (error)
			{
				return;
			}
		}
		++r;
	}
	return;
}




void multMatrix(const matrix& a, const matrix& b, matrix& result)
{
	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		for (int j = 0; j < MATRIX_SIZE; j++)
		{
			for (int k = 0; k < MATRIX_SIZE; k++)
			{
				result[i][j] += a[i][k] * b[k][j];
			}
		}
	}
}

void printMatrix(const matrix& a)
{
	//range base for 
	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		for (int j = 0; j < MATRIX_SIZE; j++)
		{
			cout << setprecision(3) << a[i][j];
			if (j < MATRIX_SIZE)
			{
				cout << " ";
			}
		}
		cout << '\n';
	}
}

int main(int argc, char* argv[])
{

	auto args = ParseArgs(argc, argv);
	if (args == nullopt)
	{
		cerr << "Invalid argument." << endl
			 << "Usage: multmatrix.exe <matrix file1> <matrix file2>" << endl;
		return ERROR;
	}
	//функция крытия файла и выдачи матрицы
	ifstream leftMatrix(args->leftMatrix);
	if (!leftMatrix.is_open())
	{
		cerr << "Input matrix file does not exist." << endl;
		return ERROR;
	}

	ifstream rightMatrix(args->rightMatrix);
	if (!rightMatrix.is_open())
	{
		cerr << "Input matrix file does not exist." << endl;
		return ERROR;
	}

	matrix a = {
		{ 0, 0, 0 },
		{ 0, 0, 0 },
		{ 0, 0, 0 }
	};
	matrix b = {
		{ 0, 0, 0 },
		{ 0, 0, 0 },
		{ 0, 0, 0 }
	};

	bool error = false;
	ParseMatrixFromFile(leftMatrix, a, error);
	if (error)
	{
		cerr << "Error during matrix parsing left." << endl;
		return ERROR;
	}
	ParseMatrixFromFile(rightMatrix, b, error);
	if (error)
	{
		cerr << "Error during matrix parsing." << endl;
		return ERROR;
	}

	matrix result = {
		{ 0, 0, 0 },
		{ 0, 0, 0 },
		{ 0, 0, 0 }
	};
	multMatrix(a, b, result);
	printMatrix(result);
}
