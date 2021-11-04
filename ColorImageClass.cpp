#include <iostream>
#include <fstream>
#include "ColorImageClass.h"


using namespace std;

ColorImageClass::ColorImageClass()
{
    image = NULL;
    imageRowSize = 0;
    imageColSize = 0;
    upperLeftPos.setRowCol(0, 0);
}

ColorImageClass::ColorImageClass(int width, int height)
{
    imageColSize = width;
    imageRowSize = height;
    upperLeftPos.setRowCol(0, 0);

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

void ColorImageClass::setUpLeftPos(int Row, int Col)
{
    // set the corner position
    upperLeftPos.setRowCol(Row, Col);
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
                cout<<"--";
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
            ColorClass color;
            if (readPpmRgb(inFile, color, i, j))
            {
                image[i][j].setTo(color);
            }
            else
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
            int r = image[i][j].getRed();
            int g = image[i][j].getGreen();
            int b = image[i][j].getBlue();

            outFile << r << " " << g << " " << b;
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


// Private methods


bool ColorImageClass::isColorValid(int colorVal)
{
    if (colorVal > COLOR_MAX || colorVal < COLOR_MIN)
    {
        return false;
    }

    return true;
}

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

bool ColorImageClass::readPpmRgb(
    ifstream& inFile, 
    ColorClass& color, 
    int row, 
    int col)
{
    int red;
    int green;
    int blue;

    inFile >> red;
    if (!isInputValid(inFile, "red value"))
    {
        return false;
    }

    inFile >> green;
    if (!isInputValid(inFile, "green value"))
    {
        return false;
    }

    inFile >> blue;
    if (!isInputValid(inFile, "blue value"))
    {
        return false;
    }

    if (!isColorValid(red))
    {
        cout << "Invalid red color: " << red << " ";
        cout << "at row: " << row << " column: " << col << endl;
        return false;
    }

    if (!isColorValid(green))
    {
        cout << "Invalid green color: " << green << " ";
        cout << "at row: " << row << " column: " << col << endl;
        return false;
    }

    if (!isColorValid(blue))
    {
        cout << "Invalid blue color: " << blue << " ";
        cout << "at row: " << row << " column: " << col << endl;
        return false;
    }

    color.setTo(red, green, blue);
    return true;

}

bool ColorImageClass::isInputValid(ifstream& inFile, const string& eofCase)
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

