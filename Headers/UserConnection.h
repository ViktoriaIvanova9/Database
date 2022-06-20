#ifndef __USER_CONNECTION_H
#define __USER_CONNECTION_H

#include "Table.h"

const string dbNames = "DatabaseFile.txt";

class UserConnection
{
private:
    Table *dataBase = nullptr; /// creating a pointer to a table pointin to nullptr
    string fileName; /// name of the file we need

    bool isSaved = false, isOpened = false; /// checker if the file is saved or opened

    void checkType(string line, vector<Column *> &tempTable); /// check the type of a column
    void readTable(string filePath); /// read table from file

    void writeToTableFile(); /// writing table to file

    void openFile(string &fileName); /// opening file
    void saveFile(); /// saving table in the same file
    void saveFileAs(string filePath); /// saving table in another file
    void closeFile(); /// closing table file
    void help(); /// helper for all functions
    void exit(); /// exiting program

    void importFile(string fileName); /// adding a new table to the database

    void showAllTables(); /// showing a list of all tables

    void describeTable(); /// describe the types of a table

    void printTable(); /// print a table from file

    void exportTableToFile(string tableName, string fileName); /// saving table to file

    void selectValueToPrint(int columnNumber, string value); /// printing specific value

    void deleteRows(size_t column,string value); /// delete specific rows of a table

    void updateTable(size_t searchColumn,size_t targetColumn,string searchValue,string targetValue); /// change value of some positions in a table

    void renameTable(string newTableName); /// change the name of a table

    void countRowsWithValue(size_t columnNumber, string searchedValue); /// count how many rows consist of specific value

public:
    void runProgram();

     ~UserConnection(); /// destructor for the dynamic data

};

#endif