// ImageClass.h
// Author:  Cheuk-Hang Tse
// Purpose: This file delcared the functions of the class Image, which
//			contain data type from ImageLib.h

#pragma once

#include <iostream>
#include "ImageLib.h"

class Image
{

	// operator<<: output the rows and columns of the coreImage in the class.
	// Preconditions: coreImage exists in this class.
	// Postconditions: Output the text about the number of rows and columns in the image.
	friend ostream& operator<<(ostream&, const Image&);

public:
	// getRows: Return the rows of this Image class.
	// Preconditions: coreImage exists in this class.
	// Postconditions: Return the rows of the coreImage in the class.
	int getRows() const;

	// getColumns: Return the columns of this Image class.
	// Preconditions: coreImage exists in this class.
	// Postconditions: Return the columns of the coreImage in the class.
	int getColumns() const;

	// Return a pixel of this Image class.
	// Preconditions: Must have valid row and column inputed.
	// Postconditions: return a pixel from the coreImage at location (row ,column).
	pixel& getPixel(const int& row, const int& col);

	// Set a pixel of this Image class.
	// Preconditions: Must have valid row and column inputed.
	// Postconditions: Set the coreImage's a pixel at location (row ,column) to inputPixel.
	void setPixel(const int& row, const int& col, const pixel& inputPixel);

	// Constructor using filename
	// Preconditions: Image with filename exits.
	// Postconditions: Consrtucte a Image with three arguements: image, rows, columns.
	Image(const std::string& filename);

	// Constructor using number of rows and columns
	// Preconditions: None.
	// Postconditions: Constructe an empty image with the parameters: rows and cols.
	Image(const int& rows, const int& cols);

	// Copy Constructor: Return a copy of the coreImage.
	// Precondtions: coreImage exist in the class.
	// Postconditions: Return a copy image of the coreImage.
	image copy();

	// Destructor: Deallocate the coreImage.
	// Preconditions: coreImage exists in the class.
	// Postconditions: Deallocate the coreImage in the class.
	~Image();

	// outputImage: Output a GIF file with the filename.
	// Preconditions: coreImage exist in the class.
	// Postconditions: Write the coreImage as a GIF file with the filename.
	void outputImage(std::string& filename);

	// operator=: The coreImage is equal to inputImage.
	// Preconditions: None.
	// Postconditions: Set the coreImage as a copy of the inputImage.
	const Image& operator=(const Image& in);

	// areEqual: Return true if all color components of two pixels are equal.
	// Preconditions: None.
	// Postconditions: Return a boolean about whether two pixels have equal color component.
	bool areEqualPixel(pixel coreImagePixel, pixel inputImagePixel);

	// operator==: Test if all pixels from two Images are the same.
	// Preconditions: None.
	// Postconditions: Return a true only if all pixels with the same location
	//                 between two Images have equal color component.
	const bool& operator==(Image& in);

	// operator!=: Test if all pixels from two Images are not the same.
	// Preconditions: None.
	// Postconditions: Return true if the sizes of two Images are different and
	//                 all pixels with the same location between two Images
	//                 have unequal color component.
	const bool& operator!=(Image& in);

	// operator<: Test if the number of pixels in coreImage is greater than
	//            the number of pixels in inputImage's coreImage.
	// Preconditions: The number of pixels from two Image class should not equal.
	// Postconditions: Return true if the number of pixels in coreImage is greater than
	//                 the number of pixels in the inputImage's coreImage.
	const bool& operator<(const Image& in);

	// operator<: Test if the number of pixels in coreImage is less than
	//            the number of pixels in inputImage's coreImage.
	// Preconditions: The number of pixels from two Image class should not equal.
	// Postconditions: Return true if the number of pixels in coreImage is less than
	//                 the number of pixels in the inputImage's coreImage.
	const bool& operator>(const Image& in);

	// createMirrowImage: create a mirrorImage based on coreImage.
	// Preconditions: The coreImage has coreImage.rows * coreImage.cols pixels allocated.
	// Postconditions: The mirrorImage is modified such that the image is mirrored.
	void createMirrorImage(const image& in);

private:
	image coreImage;
	int numOfCoreImagePixels;
};