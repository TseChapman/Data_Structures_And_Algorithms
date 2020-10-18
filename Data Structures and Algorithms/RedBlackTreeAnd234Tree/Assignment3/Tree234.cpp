#include "Tree234.h"

Tree234::Tree234()
{
	root = NULL;
	inputTime = 0;
}

Tree234::~Tree234()
{
	deleteTree(root);
	root = NULL;
}

void Tree234::insert(int& data)
{
	auto startTime = std::chrono::high_resolution_clock::now();
	if (add(data)) {	}
	auto endTime = std::chrono::high_resolution_clock::now();

	inputTime += std::chrono::duration_cast<std::chrono::nanoseconds>(endTime-startTime).count();
}

void Tree234::search(int& key)
{
	auto startTime = std::chrono::high_resolution_clock::now();
	int numNodeSearched = 0;
	int result = find(key, numNodeSearched);
	auto endTime = std::chrono::high_resolution_clock::now();
	
	double searchTime = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();

	if (result == key)
	{
		std::cout << "2-3-4 Tree successfully find integer by searching " << numNodeSearched << " nodes." << std::endl;
	}
	else if (result == NULL)
	{
		std::cout << "2-3-4 Tree unsuccessfully find integer by searching " << numNodeSearched << " nodes." << std::endl;
	}
	std::cout << "2-3-4 Tree's search takes " << searchTime << " nano seconds to search" << std::endl;
}

const double Tree234::getInputTime()
{
	return inputTime;
}

// Constructor to initialize the node with one value. Other will be NULL
Tree234::Node::Node(int data)
{
	A = data;
	B = C = NULL;
	less = betweenAB = betweenBC = greater = NULL;
}

// Constructor to initialize the node with one value and two child pointers.
Tree234::Node::Node(int data, Node* lessNode, Node* betweenABNode)
{
	A = data;
	less = lessNode;
	betweenAB = betweenABNode;

	B = C = NULL;
	betweenBC = greater = NULL;
}

// Constructor for all initialized.
Tree234::Node::Node(int dataA, int dataB, int dataC, Node* lessNode, Node* betweenABNode, Node* betweenBCNode, Node* greaterNode)
{
	A = dataA;
	B = dataB;
	C = dataC;
	less = lessNode;
	betweenAB = betweenABNode;
	betweenBC = betweenBCNode;
	greater = greaterNode;
}

bool Tree234::Node::containsKey(int key)
{
	if (C && C == key) { return true; }
	if (B && B == key) { return true; }
	if (A == key) { return true; }
	return false;
}

int Tree234::Node::findsKey(int key)
{
	if (C && C == key) { return C; }
	if (B && B == key) { return B; }
	if (A == key) { return A; }
	return NULL;
}

void Tree234::Node::deleteData()
{
	if (A) { A = NULL; }
	if (B) { B = NULL; }
	if (C) { C = NULL; }
}

// return true if all data are not NULL, else false.
bool Tree234::Node::isFull()
{
	return (A != NULL && B != NULL && C != NULL);
}

// return true if all child pointers are NULL.
bool Tree234::Node::isLeaf()
{
	return (less == NULL && betweenAB == NULL && betweenBC == NULL && greater == NULL);
}

int Tree234::Node::valueCount()
{
	if (C) { return 3; }
	else if (B) { return 2; }
	else if (A) { return 1; }

	return 0; // empty node.
}

void Tree234::deleteTree(Tree234::Node* pt)
{
	if (pt)
	{
		pt->deleteData();
		deleteTree(pt->less);
		deleteTree(pt->betweenAB);
		deleteTree(pt->betweenBC);
		deleteTree(pt->greater);
		delete pt;
	}
}

bool Tree234::add(int& data)
{
	if (!root)
	{
		root = new Node(data);
		return true;
	}

	int key = data;

	Node* ptr = root; // traversing pointer
	Node* parent = ptr; // previous pointer

	while (ptr)
	{
		// Check for duplicates
		if (ptr->containsKey(key)) { return false; }

		// Case 1: there is 3 nodes, split it.
		if (ptr->isFull())
		{
			// Case 1a: if parent of node has 1 key
			if (1 == parent->valueCount())
			{
				if (parent->A < ptr->B)
				{
					parent->B = ptr->B;
					parent->betweenAB = new Node(ptr->A, ptr->less, ptr->betweenAB);
					parent->betweenBC = new Node(ptr->C, ptr->betweenBC, ptr->greater);
				}
				else
				{
					parent->B = parent->A;
					parent->betweenBC = parent->betweenAB;
					parent->A = ptr->B;
					parent->less = new Node(ptr->A, ptr->less, ptr->betweenAB);
					parent->betweenAB = new Node(ptr->C, ptr->betweenBC, ptr->greater);
				}

				delete ptr;

				if (key < parent->A)
					ptr = parent->less;
				else if (key < parent->B)
					ptr = parent->betweenAB;
				else if (key > parent->B)
					ptr = parent->betweenBC;
				else
				{
					std::cout << "Case 1a: duplicated" << std::endl;
					return false; // duplicated
				}
			} // end of Case 1a

			// Case 1b: if parent of node has 2 keys
			else if (2 == parent->valueCount())
			{
				if (parent->B < ptr->B)
				{
					parent->C = ptr->B;
					parent->betweenBC = new Node(ptr->A, ptr->less, ptr->betweenAB);
					parent->greater = new Node(ptr->C, ptr->betweenBC, ptr->greater);
				}
				else if (parent->A < ptr->B)
				{
					parent->C = parent->B;
					parent->greater = parent->betweenBC;
					parent->B = ptr->B;
					parent->betweenAB = new Node(ptr->A, ptr->less, ptr->betweenAB);
					parent->betweenBC = new Node(ptr->C, ptr->betweenBC, ptr->greater);
				}
				else
				{
					parent->C = parent->B;
					parent->greater = parent->betweenBC;
					parent->B = parent->A;
					parent->betweenBC = parent->betweenAB;
					parent->A = ptr->B;
					parent->less = new Node(ptr->A, ptr->less, ptr->betweenAB);
					parent->betweenAB = new Node(ptr->C, ptr->betweenBC, ptr->greater);
				}

				delete ptr;

				if (key < parent->A)
					ptr = parent->less;
				else if (key < parent->B)
					ptr = parent->betweenAB;
				else if (key < parent->C)
					ptr = parent->betweenBC;
				else if (key > parent->C)
					ptr = parent->greater;
				else
					return false; // duplicate
			} // end of Case 1b

			// Case 1c: if parent of node has 3 key
			else
			{
				root = new Node(ptr->B);
				root->less = new Node(ptr->A, ptr->less, ptr->betweenAB);
				root->betweenAB = new Node(ptr->C, ptr->betweenBC, ptr->greater);
				delete ptr;
				parent = root;

				if (key < root->A)
					ptr = root->less;
				else if (key > root->A)
					ptr = root->betweenAB;
				else
					return false; // duplicate
			} // end of Case 1c

		} // end of Case 1

		// Case 2: it is a leaf node
		if (ptr->isLeaf())
		{
			// Case 2a: has 1 key
			if (1 == ptr->valueCount())
			{
				if (key > ptr->A)
				{
					ptr->B = data;
					return true;
				}
				else if (key < ptr->A)
				{
					int temp = data;
					ptr->B = ptr->A;
					ptr->A = temp;
					return true;
				}
			} // end of Case 2a

			// Case 2b: Has 2 keys
			else if (2 == ptr->valueCount())
			{
				if (key > ptr->B)
				{
					ptr->C = data;
					return true;
				}
				else if (key > ptr->A)
				{
					int temp = data;
					ptr->C = ptr->B;
					ptr->B = temp;
					return true;
				}
				else if (key < ptr->A)
				{
					int temp = data;
					ptr->C = ptr->B;
					ptr->B = ptr->A;
					ptr->A = temp;
					return true;
				}
			} // end of Case 2b
		} // end of Case 2

		// Case 3: Not a leaf node
		else
		{
			// Assigns previous pointer
			parent = ptr;

			// Case 3a: Has 1 key
			if (1 == ptr->valueCount())
			{
				if (key < ptr->A)
					ptr = ptr->less;
				else
					ptr = ptr->betweenAB;
			}

			// Case 3b: Has 2 keys
			else if (2 == ptr->valueCount())
			{
				if (key < ptr->A)
					ptr = ptr->less;
				else if (key < ptr->B)
					ptr = ptr->betweenAB;
				else
					ptr = ptr->betweenBC;
			}
		} // end of Case 3

	} // end while

	return false; // should never get here
}

int Tree234::find(int key, int& numNodeSearched)
{
	Node* ptr = root;

	int result = ptr->findsKey(key);
	numNodeSearched++;

	if (result) 
	{ 
		return result; 
	}
	else
	{
		if (ptr->C && ptr->C < key)
		{
			return find(key, ptr->greater, numNodeSearched);
		}
		else if (ptr->B && ptr->B < key)
		{
			return find(key, ptr->betweenBC, numNodeSearched);
		}
		else if (ptr->A < key)
		{
			return find(key, ptr->betweenAB, numNodeSearched);
		}
		else
		{
			return find(key, ptr->less, numNodeSearched);
		}
	}
	return NULL;
}

int Tree234::find(int const& key, Node*& ptr, int& numNodeSearched)
{
	if (!ptr)
		return NULL;

	int result = ptr->findsKey(key);
	numNodeSearched++;
	if (result) 
	{ 
		return result;
	}
	else
	{
		if (ptr->C && ptr->C < key)
		{
			return find(key, ptr->greater, numNodeSearched);
		}
		else if (ptr->B && ptr->B < key)
		{
			return find(key, ptr->betweenBC, numNodeSearched);
		}
		else if (ptr->A < key)
		{
			return find(key, ptr->betweenAB, numNodeSearched);
		}
		else
		{
			return find(key, ptr->less, numNodeSearched);
		}
	}
}