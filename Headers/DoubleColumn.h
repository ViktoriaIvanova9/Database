#ifndef __DOUBLE_COLUMN_H
#define __DOUBLE_COLUMN_H

#include "Column.h"

class DoubleColumn : public Column /// inherit class Column
{
private:
    vector<double> doubleArr; /// vector of dauble values

public:
    DoubleColumn();                                                               /// default constructor for the double column
    DoubleColumn(string columnType, string nameColumn, vector<double> doubleArr); /// constructor with parameters

    virtual void insertValue(string value) override; /// virtual function for inserting value

    virtual TypeColumn getColumnType() const override; /// virtual function for getting the type of the column

    virtual string getNameColumn() const override; /// virtual function for getting the name of the column

    virtual string getValueAt(size_t position) const override; /// virtual function for getting value at specific place

    virtual void setName(string name) override; /// virtual function for setting name of the column

    virtual void setValueAt(size_t index, string value) override; /// virtual function for setting value at any position

    virtual void removeValueAt(size_t index) override; /// virtual function for removing value at any index
};

#endif