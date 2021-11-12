/*
    Programmer: Leo Lee
    Date: Nov 10, 2021
    Purpose: This code is the implementation of the ColorClass methods
*/

/*
    Modification for resubmission:
    1. add a readColorFromFile method
    2. add a writeColorToFile method 
*/


#include <iostream>
#include <fstream>
#include "ColorClass.h"
#include "isInputValid.h"

using namespace std;

// ColorClass Methods
ColorClass::ColorClass()
{
    redVal = COLOR_MAX;
    greenVal = COLOR_MAX;
    blueVal = COLOR_MAX;
}

ColorClass::ColorClass(int inRed, int inGreen, int inBlue)
{
    setTo(inRed, inGreen, inBlue);
}

void ColorClass::setToBlack()
{
    redVal = COLOR_MIN;
    greenVal = COLOR_MIN;
    blueVal = COLOR_MIN;
}

void ColorClass::setToRed()
{
    redVal = COLOR_MAX;
    greenVal = COLOR_MIN;
    blueVal = COLOR_MIN;
}

void ColorClass::setToGreen()
{
    redVal = COLOR_MIN;
    greenVal = COLOR_MAX;
    blueVal = COLOR_MIN;
}

void ColorClass::setToBlue()
{
    redVal = COLOR_MIN;
    greenVal = COLOR_MIN;
    blueVal = COLOR_MAX;
}

void ColorClass::setToWhite()
{
    redVal = COLOR_MAX;
    greenVal = COLOR_MAX;
    blueVal = COLOR_MAX;
}

bool ColorClass::setTo(int inRed, int inGreen, int inBlue)
{
    
    if (!checkColorValid(inRed) || 
        !checkColorValid(inGreen) || 
        !checkColorValid(inBlue))
    {
        return false;
    }

    redVal = inRed;
    greenVal = inGreen;
    blueVal = inBlue;

    return true;

}

bool ColorClass::setTo(const ColorClass &inColor)
{
    return setTo(inColor.redVal, inColor.greenVal, inColor.blueVal);
}

bool ColorClass::addColor(ColorClass &rhs)
{
    int newRed = redVal + rhs.redVal;
    int newGreen = greenVal + rhs.redVal;
    int newBlue = blueVal + rhs.blueVal;

    if (!checkColorValid(newRed) || 
        !checkColorValid(newGreen) || 
        !checkColorValid(newBlue))
    {
        return false;
    }

    redVal = newRed;
    greenVal = newGreen;
    blueVal = newBlue;

    return true;

}

bool ColorClass::subtractColor(ColorClass &rhs)
{
    int newRed = redVal - rhs.redVal;
    int newGreen = greenVal - rhs.redVal;
    int newBlue = blueVal - rhs.blueVal;

    if (!checkColorValid(newRed) || 
        !checkColorValid(newGreen) || 
        !checkColorValid(newBlue))
    {
        return false;
    }

    redVal = newRed;
    greenVal = newGreen;
    blueVal = newBlue;

    return true;
}

bool ColorClass::adjustBrightness(double adjFactor)
{
    int newRed = static_cast< int >(redVal * adjFactor);
    int newGreen = static_cast< int >(greenVal * adjFactor);
    int newBlue = static_cast< int >(blueVal * adjFactor);

    if (!checkColorValid(newRed) || 
        !checkColorValid(newGreen) || 
        !checkColorValid(newBlue))
    {
        return false;
    }

    redVal = newRed;
    greenVal = newGreen;
    blueVal = newBlue;

    return true;
}

bool ColorClass::readColorFromFile(ifstream& inFile)
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

    if (!checkColorValid(red))
    {
        cout << "Invalid red color: " << red << endl;
        return false;
    }

    if (!checkColorValid(green))
    {
        cout << "Invalid green color: " << green << endl;
        return false;
    }

    if (!checkColorValid(blue))
    {
        cout << "Invalid blue color: " << blue << endl;
        return false;
    }

    setTo(red, green, blue);
    return true;
}

void ColorClass::writeColorToFile(ofstream& outFile)
{
    outFile << redVal << " " << greenVal << " " << blueVal;
}

bool ColorClass::isSameColor(const ColorClass& rhs)
{
    int inRed = rhs.getRed();
    int inGreen = rhs.getGreen();
    int inBlue = rhs.getBlue();

    return (redVal == inRed && greenVal == inGreen && blueVal == inBlue);
}

void ColorClass::printComponentValues() const
{
    cout << "R: " << redVal << " G: " << greenVal << " B: " << blueVal;
}


// private methods

bool ColorClass::checkColorValid(int colorVal)
{
    if (colorVal > COLOR_MAX || colorVal < COLOR_MIN)
    {
        return false;
    }

    return true;
}