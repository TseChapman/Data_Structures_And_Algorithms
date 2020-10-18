/*
	Container.cpp
	Author: Cheuk-Hang Tse
	Purpose: Contain functions implementation for the Container class
*/

#include <iostream>
#include "Container.h"

// Constructor: construct an empty container.
// Precondition: None.
// Postcondition: Construct an empty container with head points to Node of row 0 and col 0.
Container::Container()
{
	averageRed = 0;
	averageGreen = 0;
	averageBlue = 0;

	numSegment = 0;
}

// Copy Constructor: construct an exact copy of the input container.
// Precondition: None.
// Postcondition: Construct an exact copy of the input container and same head pointer.
Container::Container(const Container& in)
{
	copyList(in);

	averageRed = in.averageRed;
	averageGreen = in.averageGreen;
	averageBlue = in.averageBlue;

	numSegment = in.numSegment;
}

// operator=: deallocate memory in original container and copy exactly from input container.
// Precondition: *this is not equal to inputContainer.
// Postcondition: The new container should be exactly the same as input container.
const Container& Container::operator=(const Container& in)
{
	if (this != &in)
	{
		// Deallocate data in this list.
		deallocateList();

		// copy data from in list.
		copyList(in);

		averageRed = in.averageRed;
		averageGreen = in.averageGreen;
		averageBlue = in.averageBlue;

		numSegment = in.numSegment;
	}

	return *this;
}

// Deconstructor: deallocate memory in the container.
// Precondition: None.
// Postcondition: Deallocate all the memory in the container.
Container::~Container()
{
	deallocateList();
}

// addPixel: add a node to the container based on the components of input pixel.
// Precondition: Need to check if color component in input pixel is valid.
// Postcondition: add the inputNode to the container based on the color component of inputPixel.
void Container::addPixel(const int red, const int green, const int blue, int row, int col)
{
	// std::cout << "Add pixel in row: " << row << " col: " << col << std::endl;
	//clang++ -o main main.cpp
	//./main

	Node *temp = new Node();

	temp->red = red;
	temp->green = green;
	temp->blue = blue;
	temp->row = row;
	temp->col = col;
	temp->next = nullptr;

	if (head == nullptr)
	{
		head = temp;
		last = temp;
	}
	else
	{
		Node *cur = last;
		cur->next = temp;
		last = cur->next;
	}
}

// merge: merge the mergeContainer to current container.
// Precondition: None
// Postcondition: connect head Node from mergeContainer to current container's nextContainer.
const Container& Container::merge(const Container& mergeCon)
{
	if (mergeCon.head != nullptr)
	{
		Node *lastNode = nullptr;
		if (this->head != nullptr)
		{
			this->last->next = new Node();
			this->last = this->last->next;
			lastNode = this->last;
		}
		else
		{
			this->head = new Node();
			lastNode = this->head;
		}
		
		lastNode->row = mergeCon.head->row;
		lastNode->col = mergeCon.head->col;
		lastNode->red = mergeCon.head->red;
		lastNode->green = mergeCon.head->green;
		lastNode->blue = mergeCon.head->blue;
		lastNode->next = nullptr;

		for (Node *cur = mergeCon.head->next; cur != nullptr; cur = cur->next)
		{
			lastNode->next = new Node();
			lastNode = lastNode->next;

			lastNode->row = cur->row;
			lastNode->col = cur->col;
			lastNode->red = cur->red;
			lastNode->green = cur->green;
			lastNode->blue = cur->blue;
			lastNode->next = nullptr;
		}
		this->last = lastNode;
		// Two while loops:
		// first, traverse the list to the last node.
		// second, add node from mergeCon to this container. 
		this->numSegment++;
	}
	return *this;
}

// averageColor: average the color in the linked list in head.
// Precondition: None.
// Postcondition: average the color in the linked list and
//				  return to the reference of red, green, blue. And number of node.
int Container::averageColor()
{
	int red = 0;
	int green = 0;
	int blue = 0;

	int numNode = (head != nullptr)? 0 : 1;

	if (head == nullptr)
	{
		averageRed = 0;
		averageGreen = 0;
		averageBlue = 0;
		return 0;
	}

	for (Node *cur = head; cur != nullptr; cur = cur->next)
	{
		red += cur->red;
		green += cur->green;
		blue += cur->blue;
		numNode++;
	}

	red /= numNode;
	green /= numNode;
	blue /= numNode;

	for (Node *cur = head; cur != nullptr; cur = cur->next)
	{
		cur->red = red;
		cur->green = green;
		cur->blue = blue;
	}

	averageRed = red;
	averageGreen = green;
	averageBlue = blue;
	return numNode;
}

// outputInformation: output the information of this container to the console.
// Preconditions: Should not be called before outputing the image in driver.
// Postconditions: output the information about number of segments, number of pixels, and 
//                 average color for red, green, and blue of this container to the console.
void Container::outputInformation()
{
	// Output the number of segments.
	std::cout << "Total number of segment found: " << numSegment << std::endl;

	// Output number of pixel/node(s).
	int totalNumNode = averageColor();
	std::cout << "Total number of pixel/node(s) in this container is: " << totalNumNode << std::endl;
	std::cout << "Average color of this container: red = " << averageRed << ", green = " << averageGreen << ", blue = " << averageBlue << std::endl;
}

// getPixelByLocation: output the RGB from location row and col.
// Precondition: MUST BE VALID row AND col.
// Postcondition: red, green, and blue will be changed based on the node info at location row and col.
void Container::getPixelByLocation(int row, int col, int& red, int& green, int &blue)
{
	if (head == nullptr)
	{
		red = 0;
		green = 0;
		blue = 0;
		return;
	}
	Node *cur = head;
	while (cur != nullptr)
	{
		if (cur->row == row && cur->col == col)
		{
			red = cur->red;
			green = cur->green;
			blue = cur->blue;
			break;
		}
		cur = cur->next;
	}
}

// deallocateList: deallocate the whole container.
// Precondition: None.
// Postconditions: the whole container is deallocated.
void Container::deallocateList()
{
	if (last != nullptr)
	{
		last = nullptr;
	}
	while (head != nullptr)
	{
		Node *temp = head;
		head = head->next;
		delete temp;
	}
}

// copyList: copy the list from head to last by another container.
// Precondition: None.
// Postcondition: current container is an exact copy of input container.
void Container::copyList(const Container& in)
{
	if (in.head == nullptr)
	{
		head = nullptr;
		last = nullptr;
	}
	else
	{
		Node *temp = new Node();
		temp->row = in.head->row;
		temp->col = in.head->col;
		temp->red = in.head->red;
		temp->green = in.head->green;
		temp->blue = in.head->blue;
		temp->next = nullptr;

		head = temp;

		Node *currentCur = head;
		for (Node *cur = in.head->next; cur != nullptr; cur = cur->next)
		{
			currentCur->next = new Node();
			currentCur = currentCur->next;

			currentCur->row = cur->row;
			currentCur->col = cur->col; 
			currentCur->red = cur->red;
			currentCur->green = cur->green;
			currentCur->blue = cur->blue;
			currentCur->next = nullptr;
		}
		last = currentCur;
	}
}