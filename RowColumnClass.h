#ifndef _ROWCOLUMNCLASS_H_
#define _ROWCOLUMNCLASS_H_

/*
    Programmer: Leo Lee
    Date: Nov 3, 2021
    Purpose: This class represents a collection of row and column information
*/

#include "constants.h"

class RowColumnClass
{
  private:
    int rowIdx;
    int columnIdx;

  public:
    /*
        This default constructor simply sets both the row and column value of 
        the newly created RowColumnClass object to -99999.
    */
    RowColumnClass();

    /*
        This value constructorsimply sets the row and column values to the 
        corresponding values passed into the constructor.
    */
    RowColumnClass(int inRow, int inCol);

    /*
        These functions are simple “setter functions” that just directly set 
        the appropriate attribute(s) to the value(s) provided.
    */
    void setRowCol(int inRow, int inCol);
    void setRow(int inRow);
    void setCol(int inCol);

    
    // These functions return the appropriate attribute value to the caller.
    int getRow() const;
    int getCol() const;
    
    /*
        This function adds the row and column index values in the input
        parameter to the row and column index of the object the function
        is called on
    */
    void addRowColTo(RowColumnClass &inRowCol);

    // This function prints this object's attribute
    void printRowCol() const;
};





#endif