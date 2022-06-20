/*! \mainpage Database system - A brief description
This project presents a single database with specific functions for adding, sorting, finding, removing, etc. columns rows and tables.

The project consist of 6 classes- Column, IntColumn, DoubleColumn, StringColumn, Table and UserConnection.

Notes:
- Column parts: name of the column, type of the column, vector of values
- Table parts: name and vector of columns of different types

- For part of the functions is used additional information from the site https://www.geeksforgeeks.org/

Link to Github: https://github.com/ViktoriaIvanova9/Database

Future extensions:
- the class Database could be singleton
- more functions could be included
- more validation could be included
- tests should be included
 */


#include "../Headers/UserConnection.h"

int main()
{
    ///creating object of type UserConnection and running the program
    UserConnection User;
    User.runProgram();

}