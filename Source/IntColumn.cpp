#include "../Headers/IntColumn.h"

IntColumn::IntColumn()
{
    this->columnType = (TypeColumn)0; /// 0 - INT in enum TypeColumn
}
IntColumn::IntColumn(string columnType, string nameColumn, vector<int> intArr)
{
    this->columnType = (TypeColumn)0;
    this->nameColumn = nameColumn;
    size_t size = intArr.size();

    for (size_t i = 0; i < size; ++i)
    {
        this->intArr.push_back(intArr.at(i));
    }
}

void IntColumn::insertValue(string value)
{
    try
    {
        int result = std::stoi(value);
        this->intArr.push_back(result);
    }
    catch (const std::exception &e)
    {
        throw std::invalid_argument("Invalid value!");
    }
}

TypeColumn IntColumn::getColumnType() const
{
    return this->columnType;
}

string IntColumn::getNameColumn() const
{
    return this->nameColumn;
}

string IntColumn::getValueAt(size_t position) const
{
    return std::to_string(this->intArr.at(position));
}

void IntColumn::setName(string nameColumn)
{
    this->nameColumn = nameColumn;
}

void IntColumn::setValueAt(size_t index, string value)
{
    if (index > intArr.size())
    {
        throw std::invalid_argument("No such column!");
    }
    size_t currSize = intArr.size();
    vector<int> newArr;
    for (size_t i = 0; i < index; ++i)
    {
        newArr.push_back(intArr.at(i));
    }
    newArr.push_back(stoi(value));
    for (size_t i = index + 1; i < currSize; ++i)
    {
        newArr.push_back(intArr.at(i));
    }
    this->intArr = newArr;
}

void IntColumn::removeValueAt(size_t index)
{
    if (index > intArr.size())
    {
        throw std::invalid_argument("No such column!");
    }
    this->intArr.erase(intArr.begin() + index, intArr.begin() + index + 1);
}