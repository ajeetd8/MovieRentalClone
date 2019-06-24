// ------------------- moviestore.h --------------------
// Sawyer Knoblich and Elias Muche, CSS 343
// Created 5-25-16
// Last modified 6-8-16
// ---------------------------------------------------
// Purpose: The controller for all MovieStore functions,
//     takes care of reading the input files and calls
//     the appropriate functions
// ---------------------------------------------------

#include <iostream>
#include <stdlib.h> // for atoi to convert strings to ints
#include "movie.h"
#include "customer.h"
#include "transaction.h"
#include "dramamovie.h"
#include "comedymovie.h"
#include "classicmovie.h"
#include <vector>
#include <sstream>
#include <string>
#include <map>
#include <utility> // for pair

using namespace std;

#ifndef MOVIESTORE_H
#define MOVIESTORE_H


class MovieStore{
public:
    
    // ================ constructor ===============
    // initializes default values for fields
    // preconditions: none
    // postconditions: Customer hash table is filled with NULL
    // ==================================================
	MovieStore();
    
    // ================ destructor ===============
    // deletes all allocated memory for entire program
    // preconditions: none
    // postconditions: all allocated memory is deleted
    // ==================================================
	~MovieStore();
    

	//============= methods that read the text files ================

    // ================ readMovies ===============
    // reads through the movies in the given istream and adds them to the movie store
    // preconditions: the given istream contains properly formatted,
    //     but potentially invalid, movies
    // postconditions: the movies in the istream have been added to the appropriate lists
    // ==================================================
	void readMovies(istream &input);
	
    // ================ readCustomers ===============
    // reads through the customers in the given istream and adds them to the hash table
    // preconditions: the given istream contains properly formatted,
    //     but potentially invalid, customers
    // postconditions: the customers have been added to the hash table
    // ==================================================
	void readCustomers(istream &input);

    // ================ readCommands ===============
    // reads through the commands in the given istream and performs the resulting commands
    // preconditions: the given istream contains properly formatted,
    //     but potentially invalid, commands
    // postconditions: the commands in the istream have been performed
    // ==================================================
	void readCommands(istream &input);
	
	
private:
    
    // the size of our Customer hash table array
    const static int defaultSize=501;
    
	struct CustomerNode{//to handle collisions, the customer table will store a linked list in each element 
		Customer *cust=NULL;//customer 
		CustomerNode *next=NULL;//next customer if a collision occurs
		
	};
		
	struct DramaMovieNode{//to handle collisions, the movie table will store a linked list in each element 
		DramaMovie *movie;//movie
		DramaMovieNode *next=NULL;//next movie if a collision occurs 		
	};

	struct ComedyMovieNode{//to handle collisions, the movie table will store a linked list in each element 
		ComedyMovie *movie;//movie
		ComedyMovieNode *next=NULL;//next movie if a collision occurs 		
	};

	struct ClassicMovieNode{//to handle collisions, the movie table will store a linked list in each element 
		ClassicMovie *movie;//movie
		ClassicMovieNode *next=NULL;//next movie if a collision occurs 		
	};
    
    // hash table that holds the customers
    CustomerNode* customerTable[defaultSize];
    
    // ========== methods that add objects to hash tables based on the text files ===========
    
    // ================ addCustomer ===============
    // adds the given Customer to the hash table at the given index
    // preconditions: the given index is in the range of the hash table
    // postconditions: the Customer is added to the hash table, and collisions
    //     are solved by separate chaining
    // ==================================================
    void addCustomer(Customer *customer, int index);
    
    
    // ========== methods that handle commands and transactions =============
    
    //================== checkoutMovie ================
    //Takes a customer and a movie and performs a checkout transaction
    //Pre-conditions: the customer and the movie are not NULL,
    //     and the customer doesn't have the movie already checked out
    //Post-conditions: if the customer didn't have the movie checked out,
    //    they check it out (or an alternative if the stock was 0 and an alternative
    //    was found) and the stock is decreased by 1
    //====================================================
    void checkoutMovie(Customer *customer, Movie *movie);
    
    //================== returnMovie ================
    //Takes a customer and a movie and performs a return transaction
    //Pre-conditions: the customer currently has the movie checked out
    //Post-conditions: if the customer had the movie checked out,
    //    the movie is now returned and the stock is increased by one
    //====================================================
    void returnMovie(Customer *customer, Movie *movie);
    
    //================== printInventory ================
    //Prints the store's stock of movies in a convenient format
    //Pre-conditions: none
    //Post-conditions: this will not be changed
    //=====================================
    void printInventory();
    
    //================== printHistory ================
    //Takes a customer and prints their transaction history
    //Pre-conditions: none
    //Post-conditions: this will not be changed and the customer will not be changed
    //==================================================
    void printHistory(Customer *customer);

    // ================ hashCustomer(Customer) ===============
    // returns a hash number for the given Customer
    // preconditions: the given customer has a valid ID
    // postconditions: returns the Customer's hash number
    // ==================================================
	int hashCustomer(Customer *customer);
    
    // ================ hashCustomer(int) ===============
    // returns a hash number for the given customer ID number
    // preconditions: the given ID number is valid
    // postconditions: returns the ID's hash number
    // ==================================================
    int hashCustomer(int id);
    
    //================== findCustomer ================
    //Takes an int (id number)
    //    and returns the corresponding customer (or null if it wasn't found)
    //Pre-conditions: none
    //Post-conditions: returns a Customer pointer if found, NULL if not
    //================================================
	Customer* findCustomer(int id);

    // ================ addComedy ===============
    // adds the given ComedyMovie* to the list of comedies
    // preconditions: the given ComedyMovie* is not NULL
    // postconditions: the ComedyMovie* is added to the comedy movie list in order
    // ==================================================
	void addComedy(ComedyMovie *movie);
    
    // ================ addDrama ===============
    // adds the given DramaMovie* to the list of dramas
    // preconditions: the given DramaMovie* is not NULL
    // postconditions: the DramaMovie* is added to the drama movie list in order
    // ==================================================
	void addDrama(DramaMovie *movie);
    
    // ================ addClassic ===============
    // adds the given ClassicMovie* to the list of classics
    // preconditions: the given ClassicMovie* is not NULL
    // postconditions: the ClassicMovie* is added to the classic movie list in order
    // ==================================================
	void addClassic(ClassicMovie *movie);
	
    //================== deleteComedy ==================
    //Takes a comedy node and deletes the entire comedy movie list
    //Pre-conditions: none
    //Post-conditions: all of the comdedy movies will be de-allocated
    //====================================================
	void deleteComedy(ComedyMovieNode*& node);
    
    //================== deleteClassic ==================
    //Takes a classic node and deletes the entire classic movie list
    //Pre-conditions: none
    //Post-conditions: all of the classic movies will be de-allocated
    //====================================================
    void deleteClassic(ClassicMovieNode*& node);
    
    //================== deleteDrama ==================
    //Takes a classic node and deletes the entire drama movie list
    //Pre-conditions: none
    //Post-conditions: all of the drama movies will be de-allocated
    //====================================================
	void deleteDrama(DramaMovieNode*& node);
    
    //================== deleteCustomers  ==================
    //Deletes all of the customers
    //Pre-conditions: none
    //Post-conditions: all of the customers will be de-allocated
    //====================================================
	void deleteCustomers();
    
    //================== deleteCustChain  ==================
    //Takes a customer node and deletes the customers in the chain
    //Pre-conditions: none
    //Post-conditions: all of the customers in the chain will be de-allocated
    //====================================================
	void deleteCustChain(CustomerNode*& node);
    
    //================== findClassic ================
    //Takes a string (major actor) and two ints (release year, and release month)
    //     and returns the corresponding classic movie (or null if it wasn't found)
    //Pre-conditions: none
    //Post-conditions: returns a ClassicMovie pointer if found, NULL if not
    //====================================================
    ClassicMovie* findClassic(int month, int year, string majorActor);
    
    //================== findDrama ================
    //Takes two strings (movie title, movie director) and returns the corresponding drama movie (or null if it wasn't found)
    //Pre-conditions: none
    //Post-conditions: returns a DramaMovie pointer if found, NULL if not
    //====================================================
    DramaMovie* findDrama(string director, string title);
    
    //================== findComedy ================
    //Takes a string (movie title) and an int (release year)
    //    and returns the corresponding comedy movie (or null if it wasn't found)
    //Pre-conditions: none
    //Post-conditions: returns a ClassicMovie pointer if found, NULL if not
    //================================================
    ComedyMovie* findComedy(string title, int year);
    
    //================== findAltClassic ================
    //Takes classic movie and finds an alternative(same movie, but different major actor) and returns it if it was found
    //Pre-conditions: the given movie is not NULL
    //Post-conditions: if an alternate movie is found, it is returned, else NULL is returned
    //====================================================
    ClassicMovie* findAltClassic(Movie* movie);

    
    // the head of the list of ClassicMovies
	ClassicMovieNode *classicHead=NULL;
    
    // the head of the list of DramaMovies
	DramaMovieNode *dramaHead=NULL;
    
    // the head of the list of ComedyMovies
	ComedyMovieNode *comedyHead=NULL;
    
    // ================ split ===============
    // returns a vector of string containing the pieces of the given string
    //     that were separated by the given char
    // preconditions: none
    // postconditions: returns a vector of string with the appropriate splits
    // ==================================================
    vector<string> split(const string &s, char delim);
    
    // ================ trim ===============
    // returns a string with the leading and trailing whitespace removed
    //     from the given string
    // preconditions: none
    // postconditions: returns a trimmed string
    // ==================================================
    string trim(string);
    
    //============= printComedy =================
    //Prints the comedy movies in a neat format
    //Pre-conditions: none
    //Post-condition: this will not be changed
    //=============================================
    void printComedy();
    
    //================== printClassic ================
    //Prints the classic movies in a neat format
    //Pre-conditions: none
    //Post-conditions: this will not be changed
    //==================================================
    void printClassic();
    
    //================== printDrama ================
    //Prints the drama movies in a neat format
    //Pre-conditions: none
    //Post-conditions: this will not be changed
    //==================================================
    void printDrama();
};

#endif