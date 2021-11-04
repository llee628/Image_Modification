#ifndef _INSERTIMAGE_H_
#define _INSERTIMAGE_H_

/*
    Programmer: Leo Lee
    Date: Nov 4, 2021
    Purpose: This function allows user to insert another image from a ppm file
    to the base image
*/

#include "ColorImageClass.h"
#include "ColorClass.h"
#include "handleInputFromKeyboard.h"
#include "modifyImage.h"

void insertImage(ColorImageClass& baseImage);

#endif