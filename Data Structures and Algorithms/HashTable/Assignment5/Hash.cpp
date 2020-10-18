#include "Hash.h"

Hash::Hash(int size)
{
	m_size = size;
	hashTable = new Node* [m_size];
	for (int index = 0; index < m_size; index++)
	{
		hashTable[index] = NULL;
	}
	maxCollision = 0;
	minCollision = 0;
	numEmptyElement = 0;
}

void Hash::insertData(int inputData)
{
	// find the index of the inputData
	int index = inputData % m_size;
	Node* input = new Node(index);

	if (hashTable[index] == NULL)
	{
		hashTable[index] = input;
	}
	else
	{
		Node* cur = hashTable[index];
		int tempLength = 1; // currently have at least one node
		while (cur->next != NULL)
		{
			tempLength++;
			cur = cur->next;
		}
		cur->next = input;

		// Get the biggest number out of the tempLength and current max Collision.
		maxCollision = std::max(tempLength, maxCollision);

		// when it reach this point, there will be at least two integer colliding each other.
		minCollision = 1;
	}
}

void Hash::outputInformation()
{
	checkEmptyElement();
	std::cout << "=====================================================" << std::endl;
	std::cout << "Size of Hash Table: " << m_size << std::endl;
	std::cout << "The Minimum Number of Collision: " << minCollision << std::endl;
	std::cout << "The Maximum Number of Collision: " << maxCollision << std::endl;
	std::cout << "The Number of Array Elements with no Data: " << numEmptyElement << std::endl;
}

Hash::Node::Node(int inputData)
{
	data = inputData;
	next = nullptr;
}

void Hash::checkEmptyElement()
{
	int tempNumEmpty = 0;
	for (int i = 0; i < m_size; i++)
	{
		if (hashTable[i] == NULL)
		{
			tempNumEmpty++;
		}
	}

	if (tempNumEmpty > 0)
	{
		numEmptyElement = tempNumEmpty;
		minCollision = 0;
	}
}