#ifndef __INT_COLUMN_H
#define __INT_COLUMN_H

#include "Column.h"

class IntColumn: public Column /// inherit class Column
{
private:
    vector<int> intArr; /// vector of int values
public:
    IntColumn();
    IntColumn(string columnType, string nameColumn, vector<int> intArr);

    virtual void insertValue(string value) override;

    virtual TypeColumn getColumnType() const override;
    
    virtual string getNameColumn() const override;

    virtual string getValueAt(size_t position) const override;

    virtual void setName(string name) override;

    virtual void setValueAt(size_t index,string value) override;

    virtual void removeValueAt(size_t index) override;
};


#endif