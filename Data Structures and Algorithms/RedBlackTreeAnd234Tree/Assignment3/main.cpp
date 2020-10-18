#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "RedBlackTree.h"
#include "Tree234.h"

#define inputAction 0
#define searchAction 1

void printInputResult(RedBlackTree& RBTree, Tree234& tree234);
int readFiles(std::vector < std::string> fileNames);

void printInputResult(RedBlackTree& RBTree, Tree234& tree234)
{
	std::cout << "LOADING RESULT:" << std::endl;
	std::cout << "=======================================================================" << std::endl;
	std::cout << "Red-Black Tree input time: " << RBTree.getInputTime() << " nano seconds" << std::endl;
	std::cout << "2-3-4 Tree input time: " << tree234.getInputTime() << " nano seconds" << std::endl;
	if (RBTree.getInputTime() < tree234.getInputTime())
		std::cout << "Conclusion: Red-Black Tree has lower input time than 2-3-4 Tree by " << (tree234.getInputTime() - RBTree.getInputTime()) << " nano seconds" << std::endl;
	else
		std::cout << "Conclusion: 2-3-4 Tree has lower input time than Red-Black Tree." << (RBTree.getInputTime() - tree234.getInputTime()) << " nano seconds" << std::endl;
	std::cout << "=======================================================================" << std::endl;
}

int readFiles(std::vector<std::string> fileNames)
{
	int isSuccessful = 1; // Determine if files are loaded.

	// Initialize two trees.
	RedBlackTree RBTree;
	Tree234 tree234;
	// load the input file.
	std::ifstream file(fileNames[inputAction]);
	if (file.is_open())
	{
		std::string line;

		// get lines and insert into both tree.
		while (std::getline(file, line))
		{
			// Convert into integer type
			int inputInteger = std::stoi(line);
			RBTree.insert(inputInteger);
			tree234.insert(inputInteger);
		}
		file.close();
		isSuccessful = 0;
		printInputResult(RBTree, tree234);
	}
	else 
	{
		// Unable to open the file.
		std::cout << "File: " << fileNames[inputAction] << " is unable to open" << std::endl;
		return isSuccessful;
	}

	// Search integer in both tree.
	std::fstream file2(fileNames[searchAction]);
	if (file2.is_open())
	{
		std::cout << "SEARCHING RESULT:" << std::endl;
		std::string line2;

		// get lines and search from both tree
		while (std::getline(file2, line2))
		{
			// Convert into integer type
			int searchInteger = std::stoi(line2);
			// print the result as it searches
			std::cout << "=======================================================================" << std::endl;
			std::cout << "Search for " << searchInteger << std::endl;
			RBTree.inorderSearch(searchInteger);
			tree234.search(searchInteger);
			std::cout << "=======================================================================" << std::endl;
		}
		file2.close();
		isSuccessful = 0;
	}
	else
	{
		// Unable to open the file
		std::cout << "File: " << fileNames[searchAction] << " is unable to open" << std::endl;
		return isSuccessful;
	}

	// print result

	return isSuccessful;
}

int main()
{
	std::vector<std::string> fileNames = {"B_Tree_Input.txt" , "B_Tree_Searches.txt"};
	int isSuccessful = readFiles(fileNames);
	return isSuccessful;
}