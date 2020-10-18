// -------------------Libraries------------------- //
#include <iostream>
#include <algorithm>
#include <cstdlib>

// -------------------Class------------------- //
class BST
{
public:
	// -------------------Public Methods------------------- //

	// Constructor: Construct an empty tree.
	// Precondition: None.
	// Postcondition: Construct an empty tree and all private variables is set to 0.
	BST();

	// Destructor: Deallocate the tree.
	// Precondition:
	// Postcondition: The tree is deallocated.
	~BST();

	// inputNumber: Input an integer into the tree.
	// Precondition: Integer is not already inside the tree.
	// Postcondition: the input integer is inserted into the tree.
	void inputNumber(int in);

	// findHeight: Find the smallest and highest height of the tree.
	// Precondition: None.
	// Postcondition: Set smallestBranchHeight and highestBranchHeight
	//                by the reseult from finding height.
	void findHeight();

	// findIsBalanced: Determine if the tree is balanced.
	// Precondition: None.
	// Postcondition: Set isTreeBalanced to true if tree is balanced.
	void findIsBalanced();

	// findIsComplete: Determine if the tree is completed.
	// Precondition: None.
	// Postcondition: Set isTreeComplete to true if tree is complete.
	void findIsComplete();

	// getSmallestHeight: Get smallestBranchHeight from the tree.
	// Precondition: Recommend calling findHeight before calling getSmallestHeight.
	// Postcondition: Return smallestBranchHeight as const int.
	const int getSmallestHeight();

	// getHighestHeight: Get highestBranchHeight from the tree.
	// Precondition: Recommend calling findHeight before calling getHighestHeight.
	// Postcondition: Return highestBranchHeight as const int.
	const int getHighestHeight();

	// getNumNode: Get the number of node inputed into the tree.
	// Precondition: None.
	// Postcondition: Return numNode as const int.
	const int getNumNode();

	// getIsBalanced: Get the result of whether the tree is balanced.
	// Precondition: Recommend calling findIsBalanced before calling getIsBalanced.
	// Postcondition: Return "True" if isTreeBalanced is true, else "False".
	const std::string getIsBalanced();

	// getIsCompleted: Get the result of whether the tree is completed.
	// Precondition: Recommend calling findIsCompleted before calling getIsCompleted.
	// Postcondition: Return "True" if isTreeCompleted is true, else "False".
	const std::string getIsCompleted();

private:
	// -------------------Private Variables------------------- //
	struct bstNode
	{
		int data;
		bstNode *left, *right;
	};

	bstNode* root;
	int numNode;
	int smallestBranchHeight;
	int highestbranchHeight;
	bool isTreeBalanced;
	bool isTreeCompleted;

	// -------------------Private Methods------------------- //

	// newNode: Create a new bstNode with input integer as data.
	// Precondition: None.
	// Postcondition: Return the bstNode pointer to the new bstNode 
	//				  with input integer as data.
	bstNode* newNode(int in);

	// insert: Insert an integer into the tree
	// Precondition: None.
	// Postcondition: An new node is inserted inside the tree.
	bstNode* insert(bstNode*& node, int in);

	// smallestHeight: Determine the smallest height for the branches.
	// Precondition: None.
	// Postcondition: Return the height for the smallest branch.
	int smallestHeight(bstNode*& root);

	// highestHeight: Determine the highest height for the branches.
	// Precondition: None.
	// Postcondition: Return the height for the highest for the branches.
	int highestHeight(bstNode*& root);

	// isBalanced: Determine if the tree is balanced.
	// Precondition: None.
	// Postcondition: Return true if the tree is balanced, else false.
	bool isBalanced(bstNode*& root);

	// isCompleted: Determining if the tree is completed.
	// Precondition: None.
	// Postcondition: Return true if the tree is completed, else false.
	bool isCompleted(bstNode*& root, unsigned int index, const unsigned int numberNodes);
};

#pragma once
