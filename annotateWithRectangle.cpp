#include <iostream>
#include <string>
#include "annotateWithRectangle.h"

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

        if (option == "1")
        {
            recPattern.specifyRecByCorners();
            isOptionValid = true;
        }
        else if (option == "2")
        {
            recPattern.specifyRecByCornerAndDim();
            isOptionValid = true;
        }
        else if (option == "3")
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

        if (option == "1")
        {
            recColor.setToRed();
            recPattern.setColor(recColor);
            isOptionValid = true;
        }
        else if (option == "2")
        {
            recColor.setToGreen();
            recPattern.setColor(recColor);
            isOptionValid = true;
        }
        else if (option == "3")
        {
            recColor.setToBlue();
            recPattern.setColor(recColor);
            isOptionValid = true;
        }
        else if (option == "4")
        {
            recColor.setToBlack();
            recPattern.setColor(recColor);
            isOptionValid = true;
        }
        else if (option == "5")
        {
            recColor.setToWhite();
            recPattern.setColor(recColor);
            isOptionValid = true;
        }
        else
        {
            cout << "Error option input: the input option should be ";
            cout << "1 - 3" << endl;
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

        if (option == "1")
        {
            recPattern.setFilled(false);
            isOptionValid = true;
        }
        else if (option == "2")
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