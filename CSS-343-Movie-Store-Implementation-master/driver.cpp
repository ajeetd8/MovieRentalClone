// ------------------- driver.cpp --------------------
// Sawyer Knoblich and Elias Muche, CSS 343
// Created 5-27-16
// Last modified 6-8-16
// ---------------------------------------------------
// Purpose: Create a MovieStore and call its read functions
// ---------------------------------------------------

#include <stdio.h>
#include <iostream>
#include <fstream>
#include "moviestore.h"

int main(int argc, char** argv) {
    
    MovieStore ms;
    
    ifstream customerFile("data4customers.txt");
    ms.readCustomers(customerFile);
    
    ifstream movieFile("data4movies.txt");
    ms.readMovies(movieFile);
    
    ifstream commandFile("data4commands.txt");
    ms.readCommands(commandFile);
    
    return 0;
}