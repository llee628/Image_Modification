#ifndef _RECTANGLE_H_
#define _RECTANGLE_H_

/*
    Programmer: Leo Lee
    Date: Nov 3, 2021
    Purpose: This class represents a rectangle pattern and not limited to a
    real rectangle. It could also be a text pattern
*/

#include "RowColumnClass.h"
#include "ColorClass.h"
#include "handleInputFromKeyboard.h"

class Rectangle
{
  private:
    int** rectanglePattern;
    int recHeight;
    int recWidth;
    RowColumnClass upperLeftCorner;
    ColorClass recColor;
    bool isFilled;

    // handle the upper left corner input and handle the errors
    void handleUpLeftCornerInput(int& upperLeftRow, int& upperLeftCol);

    // handle the first row of reading in the pattern file
    bool readPatternWidthHeight(ifstream& inFile);

    // handle the pattern value reading from file
    bool readPatternVal(ifstream& inFile, int& val);

    // This method check if the input stats is valid
    bool isFileInputValid(ifstream& inFile, const string& eofCase);

    // resize the rectangle base on current height and width
    void resizeRec();

  
  public:
    
    /*
        The default ctor will set rectanglePattern to NULL and the rest of 
        data member to 0
    */
    Rectangle();

    /*
        This method sets the rectangle pattern based on its data members
    */
    void setRectangle();

    /*
        This method builds rectangle by the input file
    */
    bool readPatternFromFile(const string& inputFile);

    /*
        This methods specify the rectangle's width, height, and upper left
        corner position by given the upper left and the dimension of the
        rectangle
    */
    void specifyRectangle(
        const RowColumnClass& upperLeft, 
        int width, 
        int height);
    
    /*
        The method allows user to specify a rectangle by enter upper left 
        and lower right corners of rectangle.
    */
    void specifyRecByCorners();

    /*
        The method allows user to specify a rectangle by enter upper left 
        and the dimension of the rectangle.
    */
    void specifyRecByCornerAndDim();

    /*
        This method allows user to specify a rectangle by enter the center of 
        the rectangle and its half width and half height
    */
    void specifyRecByCenterAndDim();

    // This method get the pattern value at location
    int getValAtLocation(const RowColumnClass& inRowCol);

    /*
        Set the pattern corner position from user input
    */
    void setCorner();

    /*
        This inline method set the rectangle color with the rhs input
    */
    void setColor(const ColorClass& rhs)
    {
        recColor = rhs;
    }
    
    /*
        This inline method set the state of isFilled based on the true or
        false input
    */
    void setFilled(bool filled)
    {
        isFilled = filled;
    }

    // inline methods for get private data members
    int getRecHeight() const
    {
        return recHeight;
    }

    int getRecWidth() const
    {
        return recWidth;
    }

    int** getImage() const
    {
        return rectanglePattern;
    }

    RowColumnClass getUpperLeft() const
    {
        return upperLeftCorner;
    }

    ColorClass getColor() const
    {
        return recColor;
    }

};




#endif