#ifndef _ANNOTATEPARRERNFROMFILE_H_
#define _ANNOTATEPARRERNFROMFILE_H_

/*
    Programmer: Leo Lee
    Date: Nov 4, 2021
    Purpose: This function allows user to read a pattern from a file and 
    annotates it on the base image
*/

#include "ColorImageClass.h"
#include "Rectangle.h"
#include "ColorClass.h"
#include "modifyImage.h"

void annotatePatternFromFile(ColorImageClass& baseImage);

#endif