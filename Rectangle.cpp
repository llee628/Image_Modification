#include <iostream>
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
    rectanglePattern = new int*[recHeight];
    for (int i = 0; i < recHeight; i++)
    {
        rectanglePattern[i] = new int[recWidth];
    }

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