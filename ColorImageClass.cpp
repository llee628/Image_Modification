/*
    Programmer: Leo Lee
    Date: Nov 10, 2021
    Purpose: This code is the implementation of the ColorImageClass methods
*/

/*
    Modification for resubmission:
    1. call readColorFromFile() method of ColorClass in readImageFromFile
    2. call writeColorToFile method of ColorClass in writeImageToFile
    3. implement annotateWithRectangle method
    4. implement annotatePatternFromFile method
    5. implement insertImage method
*/

#include <iostream>
#include <fstream>
#include "ColorImageClass.h"
#include "isInputValid.h"
#include "Rectangle.h"


using namespace std;

ColorImageClass::ColorImageClass()
{
    image = NULL;
    imageRowSize = 0;
    imageColSize = 0;
}

ColorImageClass::ColorImageClass(int width, int height)
{
    imageColSize = width;
    imageRowSize = height;

    // dynamic allocate the image
    image = new ColorClass*[imageRowSize];
    for (int i = 0; i < imageRowSize; i++)
    {
        image[i] = new ColorClass[imageColSize];
    }

    // set every pixel to black
    for (int i = 0; i < imageRowSize; i++)
    {
        for (int j = 0; j < imageColSize; j++)
        {
            image[i][j].setToBlack();
        }
    }
}

void ColorImageClass::initializeTo()
{
    ColorClass color;
    color.setToBlack();
    initializeTo(color);
}

void ColorImageClass::initializeTo(ColorClass &inColor)
{
    // dynamic allocate the image
    image = new ColorClass*[imageRowSize];
    for (int i = 0; i < imageRowSize; i++)
    {
        image[i] = new ColorClass[imageColSize];
    }

    for (int i = 0; i < imageRowSize; i++)
    {
        for (int j = 0; j < imageColSize; j++)
        {
            image[i][j].setTo(inColor);
        }
    }
}

bool ColorImageClass::addImageTo(ColorImageClass &rhsImg)
{
    bool isClipped = false;
    for (int i = 0; i < imageRowSize; i++)
    {
        for (int j = 0; j < imageColSize; j++)
        {
            ColorClass correspondColor = rhsImg.image[i][j];
            // if addColor() returns ture, then set isClipped true
            // if not it will still run the addColor
            if (image[i][j].addColor(correspondColor))
            {
                isClipped = true;
            }
        }
    }

    return isClipped;
}

bool ColorImageClass::addImages(
    int numImgsToAdd, 
    ColorImageClass imagesToAdd []
    )
{
    // if no image in imagesToAdd, then return directly
    if (numImgsToAdd <= 0)
    {
        return false;
    }

    bool isClipped = false;
    ColorImageClass resultImage;

    for (int i = 0; i < numImgsToAdd; i++)
    {
        if (resultImage.addImageTo(imagesToAdd[i]))
        {
            isClipped = true;
        }
    }

    for (int i = 0; i < imageRowSize; i++)
    {
        for (int j = 0; j < imageColSize; j++)
        {
            image[i][j].setTo(resultImage.image[i][j]);
        }
    }

    return isClipped;
}

bool ColorImageClass::setColorAtLocation(
    RowColumnClass &inRowCol, 
    ColorClass &inColor
    )
{
    //check the if the location is valid
    if (!isLocationValid(inRowCol))
    {
        return false;
    }

    int row = inRowCol.getRow();
    int column = inRowCol.getCol();

    image[row][column].setTo(inColor);

    return true;


}

bool ColorImageClass::getColorAtLocation(
    RowColumnClass &inRowCol, 
    ColorClass &outColor
    )
{
    if (!isLocationValid(inRowCol))
    {
        return false;
    }

    int row = inRowCol.getRow();
    int column = inRowCol.getCol();
    outColor.setTo(image[row][column]);

    return true;

}

bool ColorImageClass::isLocationValid(RowColumnClass &inRowCol)
{
    int row = inRowCol.getRow();
    int column = inRowCol.getCol();
    
    if (row >= imageRowSize || row < 0)
    {
        return false;
    }

    if (column >= imageColSize || column < 0)
    {
        return false;
    }

    return true;
}

void ColorImageClass::printImage() const
{
    for (int i = 0; i < imageRowSize; i++)
    {
        for (int j = 0; j < imageColSize; j++)
        {
            image[i][j].printComponentValues();
            // don't print "--" when the last element in a row is reached
            if (j != imageColSize - 1)
            {
                cout << "--";
            }
        }
        cout<<endl;
    }
}

bool ColorImageClass::readImageFromFile(const string& inputFile)
{
    ifstream inFile;

    inFile.open(inputFile.c_str());

    if (inFile.fail())
    {
        cout << "Unable to open " << inputFile << "input file!" << endl;
        return false;
    }

    // check if the first three row of the ppm file is valid
    if (!readPpmFormatMagicNum(inFile) ||
        !readPpmWidthHeight(inFile) ||
        !readPpmMaxVal(inFile))
    {
        return false;
    }

    // initialize the image
    initializeTo();

    // fill in the pixels from the file
    for (int i = 0; i < imageRowSize; i++)
    {
        for (int j = 0; j < imageColSize; j++)
        {
            if (!image[i][j].readColorFromFile(inFile))
            {
                if (inFile.eof()){
                    cout << "The number of pixels is lower than the image ";
                    cout << "size" << endl;
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
        cout << "The number of pixels is larger than the image ";
        cout << "size" << endl;
        return false;
    }

    inFile.close();
    return true;
}

bool ColorImageClass::writeImageToFile(const string& outputFile)
{
    ofstream outFile;
    int width = imageColSize;
    int height = imageRowSize;

    outFile.open(outputFile.c_str());
    if (outFile.fail())
    {
        cout << "Unable to open output file: " << outputFile << endl;
        return false;
    }

    // output the ppm magic number
    outFile << PPM_MAGIC_NUM << endl;

    // output the image width and height info
    outFile << width << " " << height << endl;

    // output the image color max value info
    outFile << COLOR_MAX << endl;

    // output the image pixels
    for (int i = 0; i < imageRowSize; i++)
    {
        for (int j = 0; j < imageColSize; j++)
        {
            image[i][j].writeColorToFile(outFile);
            if (j != imageColSize - 1)
            {
                outFile << " ";
            }
        }
        outFile << endl;
    }
    
    outFile.close();
    return true;

}

void ColorImageClass::annotateWithRectangle()
{
    Rectangle recPattern;
    ColorClass recColor;
    string option;
    bool isOptionValid = false;

    // handle options for specify the rectangle
    while (!isOptionValid)
    {
        cout << "1. Specify upper left and lower right corners of rectangle";
        cout << endl;
        cout << "2. Specify upper left corner and dimensions of rectangle";
        cout << endl;
        cout << "3. Specify extent from center of rectangle";
        cout << endl;

        cout << "Enter int for rectangle specification method: ";
        cin >> option;

        if (option == BY_CORNERS_OPTION)
        {
            recPattern.specifyRecByCorners();
            isOptionValid = true;
        }
        else if (option == BY_CORNER_AND_DIM_OPTION)
        {
            recPattern.specifyRecByCornerAndDim();
            isOptionValid = true;
        }
        else if (option == BY_CENTER_AND_DIM_OPTION)
        {
            recPattern.specifyRecByCenterAndDim();
            isOptionValid = true;
        }
        else
        {
            cout << "Error option input: the input option should be ";
            cout << "1 - 3" << endl;
        }
    }

    // handle the rectangle color options
    isOptionValid = false;
    while (!isOptionValid)
    {
        cout << "1. Red" << endl;
        cout << "2. Green" << endl;
        cout << "3. Blue" << endl;
        cout << "4. Black" << endl;
        cout << "5. White" << endl;

        cout << "Enter int for rectangle color: ";
        cin >> option;

        if (option == SET_RED_OPTION)
        {
            recColor.setToRed();
            recPattern.setColor(recColor);
            isOptionValid = true;
        }
        else if (option == SET_GREEN_OPTION)
        {
            recColor.setToGreen();
            recPattern.setColor(recColor);
            isOptionValid = true;
        }
        else if (option == SET_BLUE_OPTION)
        {
            recColor.setToBlue();
            recPattern.setColor(recColor);
            isOptionValid = true;
        }
        else if (option == SET_BLACK_OPTION)
        {
            recColor.setToBlack();
            recPattern.setColor(recColor);
            isOptionValid = true;
        }
        else if (option == SET_WHITE_OPTION)
        {
            recColor.setToWhite();
            recPattern.setColor(recColor);
            isOptionValid = true;
        }
        else
        {
            cout << "Error option input: the input option should be ";
            cout << "1 - 5" << endl;
        }
    }

    // handle the rectangle fill option
    isOptionValid = false;
    while (!isOptionValid)
    {
        cout << "1. No" << endl;
        cout << "2. Yes" << endl;

        cout << "Enter int for rectangle fill option: ";
        cin >> option;

        if (option == NOT_FILLED_OPTION)
        {
            recPattern.setFilled(false);
            isOptionValid = true;
        }
        else if (option == FILLED_OPTION)
        {
            recPattern.setFilled(true);
            isOptionValid = true;
        }
        else
        {
            cout << "Error option input: the input option should be ";
            cout << "1 - 2" << endl;
        }
    }

    // make a rectangle pattern
    recPattern.setRectangle();

    // draw rectangle on the image
    modifyImage(recPattern);
}

void ColorImageClass::annotatePatternFromFile()
{
    Rectangle pattern;
    ColorClass patternColor;
    string option;
    string inFileName;
    bool isOptionValid = false;
    bool isFileValid = false;

    // handle the file input
    while (!isFileValid)
    {
        cout << "Enter string for file name containing pattern: ";
        cin >> inFileName;

        if (!pattern.readPatternFromFile(inFileName))
        {
            cout << "Fail to load the pattern file. Try again." << endl;
        }
        else
        {
            isFileValid = true;
        }
    }

    // handle the upper left corner input
    pattern.setCorner();

    // handle the pattern color options
    while (!isOptionValid)
    {
        cout << "1. Red" << endl;
        cout << "2. Green" << endl;
        cout << "3. Blue" << endl;
        cout << "4. Black" << endl;
        cout << "5. White" << endl;

        cout << "Enter int for pattern color: ";
        cin >> option;

        if (option == SET_RED_OPTION)
        {
            patternColor.setToRed();
            pattern.setColor(patternColor);
            isOptionValid = true;
        }
        else if (option == SET_GREEN_OPTION)
        {
            patternColor.setToGreen();
            pattern.setColor(patternColor);
            isOptionValid = true;
        }
        else if (option == SET_BLUE_OPTION)
        {
            patternColor.setToBlue();
            pattern.setColor(patternColor);
            isOptionValid = true;
        }
        else if (option == SET_BLACK_OPTION)
        {
            patternColor.setToBlack();
            pattern.setColor(patternColor);
            isOptionValid = true;
        }
        else if (option == SET_WHITE_OPTION)
        {
            patternColor.setToWhite();
            pattern.setColor(patternColor);
            isOptionValid = true;
        }
        else
        {
            cout << "Error option input: the input option should be ";
            cout << "1 - 5" << endl;
        }
    }

    // draw pattern on the image
    modifyImage(pattern);
}

void ColorImageClass::insertImage()
{
    ColorImageClass insertImg;
    string inFileName;
    string option;
    ColorClass transColor;
    RowColumnClass upperLeftCorner;
    bool isFileValid = false;
    bool isInputValid = false;
    bool isOptionValid = false;
    int upperLeftRow;
    int upperLeftCol;
    int baseImageHeight = imageRowSize;
    int baseImageWidth = imageColSize;
    int insertImgHeight;
    int insertImgWidth;

    // handle the file input
    while (!isFileValid)
    {
        cout << "Enter string for file name of PPM image to insert: ";
        cin >> inFileName;

        if (!insertImg.readImageFromFile(inFileName))
        {
            cout << "Fail to load the pattern file. Try again." << endl;
        }
        else
        {
            isFileValid = true;
        }

        // check the insert image size validality
        insertImgHeight = insertImg.getImageHeight();
        insertImgWidth = insertImg.getImageWidth();

        if (isFileValid && 
            (insertImgHeight > baseImageHeight || 
            insertImgWidth > baseImageWidth))
        {
            cout << "Error. The insert image size should not larger than the ";
            cout << "base image size." << endl;
            isFileValid = false;
        }
    }

    // handle the input of upper left corner
    while (!isInputValid)
    {
        cout << "Enter upper left corner to insert image row and column: ";
        isInputValid = handleInputFromKeyboard(upperLeftRow, upperLeftCol);

        if (isInputValid && (upperLeftRow < 0 || upperLeftCol < 0))
        {
            cout << "Invalid input value: " << endl;
            cout << "upper left row and upper left column should be ";
            cout << "greater and equal to 0." << endl;
            isInputValid = false;
        }
    }
    upperLeftCorner.setRowCol(upperLeftRow, upperLeftCol);

    // handle the transparency color options
    while (!isOptionValid)
    {
        cout << "1. Red" << endl;
        cout << "2. Green" << endl;
        cout << "3. Blue" << endl;
        cout << "4. Black" << endl;
        cout << "5. White" << endl;

        cout << "Enter int for transparecy color: ";
        cin >> option;

        if (option == SET_RED_OPTION)
        {
            transColor.setToRed();
            insertImg.setTransColor(transColor);
            isOptionValid = true;
        }
        else if (option == SET_GREEN_OPTION)
        {
            transColor.setToGreen();
            insertImg.setTransColor(transColor);
            isOptionValid = true;
        }
        else if (option == SET_BLUE_OPTION)
        {
            transColor.setToBlue();
            insertImg.setTransColor(transColor);
            isOptionValid = true;
        }
        else if (option == SET_BLACK_OPTION)
        {
            transColor.setToBlack();
            insertImg.setTransColor(transColor);
            isOptionValid = true;
        }
        else if (option == SET_WHITE_OPTION)
        {
            transColor.setToWhite();
            insertImg.setTransColor(transColor);
            isOptionValid = true;
        }
        else
        {
            cout << "Error option input: the input option should be ";
            cout << "1 - 5" << endl;
        }
    }

    // insert the image
    modifyImage(insertImg, upperLeftCorner);

}


// Private methods

bool ColorImageClass::readPpmFormatMagicNum(ifstream& inFile)
{
    string magicNum;
    inFile >> magicNum;

    if (!isInputValid(inFile, "magic number"))
    {
        return false;
    }

    if (magicNum != PPM_MAGIC_NUM)
    {
        cout << "Error found when trying to read magic number ";
        cout << "-expected P3 but found " << magicNum << endl;
        return false;
    }

    return true;
}

bool ColorImageClass::readPpmWidthHeight(ifstream& inFile)
{
    int width;
    int height;

    // deal with width input
    inFile >> width;
    if (!isInputValid(inFile, "width"))
    {
        return false;
    }

    // deal with width output
    inFile >> height;
    if (!isInputValid(inFile, "height"))
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

    imageRowSize = height;
    imageColSize = width;
    
    return true;
}

bool ColorImageClass::readPpmMaxVal(ifstream& inFile)
{
    int maxVal;
    inFile >> maxVal;

    if (!isInputValid(inFile, "ppm max value"))
    {
        return false;
    }

    if (maxVal != COLOR_MAX)
    {
        cout << "Invalid color maximum value" << endl;
        return false;
    }

    return true;
}

bool ColorImageClass::modifyImage(const Rectangle& pattern)
{
    if (imageRowSize == 0 && imageColSize == 0)
    {
        cout << "Error. the color image is empty" << endl;
        return false;
    }

    if (pattern.getRecHeight() == 0 && pattern.getRecWidth() == 0)
    {
        cout << "The rectangel pattern is empty. Nothing modified" << endl;
        return true;
    }

    int patternHeight = pattern.getRecHeight();
    int patternWidth = pattern.getRecWidth();
    int** mask = pattern.getImage();
    RowColumnClass increment;

    // run through the pattern once to make sure the pattern is within a 
    // valid range
    for (int i = 0; i < patternHeight; i++)
    {
        for (int j = 0; j < patternWidth; j++)
        {
            RowColumnClass location = pattern.getUpperLeft();
            increment.setRowCol(i,j);
            location.addRowColTo(increment);

            if (!isLocationValid(location))
            {
                cout << "error modify the image: the location of the ";
                cout << "rectangle is out of bound.";
                return false;
            }
        }
    }

    // if all goes well, then start modify the image
    for (int i = 0; i < patternHeight; i++)
    {
        for (int j = 0; j < patternWidth; j++)
        {
            RowColumnClass location = pattern.getUpperLeft();
            increment.setRowCol(i,j);
            location.addRowColTo(increment);
            
            if (mask[i][j] == 1)
            {
                ColorClass recColor = pattern.getColor();
                setColorAtLocation(location, recColor);
            }
        }
    }

    return true;
}

bool ColorImageClass::modifyImage(ColorImageClass& insertImg, 
                 const RowColumnClass& upperLeftCorner)
{
    if (imageRowSize == 0 && imageColSize == 0)
    {
        cout << "Error. the base image is empty" << endl;
        return false;
    }

    if (insertImg.getImageHeight() == 0 && insertImg.getImageWidth() == 0)
    {
        cout << "The insert image is empty. Nothing modified" << endl;
        return true;
    }

    int insertImgHeight = insertImg.getImageHeight();
    int insertImgWidth = insertImg.getImageWidth();
    ColorClass transColor = insertImg.getTranColor();
    RowColumnClass increment;

    // run through the insert image once to make sure the image is within a 
    // valid range of the base image
    for (int i = 0; i < insertImgHeight; i++)
    {
        for (int j = 0; j < insertImgWidth; j++)
        {
            RowColumnClass location = upperLeftCorner;
            increment.setRowCol(i,j);
            location.addRowColTo(increment);

            if (!isLocationValid(location))
            {
                cout << "error insert the image: the location of the ";
                cout << "image is out of bound.";
                return false;
            }
        }
    }

    // If all goes well, then start to insert the image
    for (int i = 0; i < insertImgHeight; i++)
    {
        for (int j = 0; j < insertImgWidth; j++)
        {
            RowColumnClass location = upperLeftCorner;
            increment.setRowCol(i,j);
            location.addRowColTo(increment);
            ColorClass insertImgColor;
            insertImg.getColorAtLocation(increment, insertImgColor);

            if (!insertImgColor.isSameColor(transColor))
            {
                setColorAtLocation(location, insertImgColor);
            }
        }
    }

    return true;
}


