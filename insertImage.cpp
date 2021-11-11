#include <iostream>
#include <string>
#include "insertImage.h"

using namespace std;

void insertImage(ColorImageClass& baseImage)
{
    ColorImageClass insertImg;
    string inFileName;
    string option;
    ColorClass transColor;
    bool isFileValid = false;
    bool isInputValid = false;
    bool isOptionValid = false;
    int upperLeftRow;
    int upperLeftCol;
    int baseImageHeight = baseImage.getImageHeight();
    int baseImageWidth = baseImage.getImageWidth();
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
    insertImg.setUpLeftPos(upperLeftRow, upperLeftCol);

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
    modifyImage(baseImage, insertImg);

}