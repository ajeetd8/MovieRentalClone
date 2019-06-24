// ------------------- rental.h --------------------
// Sawyer Knoblich and Elias Muche, CSS 343
// Created 5-25-16
// Last modified 6-2-16
// ---------------------------------------------------
// Purpose: A base class for all items that can be rented
//     from the MovieStore
// ---------------------------------------------------

#include <iostream>
using namespace std;

#ifndef RENTAL_H
#define RENTAL_H

class Rental {
public:

	
    //========================================================
    //Default constructor
	//Initializes the protected fields
	//Pre-conditions: none
	//Post-conditions: the protected fields will be initialized
	//=========================================================
    Rental();
    
	//=========================================================
    //Constructor puts the given information into their respective fields
	//Takes the number in stock, the year it was released, and the title as parameters
	//Pre-conditions: none
	//Post-conditions: the corresponding fields will be set the parameters 
	//=========================================================
    Rental(int stock, int year, string title);

	//=========================================================
	//== Overload
	//Takes a Rental object as a parameter
	//Returns true if two Rentals are equal to each other, false otherwise
	//Pre-conditions: none
	//Post-conditions: the parameter/this won't change and a value will be returned
	//=========================================================
	virtual bool operator==(const Rental &) const;

	//================================================================
	//!= Overload
	//Takes a Rental object as a parameter
	//Returns true if two Rentals are not equal to each other, false otherwise
	//Pre-conditions: none
	//Post-conditions: the parameter and this won't change and a value will be returned
	//=========================================================
	virtual bool operator!=(const Rental &) const;
	
	//=========================================================
	//Get Current Stock
	//Returns an int represented the amount of this Movie in stock
	//Pre-conditions: none
	//Post-conditions: a value will be returned
	//=========================================================
	int getCurrentStock();

	//=========================================================
	//Get Year
	//Returns an int that represents the year released for the title
	//Pre-conditions: none
	//Post-conditions: a value will be returned
	//=========================================================
	int getYear();

	//=========================================================
	//Get Title
	//Returns the title of the rental
	//Pre-conditions: none
	//Post-conditions: a value will be returned
	//=========================================================
	string getTitle();
	
	//=========================================================
	//Checkout Rental
	//Decreases the stock of the movie by one, returns the new stock
	//Pre-conditions: the current stock must be greater than 0 
	//Post-conditions: a value will be returned
	//=========================================================
	int checkoutRental();

	//=========================================================
	//Return Rental
	//Increases the stock of the movie by one, returns the new stock
	//Pre-conditions: none
	//Post-conditions: a value will be returned
	//=========================================================
	int returnRental();
    
protected:

	int stock;
	int yearReleased;
	string title;
		
};

#endif