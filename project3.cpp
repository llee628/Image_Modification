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
#include "constants.h"

using namespace std;

int main()
{
    string inFileName;
    string outFileName;
    ColorImageClass baseImage;
    string mainMenuOption;
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

            if (mainMenuOption == ANNOTATE_WITH_RECTANGLE_OPTION)
            {
                baseImage.annotateWithRectangle();
            }
            else if (mainMenuOption == ANNOTATE_PATTERN_FROM_FILE_OPTION)
            {
                annotatePatternFromFile(baseImage);
            }
            else if (mainMenuOption == INSERT_ANOTHER_IMAGE_OPTION)
            {
                insertImage(baseImage);
            }
            else if (mainMenuOption == WRITE_CURRENT_IMAGE_OPTION)
            {
                cout << "Enter string for PPM file name to output: ";
                cin >> outFileName;
                baseImage.writeImageToFile(outFileName);
            }
            else if (mainMenuOption == EXIT_OPTION)
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