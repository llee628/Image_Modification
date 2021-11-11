/*
    Programmer: Leo Lee
    Date: Nov 10, 2021
    Purpose: This code provides the implementation of the 
    handleInputFromKeyboard functions.
*/

#include <iostream>
#include "handleInputFromKeyboard.h"

using namespace std;

bool handleInputFromKeyboard(int& intIn1)
{
    cin >> intIn1;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(BUFFER_CLEAR_NUM, '\n');
        cout << endl << "Invalid input type:" << endl;
        cout << "The input type should be a int" << endl;
        return false;
    }

    return true;
}

bool handleInputFromKeyboard(int& intIn1, int& intIn2)
{
    cin >> intIn1 >> intIn2;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(BUFFER_CLEAR_NUM, '\n');
        cout << endl << "Invalid input type:" << endl;
        cout << "The input type should be a int" << endl;
        return false;
    }

    return true;
}