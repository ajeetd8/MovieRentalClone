// ------------------- customer.h --------------------
// Sawyer Knoblich and Elias Muche, CSS 343
// Created 5-25-16
// Last modified 6-7-16
// ---------------------------------------------------
// Purpose: Holds the information and functions for each customer
// ---------------------------------------------------

#include <iostream>
#include <math.h>

using namespace std;

#ifndef CUSTOMER_H
#define CUSTOMER_H

class Transaction;

class Borrow;

class Return;

class Movie;

class Customer{
	public:
    
	

    // ================ empty constructor ===============
    // initializes default values for fields
    // preconditions: none
    // postconditions: first and last are empty strings and id = -1
    // ==================================================
    Customer();

    // ================ constructor ===============
    // initializes fields to given values
    // preconditions: none
    // postconditions: first and last are the given strings
    //     and id is the given id
    // ==================================================
	Customer(string first, string last, int id);
	
    // ================ getCustomerID ===============
    // getter for the customer id number
    // preconditions: none
    // postconditions: returns the customer id as an int
    // ==================================================
    int getCustomerID();
	
    
    // ================ getCustomerIDString ===============
    // getter for the customer id number as a string
    // preconditions: id is a 4 digit number
    // postconditions: returns the customer id as a string
    // ==================================================
	string getCustomerIDString();

    // ================ getName ===============
    // getter for the customer's full name
    // preconditions: none
    // postconditions: returns the customer full name
    //     formatted as "first last"
    // ==================================================
	string getName();

    // ================ checkoutMovie ===============
    // adds the given movie to the customer's currently check out movies
    //     as well as a borrow Transaction to the transaction history
    // preconditions: movie is a valid movie object
    // postconditions: the given movie will be held in a MovieNode at
    //     the beginning of the MovieNode list and a TransactionNode will be
    //     created at the beginning of the TransactionNode list;
    // ==================================================
	void checkoutMovie(Movie *movie);

    // ================ returnMovie ===============
    // removes the given movie from the customer's currently check out movies
    //     and adds a return Transaction to the customer's history
    // preconditions: movie is a valid movie object and the customer currently
    //     has it checked out
    //     and is currently checked out by the customer
    // postconditions: the MovieNode containing the given movie
    //     will be deleted from the MovieNode list if it existed
    // ==================================================
	void returnMovie(Movie *movie);

    // ================ hasMovie ===============
    // checks if the customer currently has the given movie checked out
    // preconditions: none;
    // postconditions: returns true if the customer currently has the given movie checked out,
    //     else returns false
    // ==================================================
	bool hasMovie(Movie *movie);

    // ================ printTransactionHistory ===============
    // prints out a nicely formatted list of the customer's transaction history
    //      starting with the most recent transaction
    // preconditions: customer has performed transactions;
    // postconditions: a nicely formatted list of transactions is printed
    // ==================================================
	void printTransactionHistory();
    
    // ================ deleteMovieNodes() ===============
    // Starts the deleteMovieNode chain, calls it on head
    // preconditions: movieHead exists
    // postconditions: all MovieNodes are deleted
    // ==================================================
	void deleteMovieNodes();
    
    // ================ deleteTransactions() ===============
    // Starts the deleteTransactions chain, calls it on head
    // preconditions: transactionHead exists
    // postconditions: all TransactionsNodes and the Transactions inside them are deleted
    // ==================================================
	void deleteTransactions();
    
	private:
	
	struct TransactionNode{ // Nodes of a transaction linked list
		Transaction *transaction = NULL;    //the Transaction
		TransactionNode *next=NULL;         //the next TransactionNode
	};

	struct MovieNode { // Nodes containing the customer's current movies checked out
		Movie *movie = NULL;                // the Movie
		MovieNode *next = NULL;             // the next MovieNode
	};
    
    
	string first;	// Customer's first name
	string last;	// Customer's last name
	int id;			// Customer's ID number

	TransactionNode *transactionHead = NULL;	//customer's first transaction in the list
	MovieNode *movieHead = NULL;				// first movie customer currently has checked out
    
    // ================ deleteMovieNodes(MovieNode*&) ===============
    // Recursively deletes all MovieNodes after the given node, then deletes itself
    // preconditions: node exists
    // postconditions: all MovieNodes after and including the given node are deleted
    // ==================================================
	void deleteMovieNodes(MovieNode*&);
    
    // ================ deleteTransactions(TransactionNode*&) ===============
    // Recursively deletes all TransactionNodes after the given node, then deletes itself
    // preconditions: node exists
    // postconditions: all TransactionNodes after and including the given node are deleted,
    //     as well as the Transactions inside them
    // ==================================================
	void deleteTransactions(TransactionNode*&);
};

#include "movie.h"
#include "transaction.h"
#include "borrow.h"
#include "return.h"

#endif