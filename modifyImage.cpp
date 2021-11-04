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

    // run through the pattern once to make sure the pattern is within a 
    // valid range
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
                image.setColorAtLocation(location, recColor);
            }
        }
    }

    return true;
}

bool modifyImage(ColorImageClass& baseImg, ColorImageClass& insertImg)
{
    if (baseImg.getImageHeight() == 0 && baseImg.getImageWidth() == 0)
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
            RowColumnClass location = insertImg.getUpLeftPos();
            increment.setRowCol(i,j);
            location.addRowColTo(increment);

            if (!baseImg.isLocationValid(location))
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
            RowColumnClass location = insertImg.getUpLeftPos();
            increment.setRowCol(i,j);
            location.addRowColTo(increment);
            ColorClass InsertImgColor;
            insertImg.getColorAtLocation(increment, InsertImgColor);

            if (!InsertImgColor.isSameColor(transColor))
            {
                baseImg.setColorAtLocation(location, InsertImgColor);
            }
        }
    }

    return true;
}