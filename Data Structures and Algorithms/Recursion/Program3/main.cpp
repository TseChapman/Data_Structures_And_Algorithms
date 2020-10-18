/*
main.cpp

Author: Cheuk-Hang Tse
Purpose: Create a Recursion Image using the ImageClass, Rectangle class, and recursion function.
*/

#include <iostream>
#include "Rectangle.h"
#include "ImageLib.h"
#include "ImageClass.h"

// Declaration for the following functions
int addColorComponent(ImageClass& in, int inputRow, int inputCol, int& red, int& blue, int& green);
const pixel determineColorPixel(ImageClass& in, int row, int col, Rectangle& previousQuadTwo);
const pixel determineFlippedColorPixel(ImageClass& in, int row, int col, Rectangle& previousQuadTwo);
void createRecursionImage(ImageClass& recurImage,ImageClass& in, Rectangle& rec, Rectangle& previousQuadTwo);

// main: Input a image from inputFileName, then
//       create a recursion Image using inputImage.
//		 At last, output the recured Image by the filename outputFileName.
int main()
{ 
	// Input the image with inputFileName.
	std::string inputFileName = "test3.gif";
	ImageClass inputImage(inputFileName);

	// Construct recursionImage by inputImage's parameters.
	ImageClass recursionImage(inputImage.getRows(), inputImage.getColumns());
	const int REC_FIRST_ROW = 0;
	const int REC_FIRST_COL = 0;
	Rectangle rec(REC_FIRST_ROW, REC_FIRST_COL, inputImage.getRows(), inputImage.getColumns());

	// create recursion image.
	createRecursionImage(recursionImage, inputImage, rec, rec);

	// output the recured Image by outputFileName.
	std::string outputFileName = "output.gif";
	recursionImage.outputImage(outputFileName);

	// Tell the user, recursion is finished.
	std::cout << "Recursion is finished" << std::endl;
	system("PAUSE");
	return 0;
}

// addColorComponent: add the pixel components: red, blue, and green. Return one if adding is successful.
//                    by the color components from pixel from input at location (inputRow, inputCol).
// Preconditions: It better to pass in valid inputRow and inputCol.
// Postconditions: return one if pixel components: red, blue, and green are added by
//				   the color components from pixel from input at location (inputRow, inputCol).
int addColorComponent(ImageClass& in, int inputRow, int inputCol, int& red, int& blue, int& green)
{
	// if inputRow and inputCol is valid in inputImage, add color component and return one.
	if (inputRow < in.getRows() && inputRow >= 0 && inputCol < in.getColumns() && inputCol >= 0)
	{
		red += in.getPixel(inputRow, inputCol).red;
		blue += in.getPixel(inputRow, inputCol).blue;
		green += in.getPixel(inputRow, inputCol).green;
		return 1;
	}
	else
	{
		return 0;
	}
}

// determineColorPixel: determine the shrinked pixel from previousQuad at location row and col.
//						Then return determinedPixel.
// Preconditions: row and col exist in input.
// Preconditions: return the determinedPixel from the shrinked pixel from previousQuad at location row and col.
const pixel determineColorPixel(ImageClass& in, int row, int col, Rectangle& previousQuadTwo)
{
	// Initialize color component.
	int red = 0;
	int blue = 0;
	int green = 0;

	// Number of pixels are available to add color component.
	int numPixelAvailable = 0;
	
	// simpflied the row and col to pass into addColorComponent function.
	int inputRow = (2 * row + previousQuadTwo.getFirstRow());
	int inputCol = (2 * col + previousQuadTwo.getFirstCol());

	// Add color components in order of the formula.
	// addColorComponent will return 1 if successfully add color components, or else return 0.
	numPixelAvailable = addColorComponent(in, inputRow, inputCol, red, blue, green);
	numPixelAvailable += addColorComponent(in, inputRow + 1, inputCol, red, blue, green);
	numPixelAvailable += addColorComponent(in, inputRow, inputCol + 1, red, blue, green);
	numPixelAvailable += addColorComponent(in, inputRow + 1, inputCol + 1, red, blue, green);

	// divide the color component by the number of pixels 
	// are available to add color component to average the color components.
	red /= numPixelAvailable;
	green /= numPixelAvailable;
	blue /= numPixelAvailable;

	// Create determinedPixel and pass in the averaged color components
	pixel determinedPixel;
	determinedPixel.red = red;
	determinedPixel.blue = blue;
	determinedPixel.green = green;

	// return the final determinedPixel.
	return determinedPixel;
}

// determineFlippedColorPixel: determine the flipped and shrinked pixel in inputImage
//							   from previousQuad at location row and col. Then return determinedPixel.
// Preconditions: row and col exist in input.
// Preconditions: return the determinedPixel from the flipped and shrinked pixel in inputImage
//				  from previousQuad at location row and col.
const pixel determineFlippedColorPixel(ImageClass& in, int row, int col,Rectangle& previousQuadTwo)
{
	// Initialize color component.
	int red = 0;
	int blue = 0;
	int green = 0;

	// Number of pixels are available to add color component.
	int numPixelAvailable = 0;

	// simpflied the row and col to pass into addColorComponent function.
	const int OLD_QUADRANT_MAX_ROW = (previousQuadTwo.getNumRows() + previousQuadTwo.getFirstRow());
	const int OLD_QUADRANT_MAX_COL = (previousQuadTwo.getNumCols() + previousQuadTwo.getFirstCol());
	int inputRow = OLD_QUADRANT_MAX_ROW - (2 * row);
	int inputCol = OLD_QUADRANT_MAX_COL - (2 * col);

	// Add color components in order of the formula.
	// addColorComponent will return 1 if successfully add color components, or else return 0.
	numPixelAvailable = addColorComponent(in, inputRow, inputCol, red, blue, green);
	numPixelAvailable += addColorComponent(in, (inputRow - 1), inputCol, red, blue, green);
	numPixelAvailable += addColorComponent(in, inputRow, (inputCol - 1), red, blue, green);
	numPixelAvailable += addColorComponent(in, (inputRow - 1), (inputCol - 1), red, blue, green);

	// divide the color component by the number of pixels 
	// are available to add color component to average the color components.
	red /= numPixelAvailable;
	green /= numPixelAvailable;
	blue /= numPixelAvailable;

	// Create determinedPixel and pass in the averaged color components
	pixel determinedPixel;
	determinedPixel.red = red;
	determinedPixel.blue = blue;
	determinedPixel.green = green;

	// return the final determinedPixel.
	return determinedPixel;
}

// createRecursionImage: create and recure Image until the rec gets too small to continue.
// Preconditions: when call this function, initialize previousQuadTwo equal to rec.
// Postconditions: modify the recurImage from the inputImage by recursion.
void createRecursionImage(ImageClass& recurImage, ImageClass& in, Rectangle& rec, Rectangle& previousQuadTwo)
{
	// Return if the rec gets too small like the width and length are one pixel.
	if (rec.getNumRows() <= 1 && rec.getNumCols() <= 1)
	{
		return;
	}

	// Divide the rec into four quadrants:
	// quadrantTwo: Upper-Left rectangle
	Rectangle quadrantTwo(rec.getFirstRow(), 
						  rec.getFirstCol(), 
						  rec.getNumRows() / 2 + rec.getNumRows() % 2, 
						  rec.getNumCols() / 2 + rec.getNumCols() % 2);

	// quadrantOne: Upper-Right rectangle
	Rectangle quadrantOne(quadrantTwo.getNumRows() + quadrantTwo.getFirstRow(),
						  quadrantTwo.getFirstCol(), 
						  rec.getNumRows() - quadrantTwo.getNumRows(),
						  quadrantTwo.getNumCols());

	// quadrantThree: Lower-Left rectangle
	Rectangle quadrantThree(quadrantTwo.getFirstRow(),
							quadrantTwo.getNumCols() + quadrantTwo.getFirstCol(),
							quadrantTwo.getNumRows(),
							rec.getNumCols() - quadrantTwo.getNumCols());

	// quadrantFour: Lower-Right rectangle
	Rectangle quadrantFour(quadrantTwo.getNumRows() + quadrantTwo.getFirstRow(),
						   quadrantTwo.getNumCols() + quadrantTwo.getFirstCol(),
						   rec.getNumRows() - quadrantTwo.getNumRows(),
						   rec.getNumCols() - quadrantTwo.getNumCols());

	// Increase factor of row
	int inputRow = 0;

	// Modifies pixels in quadrantTwo to become a shrinked version of inputImage
	for (int row = quadrantTwo.getFirstRow(); row < quadrantTwo.getFirstRow() + quadrantTwo.getNumRows(); row++)
	{
		// Increase factor of col
		int inputCol = 0;

		for (int col = quadrantTwo.getFirstCol(); col < quadrantTwo.getFirstCol() + quadrantTwo.getNumCols(); col++)
		{
			// if this is not the initial call.
			if (rec.getNumRows() != in.getRows() && rec.getNumCols() != in.getColumns())
			{
				recurImage.setPixel(row, col, determineColorPixel(recurImage, inputRow, inputCol, previousQuadTwo));
			}
			else
			{
				recurImage.setPixel(row, col, determineColorPixel(in, inputRow, inputCol, previousQuadTwo));
			}
			inputCol++;
		}
		inputRow++;
	}

	// Increase factor of row
	inputRow = 0;

	// Modifies pixels in quadrantfour to become a flipped and shrinked version of inputImage
	for (int row = quadrantFour.getFirstRow(); row < quadrantFour.getFirstRow() + quadrantFour.getNumRows(); row++)
	{
		// Increase factor of col
		int inputCol = 0;

		for (int col = quadrantFour.getFirstCol(); col < quadrantFour.getFirstCol() + quadrantFour.getNumCols(); col++)
		{
			// if this is not the initial call.
			if (rec.getNumRows() != in.getRows() && rec.getNumCols() != in.getColumns())
			{
				recurImage.setPixel(row, col, determineFlippedColorPixel(recurImage,inputRow,inputCol, previousQuadTwo));
			}
			else
			{
				recurImage.setPixel(row, col, determineFlippedColorPixel(in, inputRow, inputCol, previousQuadTwo));
			}
			inputCol++;
		}
		inputRow++;
	}

	// recursion for quadrantOne.
	createRecursionImage(recurImage, recurImage, quadrantOne, quadrantTwo);

	// recursion for quadrantThree.
	createRecursionImage(recurImage, recurImage, quadrantThree, quadrantTwo);

}