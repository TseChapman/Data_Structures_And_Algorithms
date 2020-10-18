// ImageClass.cpp
// Author:  Cheuk-Hang Tse
// Purpose: This cpp file contains the following functions:
//			1. Constructor using a filename (read from a file).
//			2. Constructor using just the number of rows and columns (create a blank, black image).
//			3. Copy constructor, destructor, operator=.
//			4. Accessors for the number of rows and columns in the image.
//			5. Accessor and mutator functions for individual image pixels.
//			6. Output a gif file with filename and coreImage.
//			7. Overload the operator== and operator!= for comparison of images.
//			8. Overload the operator< and operator> for comparison of images sizes.
//			9. Overload the << operator to output the number of rows and columns in the image.
//			10. A function that returns a  mirror-image of the original image.

#include <iostream>
#include "ImageClass.h"

// getRows: Return the rows of this Image class.
// Preconditions: coreImage exists in this class.
// Postconditions: Return the rows of the coreImage in the class.
int Image::getRows() const
{
	return coreImage.rows;
}

// getColumns: Return the columns of this Image class.
// Preconditions: coreImage exists in this class.
// Postconditions: Return the columns of the coreImage in the class.
int Image::getColumns() const
{
	return coreImage.cols;
}

// Return a pixel of this Image class.
// Preconditions: Must have valid row and column inputed.
// Postconditions: return a pixel from the coreImage at location (row ,column).
pixel& Image::getPixel(const int& row, const int& col)
{
	return coreImage.pixels[row][col];
}

// Set a pixel of this Image class.
// Preconditions: Must have valid row and column inputed.
// Postconditions: Set the coreImage's a pixel at location (row ,column) to inputPixel.
void Image::setPixel(const int& row, const int& col, const pixel& inputPixel)
{
	coreImage.pixels[row][col] = inputPixel;
}

// Constructor using filename
// Preconditions: Image with filename exits.
// Postconditions: Consrtucte the Image with three arguements: image, rows, columns.
Image::Image(const std::string& filename)
{
	image input = ReadGIF(filename);
	coreImage = input;
	numOfCoreImagePixels = getRows() * getColumns();
}

// Constructor using number of rows and columns
// Preconditions: None.
// Postconditions: Constructe an empty image with the parameters: rows and cols.
Image::Image(const int& rows, const int& columns)
{
	image newImage = CreateImage(rows, columns);
	coreImage = newImage;
	numOfCoreImagePixels = getRows() * getColumns();
}

// Copy Constructor: Return a copy of the coreImage.
// Precondtions: None.
// Postconditions: Return a copy image of the coreImage.
image Image::copy()
{
	return CopyImage(coreImage);
}

// Destructor: Deallocate the coreImage.
// Preconditions: None.
// Postconditions: Deallocate the coreImage in the class.
Image::~Image()
{
	DeallocateImage(coreImage);
}

// outputImage: Output a GIF file with the filename.
// Preconditions: None.
// Postconditions: Write the coreImage as a GIF file with the filename.
void Image::outputImage(std::string& filename)
{
	WriteGIF(filename, coreImage);
}

// operator=: The coreImage is equal to a copy of inputImage's coreImage.
// Preconditions: None.
// Postconditions: Set the coreImage as a copy of the inputImage's coreImage.
const Image& Image::operator=(const Image& in)
{
	if (this != &in)
	{
		// Deallocate left operand.
		DeallocateImage(coreImage);

		// Copy the right to the left operand.
		coreImage = CopyImage(in.coreImage);
	}
	return *this;
}

// areEqual: return true if all color components of two pixels are equal.
// Preconditions: None.
// Postconditions: return a boolean about whether two pixels have equal color component.
bool Image::areEqualPixel(pixel coreImagePixel, pixel inputImagePixel)
{
	return ((coreImagePixel.blue == inputImagePixel.blue) &&
		    (coreImagePixel.red == inputImagePixel.red) &&
		    (coreImagePixel.green == inputImagePixel.green));
}

// operator==: Test if all pixels from two Images are the same.
// Preconditions: None.
// Postconditions: Return a true only if all pixels with the same location
//                 between two images have equal color component.
const bool& Image::operator==(Image& in)
{
	// Return false if the sizes of two Images are not the same.
	if (coreImage.rows != in.getRows() || coreImage.cols != in.getColumns())
	{
		// Two image is not equal when they have different number of rows or columns.
		return false;
	}

	else if (coreImage.rows == in.getRows() && coreImage.cols == in.getColumns())
	{
		// Check if any pixel is not the same between both Image at the same location.
		for (int row = 0; row < coreImage.rows; row++)
		{
			for (int col = 0; col < coreImage.cols; col++)
			{
				pixel coreImagePixel = coreImage.pixels[row][col];
				pixel inputImagePixel = in.getPixel(row, col);

				if (!areEqualPixel(coreImagePixel, inputImagePixel))
				{
					return false;
				}
			}
		}

		// Return true if all pixels from both Images are the same.
		return true;
	}
}

// operator!=: Test if all pixels from two Images are not the same.
// Preconditions: None.
// Postconditions: Return true if the sizes of two Images are different and
//                 all pixels with the same location between two Images
//                 have unequal color component.
const bool& Image::operator!=(Image& in)
{
	// Return true if the sizes of two Images are not the same.
	if (coreImage.rows != in.getRows() || coreImage.cols != in.getColumns())
	{
		// Two image is not equal when they have different number of rows or columns.
		return true;
	}

	else if (coreImage.rows == in.getRows() && coreImage.cols == in.getColumns())
	{
		// Check if any pixel is the same between both Image at the same location.
		for (int row = 0; row < coreImage.rows; row++)
		{
			for (int col = 0; col < coreImage.cols; col++)
			{
				pixel coreImagePixel = coreImage.pixels[row][col];
				pixel inputImagePixel = in.getPixel(row, col);

				if (areEqualPixel(coreImagePixel, inputImagePixel))
				{
					return false;
				}
			}
		}

		// Return true if all pixels from both Images are not the same.
		return true;
	}
}

// operator<: Test if the number of pixels in coreImage is greater than
//            the number of pixels in inputImage's coreImage.
// Preconditions: The number of pixels from two Image class should not equal.
// Postconditions: Return true if the number of pixels in coreImage is greater than
//                 the number of pixels in the inputImage's coreImage.
const bool& Image::operator<(const Image& in)
{
	return (numOfCoreImagePixels < in.numOfCoreImagePixels);
}

// operator<: Test if the number of pixels in coreImage is less than
//            the number of pixels in inputImage's coreImage.
// Preconditions: The number of pixels from two Image class should not equal.
// Postconditions: Return true if the number of pixels in coreImage is less than
//                 the number of pixels in the inputImage's coreImage.
const bool& Image::operator>(const Image& in)
{
	return (numOfCoreImagePixels > in.numOfCoreImagePixels);
}

// operator<<: output the rows and columns of the coreImage in the class.
// Preconditions: None.
// Postconditions: Output the text about the number of rows and columns in the image.
ostream& operator<<(ostream& output, const Image& in)
{
	output << "Number of rows: " << in.getRows() << " and the number of columns: " << in.getColumns() << std::endl;
	return output;
}

// createMirrowImage: create a mirrorImage based on coreImage.
// Preconditions: The coreImage has coreImage.rows * coreImage.cols pixels allocated.
// Postconditions: The mirrorImage is modified such that the image is mirrored.
void Image::createMirrorImage(const image& in)
{
	image mirrorImage = in;
	for (int row = 0; row < mirrorImage.rows; row++) {
		for (int col = 0; col < mirrorImage.cols / 2; col++) {
			int mirrorCol = mirrorImage.cols - col - 1;
			pixel temp = mirrorImage.pixels[row][col];
			mirrorImage.pixels[row][col] = mirrorImage.pixels[row][mirrorCol];
			mirrorImage.pixels[row][mirrorCol] = temp;
		}
	}
	coreImage = mirrorImage;
}
