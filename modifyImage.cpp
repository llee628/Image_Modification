#include <iostream>
#include "modifyImage.h"

using namespace std;

bool modifyImage(ColorImageClass& image, Rectangle& pattern)
{
    if (image.getImageHeight() == 0 && image.getImageWidth() == 0)
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

    for (int i = 0; i < patternHeight; i++)
    {
        for (int j = 0; j < patternWidth; j++)
        {
            RowColumnClass location = pattern.getUpperLeft();
            increment.setRowCol(i,j);
            location.addRowColTo(increment);

            if (!image.isLocationValid(location))
            {
                cout << "error modify the image: the location of the ";
                cout << "rectangle is out of bound.";
                return false;
            }
            else
            {
                if (mask[i][j] == 1)
                {
                    ColorClass recColor = pattern.getColor();
                    image.setColorAtLocation(location, recColor);
                }
            }

        }
    }

    return true;
}