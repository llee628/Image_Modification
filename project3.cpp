/*
    Programmer: Leo Lee
    Date: Nov 3, 2021
    Purpose: This program can read images from ppm files and provide three 
    differenct functionality to modify the image and write it to ppm file
*/


#include <iostream>
#include <string>
#include "ColorImageClass.h"
#include "annotateWithRectangle.h"
#include "annotatePatternFromFile.h"
#include "insertImage.h"

using namespace std;

int main()
{
    string inFileName;
    string outFileName;
    ColorImageClass baseImage;
    string mainMenuOption;
    bool isMainOptionValid = false;
    bool isExit = false;

    cout << "Enter string for PPM image file name to load: ";
    cin >> inFileName;

    if (baseImage.readImageFromFile(inFileName))
    {
        // handle the main options
        while (!isExit)
        {
            cout << "1. Annotate image with rectangle" << endl;
            cout << "2. Annotate image with pattern from file" << endl;
            cout << "3. Insert another image" << endl;
            cout << "4. Write out current image" << endl;
            cout << "5. Exit the program" << endl;

            cout << "Enter int for main menu choice: ";
            cin >> mainMenuOption;

            if (mainMenuOption == "1")
            {
                annotateWithRectangle(baseImage);
            }
            else if (mainMenuOption == "2")
            {
                annotatePatternFromFile(baseImage);
            }
            else if (mainMenuOption == "3")
            {
                insertImage(baseImage);
            }
            else if (mainMenuOption == "4")
            {
                cout << "Enter string for PPM file name to output: ";
                cin >> outFileName;
                baseImage.writeImageToFile(outFileName);
            }
            else if (mainMenuOption == "5")
            {
                cout << "Thank you for using this program" << endl;
                isExit = true;
            }
            else
            {
                cout << "Invalid input option. Please enter the option from ";
                cout << "1 - 5" << endl;
            }

        }
        
    }
    else
    {
        cout << "Fail to load the base image" << endl;
        cout << "Program ends." << endl;
    }

    return 0;

    

}