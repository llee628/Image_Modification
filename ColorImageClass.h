#ifndef _COLORIMAGECLASS_H_
#define _COLORIMAGECLASS_H_

/*
    Programmer: Leo Lee
    Date: Nov 2, 2021
    Purpose: Define a class that represent a image containing RGB value in each
    pixel.s
*/

#include <string>
#include <fstream>
#include "ColorClass.h"
#include "RowColumnClass.h"
#include "constants.h"

using namespace std;

class ColorImageClass
{
  private:
    ColorClass** image;
    int imageRowSize;
    int imageColSize;
    RowColumnClass upperLeftPos;
    ColorClass transparencyColor;

    // This method check if the color value in a pixel is within a valid range
    bool isColorValid(int colorVal);

    // This method read and check the image format magic number from ppm file
    bool readPpmFormatMagicNum(ifstream& inFile);

    // This method read and check the image height and width from ppm file
    bool readPpmWidthHeight(ifstream& inFile);

    // This method read and check the ppm image max value from ppm file
    bool readPpmMaxVal(ifstream& inFile);

    // This method read and check a set of rgb value from ppm file
    bool readPpmRgb(ifstream& inFile, ColorClass& color, int row, int col);

    // This method check if the input stats is valid
    bool isInputValid(ifstream& inFile, const string& eofCase);

  public:
    /*
        The default constructor set width and height to 0 and set image ptr to
        NULL
    */  
    ColorImageClass();

    /*
        The constructor create a image of size row*column with the given row 
        and column input and set all pixel to the black
    */
    ColorImageClass(int width, int height);

    /*
        Initialize the image with its size and set all pixel to black
    */
    void initializeTo();

    /*
        This function initializes all image pixels to the color provided 
        via input
    */
    void initializeTo(ColorClass &inColor);

    /*
        This function performs a pixel-wise addition, such that each pixel in 
        the image has the pixel in the corresponding location in the right hand 
        side input image added to it. If the result of one or more of the pixel 
        additions required color value clipping, this function returns true, 
        otherwise it returns false.
    */
    bool addImageTo(ColorImageClass &rhsImg);

    /*
        This function causes the image's pixel values to be set to the sum of 
        the corresponding pixels in each image in the imagesToAdd input 
        parameter. 
    */
    bool addImages(int numImgsToAdd, ColorImageClass imagesToAdd []);

    /*
        This function attempts to set the pixel at the location specified by 
        the “inRowCol” parameter to the color specified via the “inColor”
        parameter. If the location specified is a valid location for the image, 
        the pixel value is changed and the function returns true, otherwise the 
        image is not modified in ANY way, and the function returns false.
    */
    bool setColorAtLocation(RowColumnClass &inRowCol, ColorClass &inColor);

    /*
        If the row/column provided is a valid row/column for the image, 
        this function returns true and the output parameter "outColor" is 
        assigned to the color of the image pixel at that location. f the 
        row/column is invalid then the function returns false, and the output 
        parameter "outColor" is not modified in any way.
    */
    bool getColorAtLocation(RowColumnClass &inRowCol, ColorClass &outColor);

    /*
        This method set the upper left corner position for the image by user
        input the position
    */
    void setUpLeftPos(int Row, int Col);

    /*
        This method set the transparency color directly by the rhs color
    */
    void setTransColor(const ColorClass& rhs)
    {
        transparencyColor.setTo(rhs);
    }

    // This method check if the row and column index are within a valid range
    bool isLocationValid(RowColumnClass &inRowCol);

    // This function prints the contents of the image to the screen.
    void printImage() const;

    /*
        Read image from a ppm file. If read successfully, return true,
        otherwise, return false
    */
    bool readImageFromFile(const string& inputFile);

    /*
        Write the image to a file as a ppm format. If write successfully,
        return true, otherwise, return false.
    */
    bool writeImageToFile(const string& outputFile);

    //////// inline get data member methods ////////////////
    int getImageHeight() const
    {
        return imageRowSize;
    }

    int getImageWidth() const
    {
        return imageColSize;
    }

    ColorClass** getImage() const
    {
        return image;
    }

    ColorClass getTranColor() const
    {
        return transparencyColor;
    }

    RowColumnClass getUpLeftPos() const
    {
        return upperLeftPos;
    }
    /////// end of inline get data member methods /////////
};


#endif