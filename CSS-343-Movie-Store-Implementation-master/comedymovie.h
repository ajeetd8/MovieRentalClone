// ------------------- comedymovie.h --------------------
// Sawyer Knoblich and Elias Muche, CSS 343
// Created 5-25-16
// Last modified 6-5-16
// ---------------------------------------------------
// Purpose: Holds the information and functions for each comedy movie
// ---------------------------------------------------

#include <iostream>
#include "movie.h"
using namespace std;

#ifndef COMEDYMOVIE_H
#define COMEDYMOVIE_H

class ComedyMovie: public Movie {
public:
    
	//=================================
	//Default Constructor
	//Initializes the fields
	//Pre-conditions: none 
	//Post-conditions: the fields will be initialized
	//=================================
    ComedyMovie();
    
	//=================================
	//Constructor
	//Calls the movie constructor
	//Pre-conditions: none 
	//Post-conditions: the fields will be set to the parameters
	//=================================
    ComedyMovie(int stock, int year, string title, string director);
    
	//=================================
	//= Overload
	//Takes a comedy movie and creates a deep copy
	//Pre-conditions: none 
	//Post-conditions: this will have the same data as the param
	//=================================
    void operator=(const ComedyMovie& rhs);
    
private:
    
    
    
};

#endif