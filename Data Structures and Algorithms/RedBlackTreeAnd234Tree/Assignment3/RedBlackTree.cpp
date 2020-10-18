#include "RedBlackTree.h"

RedBlackTree::RedBlackTree()
{
	root = NULL;
	inputTime = 0;
}

// public insert function
void RedBlackTree::insert(const int& inputInteger)
{
	// calculate time in nanosecond while inserting node
	auto startTime = std::chrono::high_resolution_clock::now();
	Node* pt = new Node(inputInteger);

	root = BSTInsert(root, pt);

	fixViolation(root, pt);
	auto endTime = std::chrono::high_resolution_clock::now();

	// adding up the input time
	inputTime += std::chrono::duration_cast<std::chrono::nanoseconds>(endTime-startTime).count();
}

// Searching an integer
void RedBlackTree::inorderSearch(const int& searchInteger)
{
	int numberNodeSearched = 0;
	int result = NULL;

	// calculate time while searching
	auto startTime = std::chrono::high_resolution_clock::now();
	inorder(root, searchInteger, result, numberNodeSearched);
	auto endTime = std::chrono::high_resolution_clock::now();

	// decide if the search is unsuccessful.
	if (result == NULL)
	{
		std::cout << "Red-Black Tree unsuccessfully find integer by searching " << numberNodeSearched << " nodes" << std::endl;
	}

	// output search time
	std::cout << "Red-Black Tree takes " << std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count() << " nano seconds to search" << std::endl;
}

// return the constant total input time
const double RedBlackTree::getInputTime()
{
	return inputTime;
}

// normal Binary Search Tree insert
RedBlackTree::Node* RedBlackTree::BSTInsert(RedBlackTree::Node* rootPtr, RedBlackTree::Node* pt)
{
	if (rootPtr == NULL)
		return pt;

	if (pt->data < rootPtr->data)
	{
		rootPtr->left = BSTInsert(rootPtr->left, pt);
		rootPtr->left->parent = rootPtr;
	}
	else if (pt->data > rootPtr->data)
	{
		rootPtr->right = BSTInsert(rootPtr->right, pt);
		rootPtr->right->parent = rootPtr;
	}

	// return the (unchanged) node pointer.
	return rootPtr;
}

// inorder searches
void RedBlackTree::inorder(RedBlackTree::Node* root, const int& searchInteger, int& result, int& numberNodeSearched)
{
	if (root == NULL) return;
	if (result != NULL) return;

	inorder(root->left, searchInteger, result, numberNodeSearched);
	numberNodeSearched++;
	if (root->data == searchInteger)
	{
		result = root->data;
		std::cout << "Red-Black Tree successfully find the integer by searching " << numberNodeSearched << " nodes." << std::endl;
	}
	inorder(root->right, searchInteger, result, numberNodeSearched);
}

// Red-Black Tree's rotate left function
void RedBlackTree::rotateLeft(RedBlackTree::Node*& root, RedBlackTree::Node*& pt)
{
	Node* pt_right = pt->right;

	pt->right = pt_right->left;

	if (pt->right != NULL)
		pt->right->parent = pt;

	pt_right->parent = pt->parent;

	if (pt->parent == NULL)
		root = pt_right;

	else if (pt == pt->parent->left)
		pt->parent->left = pt_right;

	else
		pt->parent->right = pt_right;

	pt_right->left = pt;
	pt->parent = pt_right;
}

// Red-Black Tree's rotate right function
void RedBlackTree::rotateRight(RedBlackTree::Node*& root, RedBlackTree::Node*& pt)
{
	Node* pt_left = pt->left;

	pt->left = pt_left->right;

	if (pt->left != NULL)
		pt->left->parent = pt;

	pt_left->parent = pt->parent;

	if (pt->parent == NULL)
		root = pt_left;

	else if (pt == pt->parent->left)
		pt->parent->left = pt_left;

	else
		pt->parent->right = pt_left;

	pt_left->right = pt;
	pt->parent = pt_left;
}

// This function fixes violation caused by BST insertion
void RedBlackTree::fixViolation(RedBlackTree::Node*& rootPtr, RedBlackTree::Node*& pt)
{
	Node* parent_pt = NULL;
	Node* grand_parent_pt = NULL;

	while ((pt != rootPtr) && (pt->color != BLACK) && (pt->parent != NULL && pt->parent->color == RED))
	{
		parent_pt = pt->parent;
		grand_parent_pt = pt->parent->parent;

		// Case A: Parent of pt is left child of Grand-parent of pt.
		if (parent_pt == grand_parent_pt->left)
		{
			Node* uncle_pt = grand_parent_pt->right;

			// Case 1: The uncle of pt is also red, only recoloring required.
			if (uncle_pt != NULL && uncle_pt->color == RED)
			{
				grand_parent_pt->color = RED;
				parent_pt->color = BLACK;
				uncle_pt->color = BLACK;
				pt = grand_parent_pt;
			}
			else
			{
				// Case 2: pt is right child of its parent, left-rotation required
				if (pt == parent_pt->right)
				{
					rotateLeft(rootPtr, parent_pt);
					pt = parent_pt;
					parent_pt = pt->parent;
				}

				// Case 3: pt is left child of its parent, right-rotation required
				rotateRight(rootPtr, grand_parent_pt);
				std::swap(parent_pt->color, grand_parent_pt->color);
				pt = parent_pt;
			}
		}

		// Case B: Parent of pt is right child of Grand-parent of pt.
		else
		{
			Node* uncle_pt = grand_parent_pt->left;

			// Case 1: The uncle of pt is also red, only recoloring required
			if ((uncle_pt != NULL) && (uncle_pt->color == RED))
			{
				grand_parent_pt->color = RED;
				parent_pt->color = BLACK;
				uncle_pt->color = BLACK;
				pt = grand_parent_pt;
			}
			else
			{
				// Case 2: pt is left child of its parent, right-rotation required
				if (pt == parent_pt->left)
				{
					rotateRight(rootPtr, parent_pt);
					pt = parent_pt;
					parent_pt = pt->parent;
				}

				// Case 3: pt is right child of its parent, left-rotation required
				rotateLeft(rootPtr, grand_parent_pt);
				std::swap(parent_pt->color, grand_parent_pt->color);
				pt = parent_pt;
			}
		}
	}

	rootPtr->color = BLACK;
}