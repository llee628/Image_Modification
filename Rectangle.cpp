#include <iostream>
#include <fstream>
#include "Rectangle.h"

using namespace std;


// public methods
Rectangle::Rectangle()
{
    rectanglePattern = NULL;
    recHeight = 0;
    recWidth = 0;
    upperLeftCorner.setRowCol(0, 0);
    isFilled = false;
}

void Rectangle::setRectangle()
{
    // intialize the shape of the rectangle
    resizeRec();

    // fill the rectangle with 1 first
    for (int i = 0; i < recHeight; i++)
    {
        for (int j = 0; j < recWidth; j++)
        {
            // 1 means the place that will replace by the rectangle's own color
            rectanglePattern[i][j] = 1; 
        }
    }

    // if the rectangle is not filled, then replace rectangle pattern to 0
    // except for the place of edges.
    if (!isFilled)
    {
        for (int i = 1; i < recHeight - 1; i++)
        {
            for (int j = 1; j < recWidth - 1; j++)
            {
                // 0 means the place that should be transparent
                rectanglePattern[i][j] = 0;
            }
        }

    }
}

bool Rectangle::readPatternFromFile(const string& inputFile)
{
    ifstream inFile;

    inFile.open(inputFile.c_str());

    if (inFile.fail())
    {
        cout << "Unable to open " << inputFile << "input file!" << endl;
        return false;
    }

    // check if the first row of pattern file is valid
    if (!readPatternWidthHeight(inFile))
    {
        return false;
    }

    // resize the rectangle
    resizeRec();

    // fill in the pattern from the file
    for (int i = 0 ; i < recHeight; i++)
    {
        for (int j = 0; j < recWidth; j++)
        {
            int val;
            if (readPatternVal(inFile, val))
            {
                rectanglePattern[i][j] = val;
            }
            else
            {
                if (inFile.eof()){
                    cout << "The number of elements is less than the pattern ";
                    cout << "size indicates" << endl;
                }
                return false;
            }

        }
    }

    // if file is not at the end of file here, that means the pixels does not 
    // match the size indicates.
    string eofTest;
    inFile >> eofTest;  // make inFile pointer move one extra word
    if (!inFile.eof())
    {
        cout << "The number of elements is greater than the pattern file ";
        cout << "indicates" << endl;
        return false;
    }

    inFile.close();
    return true;
}

void Rectangle::specifyRectangle(
    const RowColumnClass& upperLeft, 
    int width, 
    int height)
{
    upperLeftCorner = upperLeft;
    recHeight = height;
    recWidth = width;
}

void Rectangle::specifyRecByCorners()
{
    int upperLeftRow;
    int upperLeftCol;
    int lowerRightRow;
    int lowerRightCol;
    bool isInputValid = false;
    bool isAllInputValid = false;

    while (!isAllInputValid)
    {
        // handle the input of upper left corner
        handleUpLeftCornerInput(upperLeftRow, upperLeftCol);

        // handle the input of lower right corner
        while (!isInputValid)
        {
            cout << "Enter lower right corner row and column: ";
            isInputValid = handleInputFromKeyboard(
                            lowerRightRow, 
                            lowerRightCol);

            if (isInputValid && (lowerRightRow < 0 || lowerRightCol < 0))
            {
                cout << "Invalid input value: " << endl;
                cout << "lower right row and lower right column should be ";
                cout << "greater and equal to 0." << endl;
                isInputValid = false;
            }
        }

        // check if all input data are reasonable
        if (lowerRightRow < upperLeftRow || lowerRightCol < upperLeftCol)
        {
            cout << "Error!! The lower right row and lower right column ";
            cout << "should be greater than upper left row and column ";
            cout << "respectively." << endl;
        }
        else
        {
            isAllInputValid = true;
        }

    }

    // specify the rectangle
    upperLeftCorner.setRowCol(upperLeftRow, upperLeftCol);
    recWidth = lowerRightCol - upperLeftCol;
    recHeight = lowerRightRow - upperLeftRow;

}

void Rectangle::specifyRecByCornerAndDim()
{
    int upperLeftRow;
    int upperLeftCol;
    bool isInputValid = false;
    int width;
    int height;

    // handle the input of upper left corner
    handleUpLeftCornerInput(upperLeftRow, upperLeftCol);

    // handle the input of height
    while (!isInputValid)
    {
        cout << "Enter int for number of rows: ";
        isInputValid = handleInputFromKeyboard(height);

        if (isInputValid && height < 0)
        {
            cout << "Invalid input value: " << endl;
            cout << "The number of rows of the rectangle should be greater ";
            cout << "and equal to 0." << endl;

            isInputValid = false;
        }
        
    }

    // handle the input of width
    isInputValid = false;
    while (!isInputValid)
    {
        cout << "Enter int for number of columns: ";
        isInputValid = handleInputFromKeyboard(width);

        if (isInputValid && width < 0)
        {
            cout << "Invalid input value: " << endl;
            cout << "The number of columns of the rectangle should be ";
            cout << "greater and equal to 0." << endl;

            isInputValid = false;
        }
        
    }

    // specify the rectangle
    recHeight = height;
    recWidth = width;
    upperLeftCorner.setRowCol(upperLeftRow, upperLeftCol);

}

void Rectangle::specifyRecByCenterAndDim()
{
    int centerRow;
    int centerCol;
    int halfHeight;
    int halfWidth;
    bool isInputValid = false;
    bool isAllValid = false;
    int upperLeftRow;
    int upperLeftCol;

    while (!isAllValid)
    {
        // handle the center row column input
        while (!isInputValid)
        {
            cout << "Enter rectangle center row and column: ";
            isInputValid = handleInputFromKeyboard(centerRow, centerCol);

            if (isInputValid && (centerRow < 0 || centerCol < 0))
            {
                cout << "Invalid input value:" << endl;
                cout << "Center row and column should be greater or ";
                cout << "to 0" << endl;
                isInputValid = false;
            }
        }

        // handle the half height input
        isInputValid = false;
        while (!isInputValid)
        {
            cout << "Enter int for half number of rows: ";
            isInputValid = handleInputFromKeyboard(halfHeight);

            if (isInputValid && halfHeight < 0)
            {
                cout << "Invalid input value:" << endl;
                cout << "Half number of rows should be greater and ";
                cout << "equal to 0." << endl;
                isInputValid = false;
            }
        }

        // handle the half width input
        isInputValid = false;
        while (!isInputValid)
        {
            cout << "Enter int for half number of columns: ";
            isInputValid = handleInputFromKeyboard(halfWidth);

            if (isInputValid && halfWidth < 0)
            {
                cout << "Invalid input value:" << endl;
                cout << "Half number of columns should be greater and ";
                cout << "equal to 0." << endl;
                isInputValid = false;
            }
        }

        // check the upper left corner validality
        upperLeftRow = centerRow - halfHeight;
        upperLeftCol = centerCol - halfWidth;

        if (upperLeftRow < 0 || upperLeftCol < 0)
        {
            cout << "Invalid input value:" << endl;
            cout << "values of upper left corner should greater and ";
            cout << "equal to 0." << endl;
        }
        else
        {
            isAllValid = true;
        }

    }

    // specify the rectangle
    upperLeftCorner.setRowCol(upperLeftRow, upperLeftCol);
    recHeight = 2 * halfHeight;
    recWidth = 2 * halfWidth;
}

void Rectangle::setCorner()
{
    int upperLeftRow;
    int upperLeftCol;
    bool isInputValid = false;
    // handle the input of upper left corner
    while (!isInputValid)
    {
        cout << "Enter upper left corner row and column: ";
        isInputValid = handleInputFromKeyboard(upperLeftRow, upperLeftCol);

        if (isInputValid && (upperLeftRow < 0 || upperLeftCol < 0))
        {
            cout << "Invalid input value: " << endl;
            cout << "upper left row and upper left column should be ";
            cout << "greater and equal to 0." << endl;
            isInputValid = false;
        }
    }

    // set the corner position
    upperLeftCorner.setRowCol(upperLeftRow, upperLeftCol);
}

// private methods
void Rectangle::handleUpLeftCornerInput(int& upperLeftRow, int& upperLeftCol)
{
    bool isInputValid = false;
    // handle the input of upper left corner
    while (!isInputValid)
    {
        cout << "Enter upper left corner row and column: ";
        isInputValid = handleInputFromKeyboard(upperLeftRow, upperLeftCol);

        if (isInputValid && (upperLeftRow < 0 || upperLeftCol < 0))
        {
            cout << "Invalid input value: " << endl;
            cout << "upper left row and upper left column should be ";
            cout << "greater and equal to 0." << endl;
            isInputValid = false;
        }
    }
}

bool Rectangle::readPatternWidthHeight(ifstream& inFile)
{
    int width;
    int height;

    // deal with width input
    inFile >> width;
    if (!isFileInputValid(inFile, "width"))
    {
        return false;
    }

    // deal with width output
    inFile >> height;
    if (!isFileInputValid(inFile, "height"))
    {
        return false;
    }

    if (width < 0)
    {
        cout << "Invalid width value: " << width << endl;
        return false;
    }

    if (height < 0)
    {
        cout << "Invalid height value: " << height << endl;
        return false;
    }

    recHeight = height;
    recWidth = width;

    return true;
}

bool Rectangle::readPatternVal(ifstream& inFile, int& val)
{
    inFile >> val;
    if (!isFileInputValid(inFile, "pattern element"))
    {
        return false;
    }

    if (val != 0 && val != 1)
    {
        cout << "Invalid value of the pattern element: " << val << endl;
        return false;
    }

    return true;

}

bool Rectangle::isFileInputValid(ifstream& inFile, const string& eofCase)
{
    if (inFile.eof())
    {
        cout << "EOF before reading the " << eofCase << endl;
        return false;
    }
    else if (inFile.fail())
    {
        inFile.clear();
        inFile.ignore(BUFFER_CLEAR_NUM, '\n');
        cout << "Input type error" << endl;
        return false;
    }

    return true;
}

void Rectangle::resizeRec()
{
    // intialize the shape of the rectangle
    rectanglePattern = new int*[recHeight];
    for (int i = 0; i < recHeight; i++)
    {
        rectanglePattern[i] = new int[recWidth];
    }
}