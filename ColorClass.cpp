/*
    Programmer: Leo Lee
    Date: Nov 10, 2021
    Purpose: This code is the implementation of the ColorClass methods
*/


#include <iostream>
#include "ColorClass.h"

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
    bool isClipped = false;

    redVal = clipColor(inRed, isClipped);
    greenVal = clipColor(inGreen, isClipped);
    blueVal = clipColor(inBlue, isClipped);

    return isClipped;

}

bool ColorClass::setTo(const ColorClass &inColor)
{
    return setTo(inColor.redVal, inColor.greenVal, inColor.blueVal);
}

bool ColorClass::addColor(ColorClass &rhs)
{
    bool isClipped = false;

    redVal += rhs.redVal;
    greenVal += rhs.greenVal;
    blueVal += rhs.blueVal;

    redVal = clipColor(redVal, isClipped);
    greenVal = clipColor(greenVal, isClipped);
    blueVal = clipColor(blueVal, isClipped);

    return isClipped;

}

bool ColorClass::subtractColor(ColorClass &rhs)
{
    bool isClipped = false;

    redVal -= rhs.redVal;
    greenVal -= rhs.greenVal;
    blueVal -= rhs.blueVal;

    redVal = clipColor(redVal, isClipped);
    greenVal = clipColor(greenVal, isClipped);
    blueVal = clipColor(blueVal, isClipped);

    return isClipped;
}

bool ColorClass::adjustBrightness(double adjFactor)
{
    bool isClipped = false;

    redVal = static_cast< int >(redVal*adjFactor);
    greenVal = static_cast< int >(greenVal*adjFactor);
    blueVal = static_cast< int >(blueVal*adjFactor);

    redVal = clipColor(redVal, isClipped);
    greenVal = clipColor(greenVal, isClipped);
    blueVal = clipColor(blueVal, isClipped);

    return isClipped;
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

int ColorClass::clipColor(const int colorAmount, bool& isClipped)
{
    if (colorAmount > COLOR_MAX)
    {
        isClipped = true;
        return COLOR_MAX;
    }
    else if (colorAmount < COLOR_MIN)
    {
        isClipped = true;
        return COLOR_MIN;
    }

    return colorAmount;
}