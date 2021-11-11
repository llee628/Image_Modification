#include <iostream>
#include <string>
#include "annotateWithRectangle.h"
#include "constants.h"

using namespace std;

void annotateWithRectangle(ColorImageClass& baseImage)
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
    option = -1;
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
    option = -1;
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
    modifyImage(baseImage, recPattern);




}