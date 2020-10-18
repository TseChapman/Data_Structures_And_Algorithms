#include <iostream>
#include <vector>
#include <algorithm>

class Hash
{
public:
	Hash(int size);

	void insertData(int inputData);

	void outputInformation();
private:
	struct Node
	{
		int data;
		Node* next;

		Node(int inputData);
	};

	int m_size;
	Node** hashTable;

	int maxCollision;
	int minCollision;
	int numEmptyElement;

	void checkEmptyElement();
};
#pragma once
