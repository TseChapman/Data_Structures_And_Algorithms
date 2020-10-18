#include <iostream>
#include <chrono>

class Tree234
{
public:
	Tree234();

	~Tree234();

	void insert(int& data);

	void search(int& key);

	const double getInputTime();
private:
	struct Node
	{
		int A, B, C;
		Node* less;
		Node* betweenAB;
		Node* betweenBC;
		Node* greater;

		Node(int data);

		Node(int data, Node* lessNode, Node* betweenABNode);

		Node(int dataA, int dataB, int dataC, Node* lessNode, Node* betweenABNode, Node* betweenBCNode, Node* greaterNode);

		// Helper function
		bool containsKey(int key);
		int findsKey(int key);
		void deleteData();
		bool isFull();
		bool isLeaf();
		int valueCount();
	};

	Node* root;
	double inputTime;

	void deleteTree(Node* pt);

	bool add(int& data);

	int find(int key, int& numNodeSearched);
	int find(int const& key, Node*& ptr, int& numNodeSearched);
};

#pragma once
