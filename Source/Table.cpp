#include "../Headers/Table.h"

Table::Table(string nameTable, string nameTableFile, vector<Column *> table)
{
    this->nameTable = nameTable;
    this->nameTableFile = nameTableFile;
    size_t size = table.size();

    for (size_t i = 0; i < size; ++i)
    {
        this->table.push_back(table.at(i));
    }
}

Table::~Table()
{
    size_t size = this->table.size();

    for (size_t i = 0; i < size; ++i)
    {
        delete table.at(i);
    }
}

size_t Table::getColumnsCount() const
{
    return this->table.size();
}

TypeColumn Table::getColumnTypeAt(size_t position) const
{
    return table.at(position)->getColumnType();
}

void Table::setMaxLen(size_t value)
{
    this->maxLengthColumn = value;
}

size_t Table::getLinesCount() const
{
    return this->maxLengthColumn;
}

Column *Table::getColumn(size_t index)
{
    if (index >= table.size())
    {
        throw std::invalid_argument("No such column!");
    }
    return this->table.at(index);
}

string Table::getNameTable() const
{
    return this->nameTable;
}

void Table::setNameTable(string name)
{
    this->nameTable = name;
}