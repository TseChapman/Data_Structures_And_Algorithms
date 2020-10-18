#include <iostream>
#include <string>
#include <fstream>
#include "Hash.h"

void readFile(const std::string FILENAME);

void readFile(const std::string FILENAME)
{
	// Change the variable name and integer based on the hash table's size.
	const int hash10Size = 10;
	const int hash11Size = 11;
	const int hash23Size = 23;
	const int hash40Size = 40;

	std::ifstream file(FILENAME);
	std::string line;
	if (file.is_open())
	{
		// Initiallized 4 hash vector.
		Hash hash10(hash10Size);
		Hash hash11(hash11Size);
		Hash hash23(hash23Size);
		Hash hash40(hash40Size);

		// Read integer from file and put into the hashes.
		while (std::getline(file, line))
		{
			int inputNumber = std::stoi(line);

			hash10.insertData(inputNumber);
			hash11.insertData(inputNumber);
			hash23.insertData(inputNumber);
			hash40.insertData(inputNumber);
		}
		file.close();

		// output the four result for the hashes.
		hash10.outputInformation();
		hash11.outputInformation();
		hash23.outputInformation();
		hash40.outputInformation();

	}
	else
	{
		std::cout << "Unable to open file: " << FILENAME << std::endl;
	}
}

int main()
{
	const std::string FILENAME("CSS343_Final_Data.txt");
	readFile(FILENAME);
	return 0;
}