#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

/*
    Programmer: Leo Lee
    Date: Nov 3, 2021
    Purpose: This .h file contains every global constant variable required for
    the project3
*/

#include <string>
using namespace std;

// global constant variables
const int COLOR_MAX = 255;
const int COLOR_MIN = 0;
const int DEFAULT_ROW_COL = -99999;
const int BUFFER_CLEAR_NUM = 200;

const string PPM_MAGIC_NUM = "P3";

const string ANNOTATE_WITH_RECTANGLE_OPTION = "1";
const string ANNOTATE_PATTERN_FROM_FILE_OPTION = "2";
const string INSERT_ANOTHER_IMAGE_OPTION = "3";
const string WRITE_CURRENT_IMAGE_OPTION = "4";
const string EXIT_OPTION = "5";

const string BY_CORNERS_OPTION = "1";
const string BY_CORNER_AND_DIM_OPTION = "2";
const string BY_CENTER_AND_DIM_OPTION = "3";

const string SET_RED_OPTION = "1";
const string SET_GREEN_OPTION = "2";
const string SET_BLUE_OPTION = "3";
const string SET_BLACK_OPTION = "4";
const string SET_WHITE_OPTION = "5";

const string NOT_FILLED_OPTION = "1";
const string FILLED_OPTION = "2";




#endif