// -------------------Libraries------------------- //
#include <iostream>
#include <fstream>
#include <string>
#include "BST.h"

// -------------------Declarations------------------- //
void outputInfo(BST& tree);
void readFiles(const int NUM_FILES, std::string fileName, std::string fileNumber[]);

// -------------------Methods------------------- //

// outputInfo: Output the information about the tree.
// Precondition: Finished calling all the required method, before calling outputInfo.
// Postcondition: Output the smallest and highest branch height, 
//                the number of nodes, is the tree balanced, and is the tree completed.
void outputInfo(BST& tree)
{
	std::cout << "Smallest branch height: " << tree.getSmallestHeight() << std::endl;
	std::cout << "Highest branch height: " << tree.getHighestHeight() << std::endl;
	std::cout << "Number of nodes: " << tree.getNumNode() << std::endl;
	std::cout << "Is balanced: " << tree.getIsBalanced() << std::endl;
	std::cout << "Is completed: " << tree.getIsCompleted() << std::endl;
}

// readFiles: read the input text files included in the program.
// Precondition: NUM_FILES must be positive, valid file name.
// Postcondition: Output the information of the tree created by the input text file.
void readFiles(const int NUM_FILES, std::string fileName, std::string fileNumber[])
{
	// Read through all files.
	for (int fileIndex = 0; fileIndex < NUM_FILES; fileIndex++)
	{
		std::ifstream file(fileName + fileNumber[fileIndex] + ".txt");

		std::string line;
		if (file.is_open()) // Able to open the file.
		{
			// Introduce dataset
			std::cout << "------------------------------" << std::endl;
			std::cout << "Successful to open file: " << fileName << fileNumber[fileIndex] << ".txt" << std::endl;

			// Initialize tree.
			BST tree;

			// Close the file until all lines are read.
			while (std::getline(file, line))
			{
				int inputNum = std::stoi(line);
				// Input the integer into BST
				tree.inputNumber(inputNum);
			}
			file.close();

			// Find the heights of the tree.
			tree.findHeight();

			// Determine if the tree is balanced.
			tree.findIsBalanced();

			// Determine if the tree is completed.
			tree.findIsComplete();

			// Output all the informations required for this tree.
			outputInfo(tree);
		}
		else // Unable to open the file.
		{
			std::cout << "Unable to open file: " << fileName << fileNumber[fileIndex] << ".txt" << std::endl;
		}
	}
}

// -------------------Driver------------------- //
int main()
{
	// Define constants and variables.
	const int NUM_FILES = 3; // change the number when more or less file will be inputed.
	std::string fileName("CSS343_A1_");
	// Add or delete based on the number of files.
	std::string fileNumber[NUM_FILES] = { "F1", "F2", "F3"};
	
	readFiles(NUM_FILES, fileName, fileNumber);
	return 0;
}