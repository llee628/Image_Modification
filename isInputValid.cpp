/*
    Programmer: Leo Lee
    Date: Nov 11, 2021
    Purpose: This code provides the implementation of the isInputValid function
*/

#include <iostream>
#include <fstream>
#include <string>
#include "isInputValid.h"
#include "constants.h"

using namespace std;

bool isInputValid(ifstream& inFile, const string& eofCase)
{
    if (inFile.eof())
    {
        cout << "EOF before reading the " << eofCase << endl;
        return false;
    }
    else if (inFile.fail())
    {
        inFile.clear();
        inFile.ignore(BUFFER_CLEAR_NUM, '\n');
        cout << "Input type error" << endl;
        return false;
    }

    return true;

}