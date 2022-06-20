#include "../Headers/StringColumn.h"

StringColumn::StringColumn()
{
    this->columnType = (TypeColumn)2; /// 2 - STRING in enum TypeColumn
}
StringColumn::StringColumn(string columnType, string nameColumn, vector<string> stringArr)
{
    this->columnType = (TypeColumn)2;
    this->nameColumn = nameColumn;
    size_t size = stringArr.size();

    for (size_t i = 0; i < size; ++i)
    {
        this->stringArr.push_back(stringArr.at(i));
    }
}

void StringColumn::insertValue(string value)
{
    this->stringArr.push_back(value);
}

TypeColumn StringColumn::getColumnType() const
{
    return this->columnType;
}
string StringColumn::getNameColumn() const
{
    return this->nameColumn;
}

string StringColumn::getValueAt(size_t position) const
{
    return this->stringArr.at(position);
}

void StringColumn::setName(string name)
{
    this->nameColumn = name;
}

void StringColumn::setValueAt(size_t index, string value)
{
    if (index > stringArr.size())
    {
        throw std::invalid_argument("No such column!");
    }

    size_t currSize = stringArr.size();
    vector<string> newArr;
    for (size_t i = 0; i < index; ++i)
    {
        newArr.push_back(stringArr.at(i));
    }

    newArr.push_back(value);

    for (size_t i = index + 1; i < currSize; ++i)
    {
        newArr.push_back(stringArr.at(i));
    }
    this->stringArr = newArr;
}

void StringColumn::removeValueAt(size_t index)
{
    if (index > stringArr.size())
    {
        throw std::invalid_argument("No such column!");
    }
    this->stringArr.erase(stringArr.begin() + index, stringArr.begin() + index + 1);
}