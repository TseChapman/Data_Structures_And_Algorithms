// main.cpp
// Author:  Cheuk-Hang Tse
// Purpose: Reads a test image (hardcoded to "test2.gif"), then do the following steps:
//			1. Return a mirrorImage of the test image.
//          2. Subtract row mod 7 from the blue component of all pixel.
//          3. Add col mod 9 to the red component of all pixel.
//			4. Save the modified mirrorImage called "output.gif" and read the output.gif back into the code.
//			5. Then compare the mirrorImage to the image (outputImage) read from output.gif.
//			6. Output the number of differences to the console if the Images are not equal.

#include <iostream>
#include <algorithm>
#include "ImageClass.h"

int main()
{
	// Read a test image ("test2.gif").
	std::string inputFilename = "test2.gif";
	Image inputImage(inputFilename);

	// Check if it is a valid read.
	if (inputImage.getRows() == 0) {
		std::cout << "Unable to open file: " << inputFilename << std::endl;
		return -1;
	}

	// Output the number of rows and columns.
	std::cout << inputImage << std::endl;

	// Initialize Image mirroredImage.
	Image mirroredImage(inputImage.getRows(), inputImage.getColumns());

	// Create a mirrorImage and put into the Image class as coreImage.
	mirroredImage.createMirrorImage(inputImage.copy());

	// Next, do the following actions:
	// Subtract row mod 7 from the blue component of all pixel.
	// Add col mod 9 to the red component of all pixel.
	for (int row = 0; row < mirroredImage.getRows(); row++)
	{
		for (int col = 0; col < mirroredImage.getColumns(); col++)
		{
			// Subtract row mod 7 from the blue component of all pixel.
			mirroredImage.getPixel(row, col).blue = std::max(mirroredImage.getPixel(row, col).blue - (row % 7), 0);

			// Add col mod 9 to the red component of all pixel.
			mirroredImage.getPixel(row, col).red = std::min(mirroredImage.getPixel(row, col).red + (col % 9), 255);
		}
	}

	// Output a gif file with filename ("output.gif").
	std::string outputFilename = "output.gif";
	mirroredImage.outputImage(outputFilename);

	// Reintroduce the "output.gif" into the Image class.
	Image outputImage(outputFilename);
	if (outputImage.getRows() == 0) {
		std::cout << "Unable to open file: " << outputFilename << std::endl;
		return -1;
	}

	// Check if outputImage is equal to mirrorImage.
	if (outputImage == mirroredImage)
	{
		// If two images are equal, output the following text.
		std::cout << "The mirrorImage is exactly the same as the reinput image of mirrorImage." << std::endl;
	}
	else // If they are not equal:
	{
		// Count the number of different pixels.
		int numDifferences = 0;

		// Check to make sure they have the same size (equal rows and columns).
		if (mirroredImage.getRows() != outputImage.getRows() || mirroredImage.getColumns() != outputImage.getColumns())
		{
			// Output the following text when the rows or columns are not equal.
			std::cout << "Somehow the mirrorImage and the reinput mirrorImage does not have the same size" << std::endl;
		}
		else if (mirroredImage.getRows() == outputImage.getRows() && mirroredImage.getColumns() == outputImage.getColumns())
		{
			// if the size of two images are equal:
			for (int row = 0; row < mirroredImage.getRows(); row++) 
			{
				for (int col = 0; col < mirroredImage.getColumns(); col++) 
				{
					pixel inputLocatedPixel = mirroredImage.getPixel(row, col);
					pixel outputLocatedPixel = outputImage.getPixel(row,col);
					// Check if there are any difference in red, blue, or green, plus one to the number of different pixels.
					if (!outputImage.areEqualPixel(inputLocatedPixel, outputLocatedPixel)) 
					{
						numDifferences += 1;
					}
				}
			}

			// Output the total number of differences to the console.
			std::cout << "Number of different pixels: " << numDifferences << "." << std::endl;
		}
	}
	std::system("PAUSE");

	// Deallocate all Image.
	inputImage.~Image();
	outputImage.~Image();
	mirroredImage.~Image();

	// return 0 if successfully run.
	return 0;
}