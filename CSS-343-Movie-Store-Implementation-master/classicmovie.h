// ------------------- classicmovie.h --------------------
// Sawyer Knoblich and Elias Muche, CSS 343
// Created 5-25-16
// Last modified 6-7-16
// ---------------------------------------------------
// Purpose: Holds the information and functions for each classic movie
// ---------------------------------------------------

#include <iostream>
#include "movie.h"
using namespace std;

#ifndef CLASSICMOVIE_H
#define CLASSICMOVIE_H

class ClassicMovie: public Movie {
	public:
		
	//=========================================================
	//Date Comparable
	//Returns the date as a single int 
	//Pre-conditions: none 
	//Post-conditions: a value will be returned
	//=========================================================
	int dateComparable();
    
	//=========================================================
	//Default constructor	
	//Initializes the fields 
	//Pre-conditions: none 
	//Post-conditions: the fields will be initialized
	//=========================================================
    ClassicMovie();
	
	//=========================================================
	//Constructor
	//Calls the Movie constructor with the given info,
	//Also puts the ClassicMovie-specific info into the correct fields
	//Pre-conditions: none 
	//Post-conditions: the fields will be set to the parameters 
	//=========================================================
    ClassicMovie(int stock, int year, string title, string director, int month, string actor);
    
	//=========================================================
	//== Overload
	//Returns true if two ClassicMovies are equal to each other,false otherwise 
	//Pre-conditions: none 
	//Post-conditions: a value will be returned and this and the param won't change
	//=========================================================
	bool operator==(const ClassicMovie &) const;

	//=========================================================
	//!= Overload
	//Returns true if two ClassicMovies are not equal to each other,false otherwise 
	//Pre-conditions: none 
	//Post-conditions: a value will be returned and this and the param won't change
	//=========================================================
	bool operator!=(const ClassicMovie &) const;
    
	//=========================================================
	//= Overload
	//Takes another classic movie and creates a deep copy
	//Pre-conditions: none
	//Post-conditions: this will have the same data as the param
	//=========================================================
    void operator=(const ClassicMovie &);
    
	//=========================================================
	//Get Major Actor
	//Returns the major actor in the movie
	//Pre-conditions: none
	//Post-conditions: the actor field will be returned
	//=========================================================
    string getMajorActor();
	
	//=========================================================
	//Get Month Released
	//Returns the month the movie was released
	//Pre-conditions: none 
	//Post-conditions: the month field will be returned
	//=========================================================
    int getMonthReleased();
    
	//=========================================================
	//Is Same
	//Takes another classic movie and checks if they're both the same movie(they can have different major actors)
	//Pre-conditions: none 
	//Post-conditions: a value will be returned 
	//=========================================================
    bool isSame(ClassicMovie* movie);
	
	
	private:
	string majorActor;

	int monthReleased;	
	
	
};

#endif