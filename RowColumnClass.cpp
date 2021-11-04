#include <iostream>
#include "RowColumnClass.h"

using namespace std;

RowColumnClass::RowColumnClass()
{
    rowIdx = DEFAULT_ROW_COL;
    columnIdx = DEFAULT_ROW_COL;
}

RowColumnClass::RowColumnClass(int inRow, int inCol)
{
    rowIdx = inRow;
    columnIdx = inCol;
}

void RowColumnClass::setRowCol(int inRow, int inCol)
{
    rowIdx = inRow;
    columnIdx = inCol;
}

void RowColumnClass::setRow(int inRow)
{
    rowIdx = inRow;
}

void RowColumnClass::setCol(int inCol)
{
    columnIdx = inCol;
}

int RowColumnClass::getRow() const
{
    return rowIdx;
}

int RowColumnClass::getCol() const
{
    return columnIdx;
}

void RowColumnClass::addRowColTo(RowColumnClass &inRowCol)
{
    rowIdx += inRowCol.rowIdx;
    columnIdx += inRowCol.columnIdx;
}

void RowColumnClass::printRowCol() const
{
    cout << "[" << rowIdx << "," << columnIdx << "]";
}