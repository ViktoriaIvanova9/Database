#ifndef __TABLE_H
#define __TABLE_H

#include "Column.h"
#include "IntColumn.h"
#include "StringColumn.h"
#include "DoubleColumn.h"

class Table
{
private:
    string nameTable;  /// name of the table
    string nameTableFile; /// name of the file where every table is saved
    size_t maxLengthColumn; /// length of a column

    vector<Column*> table; /// vector of pointers to Columns

public:
    Table(string nameTable, string nameTableFile, vector<Column*> table);
    ~Table(); /// destructor for the vector of pointers to column

    size_t getColumnsCount() const; /// getters for the csount of the columns

    TypeColumn getColumnTypeAt(size_t position) const; /// getting the type of the column at specific position

    void setMaxLen(size_t val); /// setter for the length of the column

    size_t getLinesCount() const; /// getter for the lines of the column

    Column* getColumn(size_t index); /// returning specific column

    string getNameTable() const; /// getter for the name of the table

    void setNameTable(string name); /// setter for the name of the table

};

#endif