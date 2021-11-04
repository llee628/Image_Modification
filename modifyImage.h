#ifndef _MODIFYIMAGE_H_
#define _MODIFYIMAGE_H_

/*
    Programmer: Leo Lee
    Date: Nov 4, 2021
    Purpose: This function modify image base on pattern information. If modify 
    succeed, return true. Otherwise, return false
*/

#include "ColorImageClass.h"
#include "Rectangle.h"

bool modifyImage(ColorImageClass& image, Rectangle& pattern);






#endif