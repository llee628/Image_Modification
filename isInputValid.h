/*
    Programmer: Leo Lee
    Date: Nov 11, 2021
    Purpose: This code provides the interface of the isInputValid
*/

#ifndef _ISINPUTVALID_H_
#define _ISINPUTVALID_H_

#include <fstream>
#include <string>

using namespace std;

// This function check if the file input state is valid
bool isInputValid(ifstream& inFile, const string& eofCase);



#endif