#ifndef _COLORCLASS_H_
#define _COLORCLASS_H_

/*
    Programmer: Leo Lee
    Date: Nov 3, 2021
    Purpose: This code is the interface of the ColorClass
*/

/*
    Modification for resubmission:
    1. add a readColorFromFile method
    2. add a writeColorToFile method 
*/

#include "constants.h"


// This class represents colors in a pixel
class ColorClass
{
  private:
    int redVal;
    int greenVal;
    int blueVal;

    // This method check if the color value from a file is within a valid range
    bool checkColorValid(int colorVal);

  public:
    /*
        The default constructor will set the color's initial RGB to the color
        full white
    */
    ColorClass();

    /*
        The value ctor will set the color's initial RGB values to the values
        provided
    */
    ColorClass(int inRed, int inGreen, int inBlue);
    

    /*
        The following member functions set the color values to the appropriate
        values to form the color indicated. In all cases, these functions will
        result in "full" colors
    */
    void setToBlack();
    void setToRed();
    void setToGreen();
    void setToBlue();
    void setToWhite();

    // This function sets the color object's RGB values to the provided values.
    bool setTo(int inRed, int inGreen, int inBlue);

    /*
        This function sets the color's component color values to the same as 
        those in the "inColor" input parameter.
    */
    bool setTo(const ColorClass &inColor);

    /*
        This function causes each RGB value to have the corresponding value 
        from the input parameter color added to it. If any resulting color 
        value would end up outside the valid color value range, the function
        return false and not change the original value
    */
    bool addColor(ColorClass &rhs);

    /*
        This function causes each RGB value to have the corresponding value 
        from the input parameter subtracted from it. If any resulting color 
        value would end up outside the valid color value range, the function
        return false and not change the original value
    */
    bool subtractColor(ColorClass &rhs);

    /*
        This function performs a brightness adjustment which multiplies each 
        RGB value by the adjustment factor provided.
    */
    bool adjustBrightness(double adjFactor);

    /*
        This method read the rgb values from a file
    */
    bool readColorFromFile(ifstream& inFile);

    /*
        This method write the rgb value to a file
    */
    void writeColorToFile(ofstream& outFile);

    /*
        check if the rhs color is the same as the color of this object
    */
    bool isSameColor(const ColorClass& rhs);

    // Prints the component color values
    void printComponentValues() const;

    /*
        The following inline methods get the r, g, and b values
    */
    int getRed() const
    {
        return redVal;
    }
    
    int getGreen() const
    {
        return greenVal;
    }

    int getBlue() const
    {
        return blueVal;
    }


};


#endif