// ------------------- comedymovie.cpp --------------------
// Sawyer Knoblich and Elias Muche, CSS 343
// Created 5-25-16
// Last modified 6-5-16
// ---------------------------------------------------
// Purpose: Implements the ComedyMovie class
// ---------------------------------------------------

#include "comedymovie.h"
#include<iostream>
using namespace std;

	//=================================
	//Default Constructor
	//Initializes the fields
	//Pre-conditions: none 
	//Post-conditions: the fields will be initialized
	//=================================
	ComedyMovie::ComedyMovie() : Movie(0, -1, "", "") {
    
    
	};

	//=================================
	//Constructor
	//Calls the movie constructor
	//Pre-conditions: none 
	//Post-conditions: the fields will be set to the parameters
	//=================================
	ComedyMovie::ComedyMovie(int stock,int year,string title,string direct):Movie(stock, year, title, direct){
		type='F';

	}

	//=================================
	//= Overload
	//Takes a comedy movie and creates a deep copy
	//Pre-conditions: none 
	//Post-conditions: this will have the same data as the param
	//=================================
	void ComedyMovie::operator=(const ComedyMovie& rhs) {
    	title = rhs.title;
    	yearReleased = rhs.yearReleased;
    	director = rhs.director;
	}