// ------------------- return.h --------------------
// Sawyer Knoblich and Elias Muche, CSS 343
// Created 5-25-16
// Last modified 6-6-16
// ---------------------------------------------------
// Purpose: Keeps track of which Customer returned which Movie
// ---------------------------------------------------

#include <iostream>
#include "transaction.h"
#include "movie.h"
#include "customer.h"
using namespace std;

#ifndef RETURN_H
#define RETURN_H

class Return : public Transaction {
	public:

    // ================ empty constructor ===============
    // simply calls the Transaction constructor with a transactionType of 'R'
    // preconditions: takes pointers to a Customer and a Movie
    // postconditions: the given Customer and Movie pointers are stored in the
    //     Borrow transaction and the transactionType is 'R'
    // ==================================================
	Return(Customer *customer, Movie *movie) : Transaction('R',customer,movie){}
};

#endif