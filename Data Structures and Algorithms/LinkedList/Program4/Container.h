/*
Container.h
Author: Cheuk-Hang Tse
Purpose: The header file for new Container class created for Program4
*/
#pragma once

#include <iostream>

class Container
{
public:
	// Constructor: construct an empty container.
	// Precondition: None.
	// Postcondition: Construct an empty container with head points to Node of row 0 and col 0.
	Container();

	// Copy Constructor: construct an exact copy of the input container.
	// Precondition: None.
	// Postcondition: Construct an exact copy of the input container and same head pointer.
	Container(const Container& in);

	// operator=: deallocate memory in original container and copy exactly from input container.
	// Precondition: *this is not equal to inputContainer.
	// Postcondition: The new container should be exactly the same as input container.
	const Container& operator=(const Container& in);

	// Deconstructor: deallocate memory in the container.
	// Precondition: None.
	// Postcondition: Deallocate all the memory in the container.
	~Container();

	// addPixel: add a node to the container based on the components of input pixel.
	// Precondition: Need to check if color component in input pixel is valid.
	// Postcondition: add the inputNode to the container based on the color component of inputPixel.
	void addPixel(const int red, const int green, const int blue, int row, int col);

	// merge: merge the mergeContainer to current container.
	// Precondition: None
	// Postcondition: connect head Node from mergeContainer to current container's nextContainer.
	const Container& merge(const Container& mergeCon);

	// averageColor: average the color in the linked list in head.
	// Precondition: visited is reset for all node.
	// Postcondition: average the color in the linked list and
	//				  return to the reference of red, green, blue. And number of node.
	int averageColor();

	// outputInformation: output the information of this container to the console.
	// Preconditions: Should not be called before outputing the image in driver.
	// Postconditions: output the information about number of segments, number of pixels, and 
	//                 average color for red, green, and blue of this container to the console.
	void outputInformation();

	// getPixelByLocation: output the RGB from location row and col.
	// Precondition: MUST BE VALID row AND col.
	// Postcondition: red, green, and blue will be changed based on the node info at location row and col.
	void getPixelByLocation(int row, int col, int& red, int& green, int &blue);
private:
	// Node structure: include information about position and color components
	struct Node
	{
		int red;
		int green;
		int blue;

		int row;
		int col;
		Node *next;
	};
	
	// deallocateList: deallocate the whole container.
	// Precondition: None.
	// Postconditions: the whole container is deallocated.
	void deallocateList();

	// copyList: copy the list from head to last by another container.
	// Precondition: None.
	// Postcondition: current container is an exact copy of input container.
	void copyList(const Container& in);

	// Store the start node on a group.
	Node *head = nullptr;

	// Store the last node on a group.
	Node *last = nullptr;

	int averageRed;
	int averageGreen;
	int averageBlue;

	int numSegment;
};