// ------------------- transaction.cpp --------------------
// Sawyer Knoblich and Elias Muche, CSS 343
// Created 5-27-16
// Last modified 6-7-16
// ---------------------------------------------------
// Purpose: Implement the Transaction class
// ---------------------------------------------------

#include "transaction.h"

// ================ empty constructor ===============
// stores the given info into the correct fields
// preconditions: takes pointers to a Customer and a Movie as well as
//     a transactionType char, should be 'B' or 'R' for valid transactions
// postconditions: the given info is stored in their respective fields
// ==================================================
Transaction::Transaction(char _transactionType, Customer* _customer, Movie* _movie) {
    transactionType = _transactionType;
    customer = _customer;
    movie = _movie;
}
// end empty constructor