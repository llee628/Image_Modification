#include <iostream>
#include <string>
#include "annotatePatternFromFile.h"

using namespace std;

void annotatePatternFromFile(ColorImageClass& baseImage)
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

        if (option == "1")
        {
            patternColor.setToRed();
            pattern.setColor(patternColor);
            isOptionValid = true;
        }
        else if (option == "2")
        {
            patternColor.setToGreen();
            pattern.setColor(patternColor);
            isOptionValid = true;
        }
        else if (option == "3")
        {
            patternColor.setToBlue();
            pattern.setColor(patternColor);
            isOptionValid = true;
        }
        else if (option == "4")
        {
            patternColor.setToBlack();
            pattern.setColor(patternColor);
            isOptionValid = true;
        }
        else if (option == "5")
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
    modifyImage(baseImage, pattern);


}