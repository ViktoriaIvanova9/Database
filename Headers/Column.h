#ifndef __COLUMN_H
#define __COLUMN_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

/// enum class for three types of columns
enum TypeColumn
{
    INT = 0,
    DOUBLE,
    STRING
};

class Column /// abstract class
{
protected:
    string nameColumn;     /// name of the column
    TypeColumn columnType; /// one of the possible types INT, DOUBLE, STRING

public:
    Column() = default;
    Column(string nameColumn, TypeColumn columnType); /// constructor with parametres
    virtual ~Column() = default;

    virtual void insertValue(string value) = 0; /// pure virtual function for inserting value

    virtual TypeColumn getColumnType() const = 0; /// pure virtual function for getting the type of the column

    virtual string getNameColumn() const = 0; /// pure virtual function for getting the name of the column

    virtual string getValueAt(size_t position) const = 0; /// pure virtual function for getting value at specific place

    virtual void setName(string name) = 0; /// pure virtual function for setting name of the column

    virtual void setValueAt(size_t index, string value) = 0; /// pure virtual function for setting value at any position

    virtual void removeValueAt(size_t index) = 0; /// pure virtual function for removing value at any position
};

#endif