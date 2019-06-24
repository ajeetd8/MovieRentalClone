// ------------------- borrow.h --------------------
// Sawyer Knoblich and Elias Muche, CSS 343
// Created 5-25-16
// Last modified 6-6-16
// ---------------------------------------------------
// Purpose: Keeps track of which Customer borrowed which movie
// ---------------------------------------------------

#include <iostream>
#include "transaction.h"
using namespace std;

#ifndef BORROW_H
#define BORROW_H

class Borrow: public Transaction{
	public:

    // ================ empty constructor ===============
    // simply calls the Transaction constructor with a transactionType of 'B'
    // preconditions: takes pointers to a Customer and a Movie
    // postconditions: the given Customer and Movie pointers are stored in the
    //     Borrow transaction and the transactionType is 'B'
    // ==================================================
	Borrow(Customer *customer, Movie *movie) : Transaction('B',customer,movie){}
};

#endif