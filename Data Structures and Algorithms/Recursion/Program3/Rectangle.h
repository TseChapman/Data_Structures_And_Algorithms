/*
Rectangle.h

Author: Cheuk-Hang Tse
Purpose: Rectangle class header file. declare functions included in Rectangle class.
*/
#pragma once

#include <iostream>
#include "ImageLib.h"

class Rectangle
{
	// operator<<: output the first row and the first column, and the number of rows and columns stored in this Rectangle class.
	// Preconditions: firstRow, firstCol, numRows, and numCols are not null.
	// Postconditions: Output the text about the number of rows and columns, 
	//                 and the first row and column stored in this Rectangle class.
	friend ostream& operator<<(ostream&, const Rectangle&);

public:
	// Constructor: construct a zero width and length rectangle without parameters.
	// Preconditions: None.
	// Postconditions: set firstRow, firstCol, numRows, and numCols to zero.
	Rectangle();

	// Constructor: construct a rectangle from parameters
	// Preconditions: none of the pararmeters should pass in null.
	// Postconditions: set firstRow, firstCol, numRows, and numCols accordingly to the parameters.
	Rectangle(int inFirstRow, int inFirstColumn, int inNumRows, int inNumColumns);

	// setFirstRow: set firstRow by the parameter.
	// Preconditions: Should not pass in null.
	// Postconditions: set firstRow by an integer.
	void setFirstRow(int inputFirstRow);

	// setFirstCol: set firstCol by the parameter.
	// Preconditions: Should not pass in null.
	// Postconditions: set firstCol by an integer.
	void setFirstCol(int inputFirstCol);

	// setNumRows: set numRows by the parameter.
	// Preconditions: Should not pass in null.
	// Postconditions: set numRows by an integer.
	void setNumRows(int inputNumRows);

	// setNumCols: set numCols by the parameter.
	// Preconditions: Should not pass in null.
	// Postconditions: set numCols by an integer.
	void setNumCols(int inputNumCols);

	// getFirstRow: get firstRow from this Rectangle class.
	// Preconditions: firstRow is not null.
	// Postconditions: return firstRow in this Rectangle class.
	int getFirstRow();

	// getFirstCol: get firstCol from this Rectangle class.
	// Preconditions: firstCol is not null.
	// Postconditions: return firstCol in this Rectangle class.
	int getFirstCol();

	// getNumRows: get numRows from this Rectangle class.
	// Preconditions: numRows is not null.
	// Postconditions: return numRows in this Rectangle class.
	int getNumRows();

	// getNumCols: get numCols from this Rectangle class.
	// Preconditions: numCols is not null.
	// Postconditions: return numCols in this Rectangle class.
	int getNumCols();

	// operator==: return true if all arguments (firstRow, firstCol, numRows, numCols) from
	//             both Rectangle class are equal.
	// Preconditions: None.
	// Postconditions: return true if all arguments (firstRow, firstCol, numRows, numCols) from
	//                 both Rectangle class are equal.
	const bool& operator==(Rectangle& rec);

	// operator!=: return true if any of the arguments (firstRow, firstCol, numRows, numCols)
	//             from both Rectangle class is not equal.
	// Preconditions: None.
	// Postconditions: return true if any of the arguments (firstRow, firstCol, numRows, numCols)
	//                 from both Rectangle class is not equal.
	const bool& operator!=(Rectangle& rec);

private:
	int firstRow;
	int firstCol;
	int numRows;
	int numCols;
};