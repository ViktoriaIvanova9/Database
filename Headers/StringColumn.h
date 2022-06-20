#ifndef __STRING_COLUMN_H
#define __STRING_COLUMN_H

#include "Column.h"

class StringColumn : public Column ///inherit class Column
{
private:
    vector<string> stringArr; /// vector of string values

public:
    StringColumn();
    StringColumn(string columnType, string nameColumn, vector<string> stringArr);

    virtual void insertValue(string value) override;

    virtual TypeColumn getColumnType() const override;
    
    virtual string getNameColumn() const override;

    virtual string getValueAt(size_t position) const override;

    virtual void setName(string name) override;

    virtual void setValueAt(size_t index,string value) override;

    virtual void removeValueAt(size_t index) override;
};

#endif