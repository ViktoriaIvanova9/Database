#include "../Headers/DoubleColumn.h"

DoubleColumn::DoubleColumn()
{
    this->columnType = (TypeColumn)1; /// 1 - DOUBLE in enum TypeColumn
}

DoubleColumn::DoubleColumn(string columnType, string nameColumn, vector<double> doubleArr)
{
    this->columnType = (TypeColumn)1;
    this->nameColumn = nameColumn;
    size_t size = doubleArr.size();

    for (size_t i = 0; i < size; ++i)
    {
        this->doubleArr.push_back(doubleArr.at(i));
    }
}

void DoubleColumn::insertValue(string value)
{
    try
    {
        double result = std::stod(value);  /// converting string to double
        this->doubleArr.push_back(result); /// push converted value in the double array
    }
    catch (const std::exception &e)
    {
        throw std::invalid_argument("Invalid value!");
    }
}

TypeColumn DoubleColumn::getColumnType() const
{
    return this->columnType;
}

string DoubleColumn::getNameColumn() const
{
    return this->nameColumn;
}

string DoubleColumn::getValueAt(size_t position) const
{
    return std::to_string(this->doubleArr.at(position)); /// converting the value to string
}

void DoubleColumn::setName(string nameColumn)
{
    this->nameColumn = nameColumn;
}

void DoubleColumn::setValueAt(size_t index, string value)
{
    if (index > doubleArr.size()) /// check if the index is bugger than the number of columns
    {
        throw std::invalid_argument("No such column!");
    }

    size_t currSize = doubleArr.size();
    vector<double> newArr;
    for (size_t i = 0; i < index; ++i)
    {
        newArr.push_back(doubleArr.at(i));
    }

    newArr.push_back(stod(value)); /// pushing value on the pointed index

    for (size_t i = index + 1; i < currSize; ++i)
    {
        newArr.push_back(doubleArr.at(i));
    }

    this->doubleArr = newArr;
}

void DoubleColumn::removeValueAt(size_t index)
{
    if (index > doubleArr.size())
    {
        throw std::invalid_argument("No such column!");
    }
    /// doubleArr.begin() is returning an iterator pointing to the first element of the vector
    this->doubleArr.erase(doubleArr.begin() + index, doubleArr.begin() + index + 1);
}
