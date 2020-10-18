/*
main.cpp
Author: Cheuk-Hang Tse
Purpose: Implement the driver function for finding pixel that is close to the seed,
		 modify the container by merging segmented pixels,
		 and modify the output Image by setting the pixels information by container.
*/
#include <iostream>
#include <cstdlib>
#include "ImageLib.h"
#include "ImageClass.h"
#include "Container.h"

// Define black's RGB value, which is 0.
static const int BLACK_COLOR_COMP = 0;

// Declaration for the functions in this driver.
void findMatch(ImageClass& in, Container& con, const pixel& seed, int row, int col);
void modifyContainerByImage(ImageClass& outputImage, Container& con);
void modifyImageByContainer(ImageClass& outputImage, Container& con);

// findMatch: a recursive function that deside if the pixel is close to the seed.
// Precondition: seed is not black.
// Postconditions: When done recuring, the con will be filled with pixels
//				   that are close to the seed pixel.
void findMatch(ImageClass& in, Container& con, const pixel& seed, int row, int col)
{
	int red = 0;
	int blue = 0;
	int green = 0;
	// Base case:
	// if row or col is out of bounds then return.
	if (in.getPixel(row, col, red, green, blue) == false)
	{
		return;
	}
	// if color is black return.
	if ((red == BLACK_COLOR_COMP) &&
		(green == BLACK_COLOR_COMP) &&
		(blue == BLACK_COLOR_COMP))
	{
		return;
	}
	// if color is average is bigger than 100, return.
	if ((abs((float)seed.red - (float)red) +
		 abs((float)seed.green - (float)green) +
		 abs((float)seed.blue - (float)blue)) >= 100)
	{
		return;
	}

	// Recursion case:
	// add the pixel to container.
	con.addPixel(red, green, blue, row, col);
	// paint the pixel in Image to black.
	in.setPixel(row, col, BLACK_COLOR_COMP, BLACK_COLOR_COMP, BLACK_COLOR_COMP);
	// recure neighbors: up, down, left, and right.
	findMatch(in, con, seed, row + 1, col);
	findMatch(in, con, seed, row, col + 1);
	findMatch(in, con, seed, row - 1, col);
	findMatch(in, con, seed, row, col - 1);
}

// modifyContainerByImage: fill the main container by all segmented merge container.
// Preconditions: not an empty image.
// Postconditions: fill the main container by one or more merge container that 
//				   each containe a segmented pixel group.
void modifyContainerByImage(ImageClass& outputImage, Container& con)
{
	for (int row = 0; row < outputImage.getRows(); row++)
	{
		for (int col = 0; col < outputImage.getColumns(); col++)
		{
			int red = 0;
			int green = 0;
			int blue = 0;
			if (outputImage.getPixel(row, col, red, green, blue))
			{
				if ((red == BLACK_COLOR_COMP) &&
					(green == BLACK_COLOR_COMP) &&
					(blue == BLACK_COLOR_COMP))
				{
					continue;
				}
				// create merge con and seed pixel base on current pixel at row and col.
				Container mergeCon;
				pixel seed;
				seed.red = red;
				seed.green = green;
				seed.blue = blue;
				// find pixel that matches the seed.
				findMatch(outputImage, mergeCon, seed, row, col);

				// average the color in mergeCon
				mergeCon.averageColor();
				// merge the mergeCon to con.
				con.merge(mergeCon);
			}
		}
	}
}

// modifyImageByContainer: color the pixels in output Image by the container.
// Precondition: This function should not be called before modifyContainerByImage.
// Postconditions: The output Image will be modified by the pixel info from the main container.
void modifyImageByContainer(ImageClass& outputImage, Container& con)
{
	// Traverse the linked list and input the information: row, col, RBG, to the outputImage.
	for (int row = 0; row < outputImage.getRows(); row++)
	{
		for (int col = 0; col < outputImage.getColumns(); col++)
		{
			int red = 0;
			int green = 0;
			int blue = 0;
			con.getPixelByLocation(row, col, red, green, blue);

			outputImage.setPixel(row, col, red, green, blue);
		}
	}
}

// main: input image and modifies the container by the image.
//		 then paint an output image by the pixel info from container.
//		 At last, output the output image.
// Preconditions: None.
// Postconditions: A modified image is outputed based 
//				   on the segmentation of input image.
int main()
{
	// Input the image with inputFileName.
	std::string inputFileName("test4.gif");
	ImageClass inputImage(inputFileName);
	if (inputImage.getRows() == 0 && inputImage.getColumns() == 0)
	{
		return -1;
	}

	ImageClass outputImage(inputImage);
	Container con;

	modifyContainerByImage(outputImage, con);

	modifyImageByContainer(outputImage, con);

	std::string outputFilename("output.gif");
	outputImage.outputImage(outputFilename);

	con.outputInformation();
	system("PAUSE");
	return 0;
}
