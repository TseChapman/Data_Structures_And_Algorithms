#include <iostream>
#include <chrono>

enum Color { RED, BLACK };

class RedBlackTree
{
public:
	RedBlackTree();

	void insert(const int& inputInteger);

	void inorderSearch(const int& searchInteger);

	const double getInputTime();

private:
	struct Node
	{
		int data;
		bool color;
		Node* left, * right, * parent;

		Node(int data)
		{
			this->data = data;
			left = right = parent = NULL;
			this->color = RED;
		}
	};

	Node* root;
	double inputTime;

	Node* BSTInsert(Node* rootPtr, Node* pt);
	void inorder(Node* root, const int& searchInteger, int& result, int& numberNodeSearched);
	void rotateLeft(Node*&, Node*&);
	void rotateRight(Node*&, Node*&);
	void fixViolation(Node*&, Node*&);
};
#pragma once
