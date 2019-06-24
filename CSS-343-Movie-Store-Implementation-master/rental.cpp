// ------------------- rental.cpp --------------------
// Sawyer Knoblich and Elias Muche, CSS 343
// Created 5-25-16
// Last modified 6-2-16
// ---------------------------------------------------
// Purpose: Implements the Rental class
// ---------------------------------------------------

#include "rental.h"
	
	//========================================================
    //Default constructor
	//Initializes the protected fields
	//Pre-conditions: none
	//Post-conditions: the protected fields will be initialized
	//=========================================================
	Rental::Rental() {
    	stock = 0;
    	title = "";
		yearReleased=0;
	}

	//=========================================================
    //Constructor puts the given information into their respective fields
	//Takes the number in stock, the year it was released, and the title as parameters
	//Pre-conditions: none
	//Post-conditions: the corresponding fields will be set the parameters 
	//=========================================================
	Rental::Rental(int _stock,int year, string _title) {
    	stock = _stock;
    	title = _title;
		yearReleased=year;
	}

	//=========================================================
	//== Overload
	//Takes a Rental object as a parameter
	//Returns true if two Rentals are equal to each other, false otherwise
	//Pre-conditions: none
	//Post-conditions: the parameter/this won't change and a value will be returned
	//=========================================================
    bool Rental::operator==(const Rental &rental)const{
		return (stock==rental.stock) && (title==rental.title) && (yearReleased==rental.yearReleased);

	}
	//================================================================
	//!= Overload
	//Takes a Rental object as a parameter
	//Returns true if two Rentals are not equal to each other, false otherwise
	//Pre-conditions: none
	//Post-conditions: the parameter and this won't change and a value will be returned
	//=========================================================
	bool Rental::operator!=(const Rental &rental)const{
		return !(*this==rental);
	}

	//=========================================================
	//Get Current Stock
	//Returns an int represented the amount of this Movie in stock
	//Pre-conditions: none
	//Post-conditions: a value will be returned
	//=========================================================
	int Rental::getCurrentStock(){
		return stock;
	}

	//=========================================================
	//Get Year
	//Returns an int that represents the year released for the title
	//Pre-conditions: none
	//Post-conditions: a value will be returned
	//=========================================================
	int Rental::getYear(){
		return yearReleased;
		
	}
	
	//=========================================================
	//Get Title
	//Returns the title of the rental
	//Pre-conditions: none
	//Post-conditions: a value will be returned
	//=========================================================
	string Rental::getTitle(){
		return title;

	}
	
	//=========================================================
	//Checkout Rental
	//Decreases the stock of the movie by one, returns the new stock
	//Pre-conditions: the current stock must be greater than 0 
	//Post-conditions: a value will be returned
	//=========================================================
	int Rental::checkoutRental(){
		return stock--;

	}
	
	//=========================================================
	//Return Rental
	//Increases the stock of the movie by one, returns the new stock
	//Pre-conditions: none
	//Post-conditions: a value will be returned
	//=========================================================
	int Rental::returnRental(){
		return stock++;

	}