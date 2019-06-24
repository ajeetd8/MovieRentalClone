// ------------------- classicmovie.cpp --------------------
// Sawyer Knoblich and Elias Muche, CSS 343
// Created 5-25-16
// Last modified 6-7-16
// ---------------------------------------------------
// Purpose: Implements the ClassicMovie class
// ---------------------------------------------------

#include<iostream>
#include "classicmovie.h"
using namespace std;

	//=========================================================
	//Date Comparable
	//Returns the date as a single int 
	//Pre-conditions: none 
	//Post-conditions: a value will be returned
	//=========================================================
	int ClassicMovie:: dateComparable(){
		return yearReleased*100 + monthReleased;
		
	}


	//=========================================================
	//Default constructor	
	//Initializes the fields 
	//Pre-conditions: none 
	//Post-conditions: the fields will be initialized
	//=========================================================
	ClassicMovie::ClassicMovie() : Movie(0, -1, "", "") {
    	monthReleased = -1;
    	majorActor = "";
    	type='C';
	}


	//=========================================================
	//Constructor
	//Calls the Movie constructor with the given info,
	//Also puts the ClassicMovie-specific info into the correct fields
	//Pre-conditions: none 
	//Post-conditions: the fields will be set to the parameters 
	//=========================================================
	ClassicMovie::ClassicMovie(int _stock, int _year, string _title, string _director, int _month, string _actor) : Movie(_stock, _year, _title, _director) {
    	monthReleased = _month;
    	majorActor = _actor;
		type='C';
	}

	//=========================================================
	//== Overload
	//Returns true if two ClassicMovies are equal to each other,false otherwise 
	//Pre-conditions: none 
	//Post-conditions: a value will be returned and this and the param won't change
	//=========================================================
	bool ClassicMovie::operator==(const ClassicMovie &rhs)const{
		bool x=(stock==rhs.stock) && (title==rhs.title) && (yearReleased==rhs.yearReleased) && (director==rhs.director);
		bool y=(monthReleased==rhs.monthReleased) && (majorActor==rhs.majorActor);
		return x&&y;

	}

	//=========================================================
	//!= Overload
	//Returns true if two ClassicMovies are not equal to each other,false otherwise 
	//Pre-conditions: none 
	//Post-conditions: a value will be returned and this and the param won't change
	//=========================================================
	bool ClassicMovie::operator!=(const ClassicMovie &rhs)const{
		return (*this==rhs);

	}

	//=========================================================
	//= Overload
	//Takes another classic movie and creates a deep copy
	//Pre-conditions: none
	//Post-conditions: this will have the same data as the param
	//=========================================================
	void ClassicMovie::operator=(const ClassicMovie& rhs) {
    	title = rhs.title;
    	yearReleased = rhs.yearReleased;
    	director = rhs.director;
    	monthReleased = rhs.monthReleased;
    	majorActor = rhs.majorActor;
	}	

	//=========================================================
	//Get Major Actor
	//Returns the major actor in the movie
	//Pre-conditions: none
	//Post-conditions: the actor field will be returned
	//=========================================================
	string ClassicMovie::getMajorActor(){
		return majorActor;
	}
	
	//=========================================================
	//Get Month Released
	//Returns the month the movie was released
	//Pre-conditions: none 
	//Post-conditions: the month field will be returned
	//=========================================================
	int ClassicMovie::getMonthReleased(){
		return monthReleased;
		
	}

	//=========================================================
	//Is Same
	//Takes another classic movie and checks if they're both the same movie(they can have different major actors)
	//Pre-conditions: none 
	//Post-conditions: a value will be returned 
	//=========================================================
	bool ClassicMovie::isSame(ClassicMovie* rhs){
		
		bool x = (title==rhs->title) && (yearReleased==rhs->yearReleased) && (director==rhs->director);
		bool y=(monthReleased==rhs->monthReleased);
		return x&&y;
		
	}