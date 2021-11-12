#ifndef _HANDLEINPUTFROMKEYBOARD_H_
#define _HANDLEINPUTFROMKEYBOARD_H_

/*
    Programmer: Leo Lee
    Date: Nov 4, 2021
    Purpose: These function overload different situations when using cin
*/

#include "constants.h"

// handle single int input and error check
bool handleInputFromKeyboard(int& intIn1);

// handle two int inputs and error check
bool handleInputFromKeyboard(int& intIn1, int& intIn2);



#endif