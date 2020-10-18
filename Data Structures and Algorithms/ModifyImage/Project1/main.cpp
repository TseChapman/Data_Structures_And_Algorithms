// main.cpp
// Author:  Cheuk-Hang Tse
// Purpose: Reads a test image (hardcoded to "test1.gif"), then do the following steps:
//          1. Subtract row mod 7 from the blue component of the pixel.
//          2. Add col mod 9 to the red component of the pixel.
//			3. After 1-3 steps, create a new image that is the mirror-image of the image.
//			4. Save the new image called "output.gif" and read the output.gif back into the code.
//			5. Then compare the new image (input) to the image (output) read from output.gif.
//			6. Output the number of differences to the console.

#include "ImageLib.h"
#include <iostream>
#include <algorithm>

// forward declarations
void subtractBlueComponent(int row, pixel& p);
void addRedComponent(int col, pixel& p);
void updateImage(image in);
void createMirrorImage(image in);
bool areEqual(const pixel& one, const pixel& two);
void compareImages(image in, image out);

// main()
// Preconditions: test.gif exists and is a valid GIF image
// Postconditions: output.gif will be written and it will contain
//				   a photoNewIamge and createMirrorImage of the image in test.gif
//				   then read the output.gif back into the code and
//				   compare the image (input) to the image (output) read from output.gif.
int main() {
	// Read test image from file
	std::string inputFileName ("test1.gif");
	image input = ReadGIF(inputFileName);
	if (input.rows == 0) {
		std::cout << "Unable to open file: " << inputFileName << std::endl;
		return -1;
	}

	// Create an image with:
	// 1. Subtract row mod 7 from the blue component of the pixel.
	// 2. Add col mod 9 to the red component of the pixel.
	updateImage(input);

	// Mirror an image (Left to Right).
	createMirrorImage(input);

	// Output results
	std::cout << "The dimensions of the image are: " << input.rows << " rows by " << input.cols << " columns." << std::endl;
	std::string outputFileName ("output.gif");
	WriteGIF(outputFileName, input);

	// Read output image from file.
	image output = ReadGIF(outputFileName);
	if (output.rows == 0) {
		std::cout << "Uable to open file: " << outputFileName << std::endl;
		return -1;
	}

	// Compare the new image (input) to the image (output) read from output.gif.
	compareImages(input, output);

	// Wait for user input before exiting
	std::system("PAUSE");
	DeallocateImage(input);

	return 0;
}

// updateImage: updates the input image with the following operations:
//				1. Subtract row mod 7 from the blue component of the pixel.
//				2. Add col mod 9 to the red component of the pixel.
//			    3. Green componenet should be unchanged.
// Preconditions: the input image (in) has in.rows * in.cols pixels allocated.
// Postconditions: the input image is modified such that the image has undergone the above operations.
void updateImage(image in) {
	for (int row = 0; row < in.rows; row++) {
		for (int col = 0; col < in.cols; col++) {
			// Subtract row mod 7 from the blue component of the pixel.
			subtractBlueComponent(row, in.pixels[row][col]);
			
			// Add col mod 9 to the red component of the pixel.
			addRedComponent(col, in.pixels[row][col]);
		}
	}
}

// subtractBlueComponent: Subtract the blue component of a single pixel by row mod 7.
// Preconditions: None
// Postconditions: Blue component of the input pixel is subtracted by row mod 7.
void subtractBlueComponent(int row, pixel& p) {
	p.blue = std::max(p.blue - (row % 7), 0);
}


// addRedComponent: Add the red component of a single pixel by col mod 9.
// Preconditions: None
// Postconditions: Red component of the input pixel is add by col mod 9.
void addRedComponent(int col, pixel& p) {
	p.red = std::min(p.red + (col % 9), 255);
}

// createMirrorImage: Modifies the input image to create a mirrored image.
// Preconditions: The input image (in) has in.rows * in.cols pixels allocated.
// Postconditions: The input image is modified such that the image is mirrored.
void createMirrorImage(image in) {
	for (int row = 0; row < in.rows; row++) {
		for (int col = 0; col < in.cols/2; col++) {
			int mirrorCol = in.cols - col - 1;
			pixel temp = in.pixels[row][col];
			in.pixels[row][col] = in.pixels[row][mirrorCol];
			in.pixels[row][mirrorCol] = temp;
		}
	}
}

// areEqual: return true if all color components of two pixels are equal.
// Preconditions: None.
// Postconditions: return a boolean about whether two pixels have equal color component.
bool areEqual(const pixel& one, const pixel& two) {
	return ((one.blue == two.blue) && (one.red == two.red) && (one.green == two.green));
}

// compareImages: Compare all pixels from input image and output image.
// Precondition: Both input image and output image must have the same amount of rows and columns.
// Postconditions: Output a total number of image differences in the console.
void compareImages(image in, image out) {
	// Check if both images must have the same amount of rows and columns.
	if (in.rows != out.rows || in.cols != out.cols) {
		// Error message: two images did not match in the same size.
		std::cout << "compareImages: Error in getting same number of rows and cols from both input image and output image" << std::endl;
		return;
	}

	int numDifferences = 0;
	for (int row = 0; row < in.rows; row++) {
		for (int col = 0; col < in.cols; col++) {
			pixel inputLocatedPixel = in.pixels[row][col];
			pixel outputLocatedPixel = out.pixels[row][col];
			if (!areEqual(inputLocatedPixel, outputLocatedPixel)) {
				numDifferences += 1;
			}
		}
	}

	// Output the total number of differences to the console.
	std::cout << "Number of different pixels: " << numDifferences << "." << std::endl;
}

