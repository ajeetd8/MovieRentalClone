// ------------------- customer.cpp --------------------
// Sawyer Knoblich and Elias Muche, CSS 343
// Created 5-25-16
// Last modified 6-7-16
// ---------------------------------------------------
// Purpose: Implements the Customer class
// ---------------------------------------------------

#include "customer.h"

// ================ empty constructor ===============
// initializes fields to default values
// preconditions: none
// postconditions: first and last name are empty string and id is -1
// ==================================================
Customer::Customer() {
    first = "";
    last = "";
    id = -1;
}
// end empty constructor



// ================ constructor ===============
// initializes fields to given values
// preconditions: none
// postconditions: first and last are the given strings
//     and id is the given id
// ==================================================
Customer::Customer(string _first, string _last, int _id) {
	first = _first;
	last = _last;
	id = _id;
}
// end constructor



// ================ getCustomerID ===============
// getter for the customer id number
// preconditions: none
// postconditions: returns the customer id as an int
// ==================================================
int Customer::getCustomerID() {
	return id;
}
// end getCustomerID


// ================ getCustomerIDString ===============
// getter for the customer id number as a string
// preconditions: id is a 4 digit number
// postconditions: returns the customer id as a string
// ==================================================
string Customer::getCustomerIDString() {
	string output = "";
	int myID = id;
    
    // go through the number from beginning to end
    //     and read each int into output as a char
    int baseNumber = 0;
	for (int i = 3; i >= 0; i--) {
        baseNumber = pow(10, i);
        output += (char)((myID / baseNumber) + '0');
        myID %= baseNumber;
	}
	
	return output;
}
// end getCustomerIDString



// ================ getName ===============
// getter for the customer's full name
// preconditions: none
// postconditions: returns the customer full name
//     formatted as "first last"
// ==================================================
string Customer::getName() {
	return first + " " + last;
}
// end getName



// ================ checkoutMovie ===============
// adds the given movie to the customer's currently check out movies
//     as well as a borrow Transaction to the transaction history
// preconditions: movie is a valid movie object
// postconditions: the given movie will be held in a MovieNode at
//     the beginning of the MovieNode list and a TransactionNode will be
//     created at the beginning of the TransactionNode list;
// ==================================================
void Customer::checkoutMovie(Movie *movie) {

	// if the customer has already checked out this movie, don't let them do it again,
    //     also return if the movie is NULL
	if (hasMovie(movie) || movie == NULL)
		return;
	
    // add the movie to the list of currently checked out movies
	MovieNode *oldMovieHead = movieHead;

	movieHead = new MovieNode;
	movieHead->movie = movie;
	movieHead->next = oldMovieHead;

    // put a Borrow transaction into the customer's transaction history
	TransactionNode *oldTransactionHead = transactionHead;

	transactionHead = new TransactionNode;
	transactionHead->transaction = new Borrow(this, movie);
	transactionHead->next = oldTransactionHead;
     
}
// end checkoutMovie



// ================ returnMovie ===============
// removes the given movie from the customer's currently check out movies
//     and adds a return Transaction to the customer's history
// preconditions: movie is a valid movie object and the customer currently
//     has it checked out
//     and is currently checked out by the customer
// postconditions: the MovieNode containing the given movie
//     will be deleted from the MovieNode list if it existed
// ==================================================
void Customer::returnMovie(Movie *movie) {

	MovieNode *current = movieHead;

    // return if movie is NULL or customer doesn't have it checked out
	if (current == NULL || !hasMovie(movie))
		return;

    // if the movie we are returning is at the start of the movie list, delete it
    if (movieHead->movie == movie) {
        MovieNode *toDelete = movieHead;
		movieHead = movieHead->next;
        delete toDelete;
    } else {

        // otherwise loop through the list and remove it
        while (current->next != NULL) {

            if (current->next->movie == movie) {
                MovieNode *toDelete = current->next;
                current->next = current->next->next;
                delete toDelete;
                return;
            }

            current = current->next;
        }
    }

    
    // put a Return transaction into the customer's transaction history
	TransactionNode *oldTransactionHead = transactionHead;

	transactionHead = new TransactionNode;
	transactionHead->transaction = new Return(this, movie);
	transactionHead->next = oldTransactionHead;
}
// end returnMovie



// ================ hasMovie ===============
// checks if the customer currently has the given movie checked out
// preconditions: none;
// postconditions: returns true if the customer currently has the given movie checked out,
//     else returns false
// ==================================================
bool Customer::hasMovie(Movie *movie) {
	MovieNode *current = movieHead;

	while (current != NULL) {

		// we found the movie, return true
		if (current->movie == movie)
			return true;

		current = current->next;
	}

	// movie not found
	return false;
}
// end hasMovie



// ================ printTransactionHistory ===============
// prints out a nicely formatted list of the customer's transaction history
//      starting with the most recent transaction
// preconditions: customer has performed transactions;
// postconditions: a nicely formatted list of transactions is printed
// ==================================================
void Customer::printTransactionHistory() {
	TransactionNode *current = transactionHead;

	// no transaction history, return error message
    if (current == NULL) {
        cout << "No transaction history for " << getName() << " (" << getCustomerIDString() << ")" << endl << endl;
        return;
    }

	// intro line for customer
    cout << "Transaction history for " << getName() << " (" << getCustomerIDString() << "):" << endl;

	// loop through all transactions
	// put info for each movie into output
	while (current != NULL) {

		// format transaction type for easier reading
		if (current->transaction->transactionType == 'B')
            cout << "Borrowed \"";
		else if (current->transaction->transactionType == 'R')
			cout << "Returned \"";

        cout << current->transaction->movie->getTitle() << "\"" << endl;
        current = current->next;
	}
    
    cout << endl;
}
// end printTransactionHistory



// ================ deleteMovieNodes() ===============
// Starts the deleteMovieNode chain, calls it on head
// preconditions: movieHead exists
// postconditions: all MovieNodes are deleted
// ==================================================
void Customer::deleteMovieNodes(){
	deleteMovieNodes(movieHead);
    delete movieHead;
}
// end deleteMovieNodes



// ================ deleteMovieNodes(MovieNode*&) ===============
// Recursively deletes all MovieNodes after the given node, then deletes itself
// preconditions: node exists
// postconditions: all MovieNodes after and including the given node are deleted
// ==================================================
void Customer::deleteMovieNodes(MovieNode*& node){
    if(node==NULL){
		return;

	}
    
    // delete all nodes after us
	deleteMovieNodes(node->next);
    
    // delete ourself
	delete node;
	node=NULL;
}
// end deleteMovieNodes(MovieNode*&)



// ================ deleteTransactions() ===============
// Starts the deleteTransactions chain, calls it on head
// preconditions: transactionHead exists
// postconditions: all TransactionsNodes and the Transactions inside them are deleted
// ==================================================
void Customer::deleteTransactions(){
	deleteTransactions(transactionHead);
}
// end deleteTransactions()



// ================ deleteTransactions(TransactionNode*&) ===============
// Recursively deletes all TransactionNodes after the given node, then deletes itself
// preconditions: node exists
// postconditions: all TransactionNodes after and including the given node are deleted,
//     as well as the Transactions inside them
// ==================================================
void Customer::deleteTransactions(TransactionNode*& node){
	if(node==NULL){
		return;
	}
    
    // deletes all nodes after node
	deleteTransactions(node->next);
    
    // delete our Transaction and ourself
	delete node->transaction;
	node->transaction=NULL;
	delete node;
	node=NULL;

}
// end deleteTransactions(TransactionNode*&)