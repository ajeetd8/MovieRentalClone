// ------------------- transaction.h --------------------
// Sawyer Knoblich and Elias Muche, CSS 343
// Created 5-25-16
// Last modified 6-6-16
// ---------------------------------------------------
// Purpose: Base class for the Borrow and Return transactions
// ---------------------------------------------------

#include <iostream>
#include "customer.h"
#include "movie.h"

using namespace std;

#ifndef TRANSACTION_H
#define TRANSACTION_H

class Transaction{
public:

	char transactionType;	// either 'B' for Borrow or 'R' for return
    Customer *customer;		// the Customer who performed the transaction
	Movie *movie;			// the Movie the customer borrowed or returned
    
    // ================ empty constructor ===============
    // stores the given info into the correct fields
    // preconditions: takes pointers to a Customer and a Movie as well as
    //     a transactionType char, should be 'B' or 'R' for valid transactions
    // postconditions: the given info is stored in their respective fields
    // ==================================================
    Transaction(char transactionType, Customer* customer, Movie* movie);	
};

#endif