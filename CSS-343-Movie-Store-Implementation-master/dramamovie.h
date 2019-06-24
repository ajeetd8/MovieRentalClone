// ------------------- dramamovie.h --------------------
// Sawyer Knoblich and Elias Muche, CSS 343
// Created 5-27-16
// Last modified 6-5-16
// ---------------------------------------------------
// Purpose: Holds the information for a drama movie
// ---------------------------------------------------

#include <iostream>
#include "movie.h"
using namespace std;

#ifndef DRAMAMOVIE_H
#define DRAMAMOVIE_H

class DramaMovie: public Movie{
public:
    
	//====================================
	//Default Constructor
	//Calls the movie constructor and sets the fields
	//Pre-conditions: none 
	//Post-conditions: the fields will be set 
	//====================================
    DramaMovie();
	
	//====================================
	//Constructor
	// Takes two strings (title,director) and two ints(stock, year) and calls the movie constructor 
	//Pre-conditions: none 
	//Post-conditions: the fields will be set to the parameters
	//====================================
    DramaMovie(int stock, int year, string title, string director);
    
    //====================================
	//= Overload
	//Takes a drama movie and creates a deep copy 
	//Pre-conditions: none 
	//Post-conditions: the fields will be set to the parameters
	//====================================
	void operator=(const DramaMovie &);
    
    
private:
    
    
    
};

#endif





