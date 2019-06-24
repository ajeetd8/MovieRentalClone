// ------------------- dramamovie.cpp --------------------
// Sawyer Knoblich and Elias Muche, CSS 343
// Created 5-25-16
// Last modified 6-8-16
// ---------------------------------------------------
// Purpose: Implements the DramaMovie class
// ---------------------------------------------------

#include<iostream>
using namespace std;
#include "dramamovie.h"


	//====================================
	//Constructor
	//Calls the movie constructor 
	//Pre-conditions: none 
	//Post-conditions: the fields will be set to the parameters
	//====================================
	DramaMovie::DramaMovie() : Movie(0, -1, "", "") {
    
    
	};

	//====================================
	//Constructor
	// Takes two strings (title,director) and two ints(stock, year) and calls the movie constructor 
	//Pre-conditions: none 
	//Post-conditions: the fields will be set to the parameters
	DramaMovie::DramaMovie(int stock,int year,string title,string direct):Movie(stock, year, title, direct){
		type='D';

	}

	//====================================
	//= Overload
	//Takes a drama movie and creates a deep copy 
	//Pre-conditions: none 
	//Post-conditions: the fields will be set to the parameters
	//====================================
	void DramaMovie::operator=(const DramaMovie& rhs) {
    
    	title = rhs.title;
    	yearReleased = rhs.yearReleased;
    	director = rhs.director;
	}