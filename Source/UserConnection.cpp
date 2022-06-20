#include "../Headers/UserConnection.h"

void UserConnection::checkType(string line, vector<Column *> &tempTable)
{
    if (line == "int")
    {
        tempTable.push_back(new IntColumn());
    }
    else if (line == "double")
    {
        DoubleColumn doubleTypeColumn;
        tempTable.push_back(new DoubleColumn());
    }
    else if (line == "string")
    {
        StringColumn stringTypeColumn;
        tempTable.push_back(new StringColumn());
    }
    else
        throw std::logic_error("Invalid type!");
}

void UserConnection::readTable(string filePath)
{
    std::ifstream fileToRead;
    fileToRead.open(filePath, std::ios::in);

    if (!fileToRead.is_open())
    {
        throw std::invalid_argument("Error while opening file!");
    }

    size_t counter = 0; /// counter for writing rows of the table file
    string nameTable;
    vector<Column *> temp; 

    string line;

    if (fileToRead.is_open())
    {
        int firstIndex;

        while (getline(fileToRead, line))
        {
            firstIndex = line.find('|');
            if (counter == 0) /// reading the first row of the file
            {
                nameTable = line;
            }
            else if (counter == 1)  /// reading the second row of the file
            {
                if (firstIndex == -1)
                {
                    checkType(line, temp);
                }
                else
                {
                    string columnType;
                    int oldIndex = 0;
                    while (firstIndex != -1)
                    {
                        columnType = line.substr(oldIndex, firstIndex - oldIndex);
                        oldIndex = firstIndex + 1;
                        firstIndex = line.find('|', oldIndex);

                        checkType(columnType, temp);
                    }

                    columnType = line.substr(oldIndex);
                    checkType(columnType, temp);
                }
            }
            else if (counter == 2) /// reading the third row of the file
            {
                vector<string> columnName;

                if (firstIndex == -1)
                {
                    temp.at(0)->setName(line);
                }
                else
                {
                    int oldIndex = 0;
                    while (firstIndex != -1)
                    {
                        columnName.push_back(line.substr(oldIndex, firstIndex - oldIndex));
                        oldIndex = firstIndex + 1;
                        firstIndex = line.find('|', oldIndex);
                    }

                    columnName.push_back(line.substr(oldIndex));

                    size_t columnCount = columnName.size();
                    for (size_t i = 0; i < columnCount; ++i)
                    {
                        temp.at(i)->setName(columnName.at(i));
                    }
                }
            }
            else /// reading the rest of the file
            {
                string cellValue;
                int counterColumns = 0;

                if (firstIndex == -1)
                {
                    temp.at(counterColumns)->insertValue(line);
                }
                else
                {
                    int oldIndex = 0;
                    while (firstIndex != -1)
                    {
                        cellValue = line.substr(oldIndex, firstIndex - oldIndex);
                        oldIndex = firstIndex + 1;
                        firstIndex = line.find('|', oldIndex);

                        temp.at(counterColumns)->insertValue(cellValue);
                        counterColumns++;
                    }

                    cellValue = line.substr(oldIndex);
                    temp.at(counterColumns)->insertValue(cellValue);
                }
            }

            counter++;
        }
    }

    this->dataBase = new Table(nameTable, filePath, temp);
    this->dataBase->setMaxLen(counter - 3);
    this->fileName = filePath;

    fileToRead.close();

    isOpened = true;
    isSaved = true;
}

void UserConnection::writeToTableFile()
{
    std::ofstream fileToWrite;
    fileToWrite.open(this->fileName, std::ios::out);

    if (!fileToWrite.is_open())
    {
        throw std::invalid_argument("Can't open file!");
    }

    fileToWrite << dataBase->getNameTable() << endl; /// writing the name of the table
    size_t columnsCount = this->dataBase->getColumnsCount();

    TypeColumn type;

    for (size_t i = 0; i < columnsCount; ++i) /// writing the types of the columns
    {
        type = dataBase->getColumnTypeAt(i);

        if (type == 0)
        {
            fileToWrite << "int";
        }
        else if (type == 1)
        {
            fileToWrite << "double";
        }
        else if (type == 2)
        {
            fileToWrite << "string";
        }
        else
            throw std::logic_error("Wrong type!");

        if (i == columnsCount - 1)
        {
            fileToWrite << endl;
        }
        else
        {
            fileToWrite << "|";
        }
    }

    for (size_t i = 0; i < columnsCount; ++i) /// writing the names of the columns
    {
        fileToWrite << dataBase->getColumn(i)->getNameColumn();

        if (i == columnsCount - 1)
        {
            fileToWrite << endl;
        }
        else
        {
            fileToWrite << "|";
        }
    }

    size_t rowsCount = dataBase->getLinesCount();

    for (size_t i = 0; i < rowsCount; ++i) /// writing information of every column
    {
        for (size_t j = 0; j < columnsCount; ++j)
        {
            fileToWrite << dataBase->getColumn(j)->getValueAt(i);

            if (j == columnsCount - 1 && i != rowsCount - 1)
            {
                fileToWrite << endl;
            }
            else if (j != columnsCount - 1)
            {
                fileToWrite << "|";
            }
        }
    }

    isSaved = true;
    fileToWrite.close();
}

void UserConnection::openFile(string &fileName)
{
    readTable(fileName);

    if (isOpened)
        cout << "Successfully opened file: " << fileName << endl;
}

void UserConnection::saveFile()
{
    if (!isOpened)
    {
        throw std::invalid_argument("There isn't opened file!");
    }

    writeToTableFile();
}

void UserConnection::saveFileAs(string filePath)
{
    if (!isOpened)
    {
        throw std::invalid_argument("There isn't opened file!");
    }

    this->fileName = filePath;
    writeToTableFile();

    cout << "Successfully saved " << filePath << endl;
}

void UserConnection::closeFile()
{
    if (!isOpened)
    {
        throw std::invalid_argument("No open file!");
    }
    delete this->dataBase;
    cout << "Table closed\n";
}

void UserConnection::help()
{
    cout << "*******************************************************************************************************\n"
         << "*******************************************************************************************************\n"
         << "***  1-  open                                             opens file                                ***\n"
         << "***  2-  close                                            closes file                               ***\n"
         << "***  3-  save                                             saves file in same place                  ***\n"
         << "***  4-  saveAs                                           saves file in another place               ***\n"
         << "***  5-  exit                                             exits program                             ***\n"
         << "***  6-  import                                           add table to database                     ***\n"
         << "***  7-  showtables                                       shows all tables in database              ***\n"
         << "***  8-  describe                                         shows types of the columns                ***\n"
         << "***  9-  print                                            prints rows of a table                    ***\n"
         << "***  10- export                                           saves table in file.                      ***\n"
         << "***  11- select                                           print all rows with specific value        ***\n"
         << "***  12- update                                           change value of some rows                 ***\n"
         << "***  13- delete                                           delete all rows with specific value       ***\n"
         << "***  14- rename                                           renames table                             ***\n"
         << "***  15- count                                            count rows with specific value            ***\n"
         << "***  16- help                                             shows info about the database             ***\n"
         << "*******************************************************************************************************\n"
         << "*******************************************************************************************************\n";
}

void UserConnection::exit()
{
    string answer;
    if (isOpened && !isSaved)
    {
        cout << "You have an open file with unsaved changes, please select 'close', 'save' or 'saveAs' first.\n";
        getline(cin, answer);
        while (true)
        {
            if (answer == "close")
            {
                closeFile();
                break;
            }
            else if (answer == "save")
            {
                saveFile();
                break;
            }
            else if (answer == "saveAs")
            {
                cout << "File name to save:\n";
                getline(cin, fileName);
                saveFileAs(fileName);
                break;
            }
            else
                cout << "Please enter 'close', 'save' or 'saveAs'. ";
        }
    }
    cout << "Exiting program...";
}

void UserConnection::importFile(string fileName)
{
    std::ifstream read;
    read.open(fileName);
    if (!read.is_open())
    {
        throw std::invalid_argument("Can't open file!");
    }

    string name, line;

    getline(read, name);
    read.close();

    read.open(dbNames);

    if (!read.is_open())
    {
        throw std::invalid_argument("Can't open Database file!");
    }

    size_t index;
    while (getline(read, line))
    {
        index = line.find('|');
        line = line.substr(index + 1);
        if (line == fileName)
        {
            read.close();
            throw std::invalid_argument("File already exists!");
        }
    }
    read.close();

    std::ofstream write;
    write.open(dbNames, std::ios::app);
    if (!write.is_open())
    {
        throw std::invalid_argument("Can't open Database file!");
    }
    write << name << "|" << fileName << endl;
    write.close();
}

void UserConnection::showAllTables()
{
    std::ifstream read;
    read.open(dbNames);

    if (!read.is_open())
    {
        throw std::invalid_argument("Can't open Databases file");
    }

    string line;
    size_t index;
    while (getline(read, line))
    {
        if (line.length() == 0)
            break;
        index = line.find('|');
        cout << line.substr(index + 1) << endl;
    }
    read.close();
}

void UserConnection::describeTable()
{
    size_t columnCount = dataBase->getColumnsCount();
    int type = 0;
    for (size_t i = 0; i < columnCount; ++i)
    {
        type = dataBase->getColumn(i)->getColumnType();
        if (type == 0)
        {
            cout << "int";
        }
        else if (type == 1)
        {
            cout << "double";
        }
        else if (type == 2)
        {
            cout << "string";
        }
        else
            throw std::logic_error("Invalid state");
        if (i == columnCount - 1)
        {
            cout << "\n";
        }
        else
            cout << " ";
    }
}

void UserConnection::printTable()
{
    size_t columns = this->dataBase->getColumnsCount();
    size_t rows = this->dataBase->getLinesCount();

    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = 0; j < columns; ++j)
        {
            cout << this->dataBase->getColumn(j)->getValueAt(i) << " ";
        }
        cout << endl;
    }
}

void UserConnection::selectValueToPrint(int columnNumber, string value)
{
    size_t rows = this->dataBase->getLinesCount();
    size_t cols = this->dataBase->getColumnsCount();
    bool found = false;
    for (size_t i = 0; i < rows; ++i)
    {
        if (dataBase->getColumn(columnNumber - 1)->getValueAt(i) == value) /// check if this value is found
        {
            found = true;
        }

        if (found)
        {
            for (size_t j = 0; j < cols; ++j)
            {
                cout << dataBase->getColumn(j)->getValueAt(i) << " ";
            }
            cout << endl;
        }
        found = false;
    }
}

void UserConnection::deleteRows(size_t column, string value)
{
    size_t rows = this->dataBase->getLinesCount();
    size_t cols = this->dataBase->getColumnsCount();
    for (size_t i = 0; i < rows; ++i)
    {
        if (dataBase->getColumn(column - 1)->getValueAt(i) == value)
        {
            for (size_t j = 0; j < cols; ++j)
            {
                dataBase->getColumn(j)->removeValueAt(i);
            }
            --rows;
            --i;
            this->dataBase->setMaxLen(rows);
        }
    }
    isSaved = false;
}

void UserConnection::updateTable(size_t searchColumn, size_t targetColumn, string searchValue, string targetValue)
{
    size_t rows = this->dataBase->getLinesCount();
    size_t cols = this->dataBase->getColumnsCount();
    for (size_t i = 0; i < rows; ++i)
    {
        if (dataBase->getColumn(searchColumn - 1)->getValueAt(i) == searchValue)
        {
            dataBase->getColumn(targetColumn - 1)->setValueAt(i, targetValue);
            isSaved = false;
        }
    }
}

void UserConnection::renameTable(string newTableName)
{
    std::ifstream read;
    read.open(dbNames);

    if (!read.is_open())
    {
        throw std::invalid_argument("Can't open Database file!");
    }
    string line;
    size_t index;
    string forNewFile;
    string fileName;
    while (getline(read, line))
    {
       
        if(line.length()==0 || line=="\n") break;
        index = line.find('|');
        fileName = line.substr(index+1);
        if(fileName==this->fileName)
        {
            forNewFile+=(newTableName+"|"+this->fileName);
            forNewFile+="\n";
        }
        else forNewFile+=(line+"\n");
        line = line.substr(0, index);
        if (line == fileName)
        {
            read.close();
            throw std::invalid_argument("Name is not unique!");
        }
    }
    read.close();
    this->dataBase->setNameTable(newTableName);
    std::ofstream write;
    write.open(dbNames,std::ios::trunc);
    if (!write.is_open())
    {
        throw std::invalid_argument("Can't open Database file!");
    }
    write << forNewFile;
    isSaved = false;
}

void UserConnection::countRowsWithValue(size_t columnNumber, string searchedValue)
{
    size_t rows = this->dataBase->getLinesCount();
    size_t cols = this->dataBase->getColumnsCount();
    bool found = false;
    int counter = 0;
    for (size_t i = 0; i < rows; ++i)
    {
        if (dataBase->getColumn(columnNumber - 1)->getValueAt(i) == searchedValue)
        {
            counter++;
        }
    }
    cout << "Number of rows containing " << searchedValue << ": " << counter << endl;
}

void UserConnection::runProgram()
{
    cout << "\n     ------WELCOME TO DATABASE MANAGEMENT SYSTEM------           \n\n";

    string selectFunction, fileName;
    help();
    while (true)
    {
        try
        {
            getline(cin, selectFunction);

            if (selectFunction == "open")
            {
                cout << "File name: ";
                getline(cin, fileName);
                openFile(fileName);
            }
            else if (selectFunction == "save")
            {
                saveFile();
            }
            else if (selectFunction == "saveAs")
            {
                cout << "File name to save: ";
                getline(cin, fileName);
                saveFileAs(fileName);
            }
            else if (selectFunction == "close")
            {
                closeFile();
            }
            else if (selectFunction == "exit")
            {
                exit();
                break;
            }
            else if (selectFunction == "help")
            {
                help();
            }
            else if (selectFunction == "import")
            {
                cout << "Enter the name of the table file: ";
                getline(cin, fileName);
                importFile(fileName);
            }
            else if (selectFunction == "showtables")
            {
                showAllTables();
            }
            else if (selectFunction == "describe")
            {
                if (!isOpened)
                {
                    throw std::invalid_argument("No opened file!");
                }
                describeTable();
            }
            else if (selectFunction == "print")
            {
                if (!isOpened)
                {
                    throw std::invalid_argument("No opened file!");
                }
                printTable();
            }
            else if (selectFunction == "export")
            {
                if (!isOpened)
                {
                    throw std::invalid_argument("No opened file!");
                }
                cout << "Enter file name to save: ";
                string secondFileName;
                getline(cin, secondFileName);
                saveFileAs(secondFileName);
            }
            else if (selectFunction == "select")
            {
                if (!isOpened)
                {
                    throw std::invalid_argument("No opened file!");
                }
                int column;
                string value;
                string column_s;

                cout << "Enter column number: ";
                getline(cin, column_s);
                column = stoi(column_s);
                cout << "Enter value: ";
                getline(cin, value);
                selectValueToPrint(column, value);
            }
            else if (selectFunction == "update")
            {
                if (!isOpened)
                {
                    throw std::invalid_argument("No opened file!");
                }
                size_t searchColumn, targetColumn;
                string serachColumn_s, searchValue, targetColumn_s, targetValue;
                cout << "Enter search column number: ";
                getline(cin, serachColumn_s);
                cout << "Enter search value: ";
                getline(cin, searchValue);
                cout << "Enter target column number: ";
                getline(cin, targetColumn_s);
                cout << "Enter target value: ";
                getline(cin, targetValue);
                searchColumn = stoi(serachColumn_s);
                targetColumn = stoi(targetColumn_s);
                updateTable(searchColumn, targetColumn, searchValue, targetValue);
            }
            else if (selectFunction == "delete")
            {
                if (!isOpened)
                {
                    throw std::invalid_argument("No opened file!");
                }
                int column;
                string value;
                string column_s;

                cout << "Enter column number: ";
                getline(cin, column_s);
                column = stoi(column_s);
                cout << "Enter value: ";
                getline(cin, value);
                deleteRows(column, value);
            }
            else if (selectFunction == "rename")
            {
                if (!isOpened)
                {
                    throw std::invalid_argument("No opened file!");
                }
                string newNameTable;
                cout << "Enter the new name of the table: ";
                getline(cin,newNameTable);

                renameTable(newNameTable);
            }
            else if (selectFunction == "count")
            {
                if (!isOpened)
                {
                    throw std::invalid_argument("No opened file!");
                }
                int column;
                string value;
                string column_s;

                cout << "Enter column number: ";
                getline(cin, column_s);
                column = stoi(column_s);
                cout << "Enter value: ";
                getline(cin, value);
                countRowsWithValue(column, value);
            }
            else
            {
                cout << "Enter a valid command!" << endl;
            }
        }

        catch (const std::exception &e)
        {
            cout << e.what() << '\n';
        }
    }
}

UserConnection::~UserConnection()
{
    delete dataBase;
}