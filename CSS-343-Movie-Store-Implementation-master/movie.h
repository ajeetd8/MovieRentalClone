// ------------------- movie.h --------------------
// Sawyer Knoblich and Elias Muche, CSS 343
// Created 5-25-16
// Last modified 6-7-16
// ---------------------------------------------------
// Purpose: A base class for all Movie objects
// ---------------------------------------------------

#include <iostream>
#include "rental.h"

#ifndef MOVIE_H
#define MOVIE_H

using namespace std;

class Movie: public Rental {
public:
	

	
	//store the type D C F
	   
    //=========================================================
	//Default Constructor
	//Initializes the fields
	//Pre-conditions: none
	//Post-conditions: the fields will be initialized
	//=========================================================
    Movie();//:Rental();


	//=========================================================
	//Constructor
	//Takes two strings (director and title) an two ints (year and stock) and sets the fields accordingly
	//Calls base class(Rental) constructor
	//Initializes the fields
	//Pre-conditions: none
	//Post-conditions: the fields will be initilized to the parameters  
	//=========================================================    
    Movie(int stock, int year, string title, string director);// : Rental(stock, year title){};
    
	//=========================================================
	//= Overload
	//Takes a movie and creates a deep copy
	//Pre-conditions: none
	//Post-conditions: this will have the same data as the parameter
	//=========================================================
    void operator=(const Movie &);
	
	//=========================================================
	//== Overload
	//Takes another movie and compares if their data is the same
	//Pre-conditions: the parameter will not be changed and this will not be changed
	//Post-conditions: a value will be returned
	//=========================================================
	//virtual bool operator==(const Movie &) const;

	//=========================================================
	//!= Overload
	//Takes another movie and compares if their data isn't the same
	//Pre-conditions: the parameter will not be changed
	//Post-conditions: a value will be returned
	//=========================================================
	//virual bool operator!=(const Movie &) const;	
	
	// returns an int represented the amount of this Movie in stock
    //int getCurrentStock();

	// returns the Movie's release year
    //int getYearReleased();

	// returns the title of the movie
    //string getTitle();

	//=========================================================
	//Get Director
	//Returns the director name
	//Pre-conditions: none
	//Post-conditions: a value will be returned
	//=========================================================
    string getDirector();
    
	// decreases the stock of the movie by one, returns the new stock
	//int checkoutMovie();

	// increases the stock of the movie by one, returns the new stock
    //int returnMovie(); 
	
	//returns the type of movie
	char getType();

private:
	
protected :
	string director;
	char type;

	
	
	
};

#endif