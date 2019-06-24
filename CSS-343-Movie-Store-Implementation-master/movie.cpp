// ------------------- movie.cpp --------------------
// Sawyer Knoblich and Elias Muche, CSS 343
// Created 5-25-16
// Last modified 6-7-16
// ---------------------------------------------------
// Purpose: Implements the Movie class
// ---------------------------------------------------

#include "movie.h"
	
	//=========================================================
	//Default Constructor
	//Initializes the fields
	//Pre-conditions: none
	//Post-conditions: the fields will be initialized
	//=========================================================
	Movie::Movie() : Rental() {
    	yearReleased = 0;
    	director = "";
	}
	
	//=========================================================
	//Constructor
	//Takes two strings (director and title) an two ints (year and stock) and sets the fields accordingly
	//Calls base class(Rental) constructor
	//Initializes the fields
	//Pre-conditions: none
	//Post-conditions: the fields will be initilized to the parameters  
	//=========================================================    
	Movie::Movie(int _stock, int _year, string _title, string _director) : Rental(_stock, _year, _title) {
    	    director = _director;
	}

	/*bool Movie::operator==(const Movie &movie)const{
		return (stock==movie.stock) && (title==movie.title) && (yearReleased==movie.yearReleased) && (director==movie.director);		

	}

	bool Movie::operator!=(const Movie &movie)const{
		return !(*this==movie);
	
	}*/
	
	//=========================================================
	//= Overload
	//Takes a movie and creates a deep copy
	//Pre-conditions: none
	//Post-conditions: this will have the same data as the parameter
	//=========================================================
	void Movie::operator=(const Movie& rhs) {
    	title = rhs.title;
    	yearReleased = rhs.yearReleased;
    	director = rhs.director;
	}

	//=========================================================
	//Get Director
	//Returns the director name
	//Pre-conditions: none
	//Post-conditions: a value will be returned
	//=========================================================
	string Movie::getDirector(){
		return director;
		
	}

	//=========================================================
	//Get Type 
	//Returns the type (character)
	//Pre-conditions: none
	//Post-conditions: a value will be returned
	//=========================================================
	char Movie::getType(){
		return type;
		
	}