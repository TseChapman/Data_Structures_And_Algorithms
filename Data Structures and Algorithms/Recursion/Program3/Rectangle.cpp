/*
Rectangle.cpp

Author: Cheuk-Hang Tse
Purpose: All Functions that are declared from "Rectangle.h"
		 Including constructor(s), accessors, mutators, operator<<, operator== and operator!=.
*/
#include "Rectangle.h"

// operator<<: output the first row and the first column, and the number of rows and columns stored in this Rectangle class.
// Preconditions: firstRow, firstCol, numRows, and numCols are not null.
// Postconditions: Output the text about the number of rows and columns, 
//                 and the first row and column stored in this Rectangle class.
ostream& operator<<(ostream& output, const Rectangle& rec)
{
	output << "First row is " << rec.firstRow << " and the first column is " << rec.firstCol << 
		      ". Number of rows: " << rec.numRows << " and the number of columns: " << rec.numCols <<std::endl;
	return output;
}

// Constructor: construct a zero width and length rectangle without parameters.
// Preconditions: None.
// Postconditions: set firstRow, firstCol, numRows, and numCols to zero.
Rectangle::Rectangle()
{
	firstRow = 0;
	firstCol = 0;
	numRows = 0;
	numCols = 0;
}

// Constructor: construct a rectangle from parameters
// Preconditions: none of the pararmeters should pass in null.
// Postconditions: set firstRow, firstCol, numRows, and numCols accordingly to the parameters.
Rectangle::Rectangle(int inFirstRow, int inFirstColumn, int inNumRows, int inNumColumns)
{
	firstRow = inFirstRow;
	firstCol = inFirstColumn;
	numRows = inNumRows;
	numCols = inNumColumns;
}

// setFirstRow: set firstRow by the parameter.
// Preconditions: Should not pass in null.
// Postconditions: set firstRow by an integer.
void Rectangle::setFirstRow(int inputFirstRow)
{
	firstRow = inputFirstRow;
}

// setFirstCol: set firstCol by the parameter.
// Preconditions: Should not pass in null.
// Postconditions: set firstCol by an integer.
void Rectangle::setFirstCol(int inputFirstCol)
{
	firstCol = inputFirstCol;
}

// setNumRows: set numRows by the parameter.
// Preconditions: Should not pass in null.
// Postconditions: set numRows by an integer.
void Rectangle::setNumRows(int inputNumRows)
{
	numRows = inputNumRows;
}

// setNumCols: set numCols by the parameter.
// Preconditions: Should not pass in null.
// Postconditions: set numCols by an integer.
void Rectangle::setNumCols(int inputNumCols)
{
	numCols = inputNumCols;
}

// getFirstRow: get firstRow from this Rectangle class.
// Preconditions: firstRow is not null.
// Postconditions: return firstRow in this Rectangle class.
int Rectangle::getFirstRow()
{
	return firstRow;
}

// getFirstCol: get firstCol from this Rectangle class.
// Preconditions: firstCol is not null.
// Postconditions: return firstCol in this Rectangle class.
int Rectangle::getFirstCol()
{
	return firstCol;
}

// getNumRows: get numRows from this Rectangle class.
// Preconditions: numRows is not null.
// Postconditions: return numRows in this Rectangle class.
int Rectangle::getNumRows()
{
	return numRows;
}

// getNumCols: get numCols from this Rectangle class.
// Preconditions: numCols is not null.
// Postconditions: return numCols in this Rectangle class.
int Rectangle::getNumCols()
{
	return numCols;
}

// operator==: return true if all arguments (firstRow, firstCol, numRows, numCols) from
//             both Rectangle class are equal.
// Preconditions: None.
// Postconditions: return true if all arguments (firstRow, firstCol, numRows, numCols) from
//                 both Rectangle class are equal.
const bool& Rectangle::operator==(Rectangle& rec)
{
	return (firstRow == rec.getFirstRow() && firstCol == rec.getFirstCol() && numRows == rec.getNumRows() && numCols == rec.getNumCols());
}

// operator!=: return true if any of the arguments (firstRow, firstCol, numRows, numCols)
//             from both Rectangle class is not equal.
// Preconditions: None.
// Postconditions: return true if any of the arguments (firstRow, firstCol, numRows, numCols)
//                 from both Rectangle class is not equal.
const bool& Rectangle::operator!=(Rectangle& rec)
{
	return (firstRow != rec.getFirstRow() || firstCol != rec.getFirstCol() || numRows != rec.getNumRows() || numCols != rec.getNumCols());
}

