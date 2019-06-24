// ------------------- moviestore.cpp --------------------
// Sawyer Knoblich and Elias Muche, CSS 343
// Created 5-25-16
// Last modified 6-8-16
// ---------------------------------------------------
// Purpose: Implements the MovieStore class
// ---------------------------------------------------
// Algorithms: The hash algorithm used for the customers
//     hashes the customer's ID number to create a 3-digit index.
//     This index is made of the first digit of the ID, the
//     second digit of the ID, and then the sum of the remaining
//     two digits modded by 10. This resulting index is modded
//     by the bucket size of the array.
// ---------------------------------------------------

#include "moviestore.h"

// ================ constructor ===============
// initializes default values for fields
// preconditions: none
// postconditions: Customer hash table is filled with NULL
// ==================================================
MovieStore::MovieStore(){
    
    for(int i=0;i<defaultSize;i++){
        customerTable[i]=NULL;
    }
}
// end constructor



// ================ destructor ===============
// deletes all allocated memory for entire program
// preconditions: none
// postconditions: all allocated memory is deleted
// ==================================================
MovieStore::~MovieStore(){
    deleteComedy(comedyHead);
    deleteClassic(classicHead);
    deleteDrama(dramaHead);
    deleteCustomers();
    
}
// end destructor



// ================ split ===============
// returns a vector of string containing the pieces of the given string
//     that were separated by the given char
// preconditions: none
// postconditions: returns a vector of string with the appropriate splits
// ==================================================
vector<string> MovieStore::split(const string &s, char delim){
    vector<string> items;
    stringstream ss(s);
    string item;
    
    // read through each part of the string separated by the delim char
    while(getline(ss,item,delim)){
        item = trim(item);
        
        items.push_back(trim(item));

    }
    return items;

}
// end split



// ================ trim ===============
// returns a string with the leading and trailing whitespace removed
//     from the given string
// preconditions: none
// postconditions: returns a trimmed string
// ==================================================
string MovieStore::trim(string item) {
    size_t first = item.find_first_not_of(' ');
    size_t last = item.find_last_not_of(' ');
    return item.substr(first, (last - first + 1));
}
// end trim



// ================ readCommands ===============
// reads through the commands in the given istream and performs the resulting commands
// preconditions: the given istream contains properly formatted,
//     but potentially invalid, commands
// postconditions: the commands in the istream have been performed
// ==================================================
void MovieStore::readCommands(istream &input){
    string currentLine;
    
    // read through each line in the file
    while(getline(input,currentLine)){
        
        // Inventory command, print the inventory
        if(currentLine[0]=='I'){
            printInventory();	
        }

        // Borrow or Return command
        else if(currentLine[0]=='B'||currentLine[0]=='R'){
            // split the line by spaces
            vector<string> currentItems = split(currentLine, ' ');
            
            int custID = atoi(currentItems[1].c_str()); // four digit customer ID
            char rentalType = currentItems[2][0];       // currently it is D for DVD
            char movieType = currentItems[3][0];        // should be C, F, or D;
            
            // pointer to the Movie to be borrowed or returned
            Movie* thisMovie = NULL;
            
            // check for incorrect movieType or rentalType
            if (rentalType == 'D') {
            
                // borrowing or returning a Classic
                if (movieType == 'C') {
                    
                    // get relevant info from line
                    int movieMonth = atoi(currentItems[4].c_str());
                    int movieYear = atoi(currentItems[5].c_str());
                    string majorActor = currentItems[6] + " " + currentItems[7];
                    
                    // remove '\r' from the majorActor string
                    majorActor = split(majorActor, '\r')[0];
                    
                    // find the correct ClassicMovie, or NULL if not found
                    thisMovie = findClassic(movieMonth, movieYear, majorActor);
                    
                    
                } else if (movieType == 'D') { // borrowing or returning a Drama
                    
                    // split by comma to separate director and title
                    vector<string> commaSep = split(currentLine, ',');
                    
                    // string containing only the title;
                    string title = commaSep[1];
                    
                    // string containing the director plus other info
                    string directorString = commaSep[0];
                    
                    // split the string containing the director plus other stuff by spaces
                    //     (this gets the individual words/chars)
                    vector<string> directorSplit = split(directorString, ' ');
                    
                    string director = "";
                    
                    // director name always starts at word of index 4, but it is unknown how long it is,
                    //    so we keep adding the resulting words until we run out
                    for (int i = 4; i < directorSplit.size(); i++) {
                        if (i < currentItems.size() - 1) { // we are not the last item in the directorString
                            director += (directorSplit[i] + " ");
                        } else { // we are the last item in the directorString
                            director += directorSplit[i];
                        }
                    }
                    
                    // find the correct DramaMovie, or NULL if not found
                    thisMovie = findDrama(director, title);
                    
                } else if (movieType == 'F') { // borrowing or returning a Comedy
                    
                    // split to separate title and year
                    vector<string> commaSep = split(currentLine, ',');
                    
                    // contains title plus some other stuff
                    string titleString = commaSep[0];
                    int year = atoi(commaSep[1].c_str());
                    
                    // split title string by space to get invidiaul words + other stuff
                    vector<string> titleSplit = split(titleString, ' ');
                    
                    string title = "";
                    
                    // since the title always starts at the words of index 4,
                    //     add everything from 4 onwards to the title
                    for (int i = 4; i < titleSplit.size(); i++) {
                        if (i < currentItems.size() - 1) { // we are not the last item in the title
                            title += (titleSplit[i] + " ");
                        } else { // we are the last item in the title
                            title += titleSplit[i];
                        }
                    }
                    
                    // find the correct ComedyMovie, or NULL if not found
                    thisMovie = findComedy(title, year);
                    
                } else {
                    // movie type was not 'C', 'D', or 'F', print an error
                    cout << "Error: Invalid command, incorrect movie type in line " << currentLine << endl;
                }
            } else {
                // rental type was not 'D', print an error
                cout << "Error: Invalid command, incorrect rental type" << endl;
            }
            
            // find the customer by their ID
            Customer* thisCustomer = findCustomer(custID);
            
            // if the movie or the customer do not exist display an error,
            //     otherwise borrow or return the movie
            
            if (thisMovie == NULL && (movieType == 'C' || movieType == 'F' || movieType == 'D')) { // invalid movie
                cout << "Error: Invalid movie in line: " << currentLine << endl;
                
            } else if (thisCustomer == NULL) { // invalid customer
                cout << "Error: Invalid customer in line: " << currentLine << endl;
                
            } else { // valid movie and customer
                
                if(currentLine[0]=='R'){
                    returnMovie(thisCustomer, thisMovie);
                }
                else if(currentLine[0]=='B'){
                    checkoutMovie(thisCustomer, thisMovie);
                }
            }
        
        }
        
        else if(currentLine[0]=='H'){ // perform the history command
            
            // split line by spaces and grab customer ID
            vector<string> currentItems=split(currentLine,' ');
            int id=atoi(currentItems[1].c_str());
            
            // find the customer
            Customer *temp=findCustomer(id);
            
            if(temp==NULL){ // customer did not exist
                cout<<"Error: No such Customer with ID " << id << endl;
            }	
            else{ // customer exists, print their transaction history
                temp->printTransactionHistory();
                temp=NULL;
            }
        }
        
        else{
            // command was not 'I', 'B', 'R', or 'H', print error
            cout<<"Error: Invalid action code in line " << currentLine << endl;
        }

    }


}
// end readCommands



// ================ readMovies ===============
// reads through the movies in the given istream and adds them to the movie store
// preconditions: the given istream contains properly formatted,
//     but potentially invalid, movies
// postconditions: the movies in the istream have been added to the appropriate lists
// ==================================================
void MovieStore::readMovies(istream &input){
    string currentLine;
    
    // read file line by line
    while(getline(input,currentLine)){
        
        // split line by space and get movie type
        vector<string> currentItems=split(currentLine,',');
        char Type=currentItems[0].at(0);//type of movie
        
        // variable for movie info
        int Stock;
        string direct;
        string Title;
        int Year;
        
        if(Type=='C') { // adding a Classic movie
            
            // read the info into their variables
            Stock=atoi(currentItems[1].c_str());
            direct=currentItems[2];
            Title=currentItems[3];
            
            // read the ClassicMovie-specific info
            vector<string> classicItems=split(currentItems[4],' ');
            string MA=classicItems[0]+" "+classicItems[1];
            int Month=atoi(classicItems[2].c_str());
            Year=atoi(classicItems[3].c_str());
            
            // create a new ClassicMovie and add it to its list
            ClassicMovie* Cm = new ClassicMovie(Stock,Year,Title,direct,Month,MA);
            addClassic(Cm);

        }

        else if(Type=='D'){ // adding a Drama movie
            
            // read the info into their variables
            Stock=atoi(currentItems[1].c_str());
            direct=currentItems[2];
            Title=currentItems[3];
            Year=atoi(currentItems[4].c_str());
            
            // create a new DramaMovie and add it to its list
            DramaMovie *dm = new DramaMovie(Stock,Year,Title,direct);
            addDrama(dm);
            
        }
        else if(Type=='F'){ // adding a Comedy movie
            
            // read the info into their variables
            Stock=atoi(currentItems[1].c_str());
            direct=currentItems[2];
            Title=currentItems[3];
            Year=atoi(currentItems[4].c_str());
            
            // create a new ComedyMovie and add it to its list
            ComedyMovie *cm = new ComedyMovie(Stock,Year,Title,direct);
            addComedy(cm);

        }
        
    }
}
// end readMovies



// ================ readCustomers ===============
// reads through the customers in the given istream and adds them to the hash table
// preconditions: the given istream contains properly formatted,
//     but potentially invalid, customers
// postconditions: the customers have been added to the hash table
// ==================================================
void MovieStore::readCustomers(istream &input){
    string currentLine;
    
    // read istream line by line
    while(getline(input,currentLine)){
        
        // read the info into their variable
        vector<string> currentItems=split(currentLine,' ');
        int id=atoi(currentItems[0].c_str());
        string first=currentItems[1];
        string last=currentItems[2];
        
        // create a new Customer from the info
        Customer *c=new Customer(first,last,id);
        
        // get its hash number and add it to the Customer list
        int customerIndex = hashCustomer(c);
        addCustomer(c, customerIndex);
    

    }
}
// end readCustomers



// ================ hashCustomer(Customer) ===============
// returns a hash number for the given Customer
// preconditions: the given customer has a valid ID
// postconditions: returns the Customer's hash number
// ==================================================
int MovieStore::hashCustomer(Customer *c) {
    
    int id = c->getCustomerID();
    return hashCustomer(id);
}
// end hashCustomer(Customer)



// ================ hashCustomer(int) ===============
// returns a hash number for the given customer ID number
// preconditions: the given ID number is valid
// postconditions: returns the ID's hash number
// ==================================================
int MovieStore::hashCustomer(int id) {
    
    int firstChar=(id/10)%10;   //third digit of id
    int secondChar=id%10;       //fourth digit of id
    
    // a combination of the third and fourth digits of the ID
    int thirdNum = (firstChar + secondChar) % 10;
    
    
    // the resulting hash number is the first digit of the ID,
    //     the second digit of the ID, and then
    //     the sum of the third and fourth digits, mod 10
    //     Ex. 1234 => 127, 5678 => 56(15 % 10) = 565
    return ((id / 100) * 10 + thirdNum) % defaultSize;
}
// end hashCustomer(int)



// ================ addCustomer ===============
// adds the given Customer to the hash table at the given index
// preconditions: the given index is in the range of the hash table
// postconditions: the Customer is added to the hash table, and collisions
//     are solved by separate chaining
// ==================================================
void MovieStore::addCustomer(Customer *c, int i) {
    
    // if there is already a CustomerNode at this index,
    //     add a new CustomerNode to the beginning of the list
    if(customerTable[i]!=NULL){
		CustomerNode *cn=new CustomerNode;
		cn->cust=c;
		cn->next=customerTable[i];
		customerTable[i]=cn;
		return;
	}
	
    // otherwise, create a new CustomerNode to start the list
	customerTable[i]=new CustomerNode;
	customerTable[i]->next=NULL;
	customerTable[i]->cust=c;
	
}
// end addCustomer



// ================ addDrama ===============
// adds the given DramaMovie* to the list of dramas
// preconditions: the given DramaMovie* is not NULL
// postconditions: the DramaMovie* is added to the drama movie list in order
// ==================================================
void MovieStore::addDrama(DramaMovie *movie){
    
    if (movie == NULL)
        return;
    
    // we are at the beginning of the list
    if(dramaHead==NULL){
        dramaHead= new DramaMovieNode;
        dramaHead->movie=movie;
        return;
    }
    
    DramaMovieNode *n=dramaHead; // pointer to traverse the list
    
    // DramaMovieNode to hold movie
    DramaMovieNode *newDrama=new DramaMovieNode;
    newDrama->movie=movie;

    // check if we should go at the beginning and add if true
    if(dramaHead->movie->getDirector()>movie->getDirector() || (dramaHead->movie->getDirector()==movie->getDirector() && dramaHead->movie->getTitle()>movie->getTitle())){
        newDrama->next=n;
        dramaHead=newDrama;
        return;

    }
    
    // we go after the beginning, find the correct spot and add
    while(n->next!=NULL){
        if(n->next->movie->getDirector()>movie->getDirector() || (n->next->movie->getDirector()==movie->getDirector() && n->next->movie->getTitle()>movie->getTitle())){
            newDrama->next=n->next;
            n->next=newDrama;
            return;

        }
        n=n->next;
    }
    
    // link us to the list
    n->next=newDrama;
}
// end addDrama




// ================ addClassic ===============
// adds the given ClassicMovie* to the list of classics
// preconditions: the given ClassicMovie* is not NULL
// postconditions: the ClassicMovie* is added to the classic movie list in order
// ==================================================
void MovieStore::addClassic(ClassicMovie *movie){
    
    if (movie == NULL)
        return;
    
    // we are the first item in the list, add
    if(classicHead==NULL){
        classicHead=new ClassicMovieNode;
        classicHead->movie=movie;
        classicHead->next = NULL;
        return;
    } 
    ClassicMovieNode *n=classicHead;
    
    // new ClassicMovieNode to hold movie
    ClassicMovieNode *newClassic=new ClassicMovieNode;
    newClassic->movie=movie;

    // if we go at the beginning, add
    if(classicHead->movie->dateComparable()>movie->dateComparable()|| (classicHead->movie->dateComparable()==movie->dateComparable()&& classicHead->movie->getMajorActor()>movie->getMajorActor())){
        newClassic->next=n;
        classicHead=newClassic;
        return;

    }
    
    // find our spot in the list and add
    while(n->next!=NULL){
        if(n->next->movie->dateComparable()>movie->dateComparable()|| (n->next->movie->dateComparable()==movie->dateComparable()&& n->next->movie->getMajorActor()>movie->getMajorActor())){
            newClassic->next=n->next;
            n->next=newClassic;
            return;

        }
        n=n->next;
    }
    
    // link us back to the list
    n->next=newClassic;
}
// end addClassic



// ================ addComedy ===============
// adds the given ComedyMovie* to the list of comedies
// preconditions: the given ComedyMovie* is not NULL
// postconditions: the ComedyMovie* is added to the comedy movie list in order
// ==================================================
void MovieStore::addComedy(ComedyMovie *movie){
    
    if (movie == NULL)
        return;
    
    // we are the first item in the list, add
    if(comedyHead==NULL){
        comedyHead=new ComedyMovieNode;
        comedyHead->movie=movie;
        comedyHead->next = NULL;
        return;
    }
    ComedyMovieNode *n=comedyHead;
    
    // new ComedyMovieNode to hold movie
    ComedyMovieNode *newComedy=new ComedyMovieNode;
    newComedy->movie=movie;

    // if we go at the beginning of the list, add
    if(comedyHead->movie->getTitle()>movie->getTitle()|| (comedyHead->movie->getTitle()==movie->getTitle() && comedyHead->movie->getYear()>movie->getYear())){
        newComedy->next=n;
        comedyHead=newComedy;
        return;

    }
    
    // find our spot in the list and add
    while(n->next!=NULL){
        if(n->next->movie->getTitle()>movie->getTitle()|| (n->next->movie->getTitle()==movie->getTitle() && n->next->movie->getYear()>movie->getYear())){
            newComedy->next=n->next;
            n->next=newComedy;
            return;

        }
        n=n->next;
    }
    
    // link us back to the list
    n->next=newComedy;
}
// end addComedy



//========= printInventory ============
//Prints the store's stock of movies in a convenient format 
//Pre-conditions: none
//Post-conditions: this will not be changed
//=====================================
void MovieStore::printInventory(){
    
    cout << endl << "===== INVENTORY =====" << endl << endl;
    
    printComedy();
    printDrama();
    printClassic();
    
    cout << endl << "===== END OF INVENTORY =====" << endl << endl;

}
// end printInventory



//============= printComedy =================
//Prints the comedy movies in a neat format
//Pre-conditions: none 
//Post-condition: this will not be changed
//=============================================
void MovieStore:: printComedy(){
    ComedyMovieNode *c=comedyHead;
    
    cout << "### Comedies: " << endl;
    
    // loop through list of comedies and print the stock
    while(c!=NULL){
        cout << "Stock for \"" << c->movie->getTitle() << "\" is " << c->movie->getCurrentStock() << endl;
        c=c->next;
    }
    
    cout << endl;
}
// end printComedy



//================== printClassic ================
//Prints the classic movies in a neat format 
//Pre-conditions: none 
//Post-conditions: this will not be changed
//==================================================
void MovieStore:: printClassic(){
    ClassicMovieNode *c=classicHead;
    cout << "### Classics: " << endl;
    
    // create a map to store each title, total stock for that title,
    //     and if there is more than one variation of that title
    map<string, pair<int, bool> > totals;
    pair<int, bool> p;
    
    // loop through the classics and print, also update the total stock for each title
    while(c!=NULL){
    
        cout << "Stock for \"" << c->movie->getTitle() << "\" with " << c->movie->getMajorActor() << " is " << c->movie->getCurrentStock() << endl;
        
        // if the title is not already in the map, create an entry for it
        if(totals.find(c->movie->getTitle()) == totals.end()){
            p.first = c->movie->getCurrentStock();
            p.second = false;
            totals[c->movie->getTitle()] = p;
        } else { // the title is already in the map, add the current stock
                 //     to the previous total stock and set the multiple variations bool to true
            totals[c->movie->getTitle()].first += c->movie->getCurrentStock();
            totals[c->movie->getTitle()].second = true;
        }
        
        c=c->next;
    
    }
    
    cout << endl;
    
    // print out the total stock for all entries in the map with multiple variations
    cout << "# Total stocks for classic movies with multiple variations: " << endl;
    for (map<string, pair<int, bool> >::iterator it = totals.begin(); it != totals.end(); ++it) {
        bool hasMultipleCopies = it->second.second;
        
        if (hasMultipleCopies)
            cout << "Total stock for \"" << it->first << "\" is " << it->second.first << endl;
    }
}

//================== printDrama ================
//Prints the drama movies in a neat format 
//Pre-conditions: none 
//Post-conditions: this will not be changed
//==================================================
void MovieStore:: printDrama(){
    DramaMovieNode *c=dramaHead;
    cout << "### Dramas: " << endl;
    
    // loop through all dramas and print the stock
    while(c!=NULL){
        cout << "Stock for \"" << c->movie->getTitle() << "\" is " << c->movie->getCurrentStock() << endl;
        c=c->next;
    
    }
    cout << endl;
}
// end printDrama



//================== printHistory ================
//Takes a customer and prints their transaction history
//Pre-conditions: none 
//Post-conditions: this will not be changed and the customer will not be changed 
//==================================================
void MovieStore::printHistory(Customer *c) {
    
    c->printTransactionHistory();
}
// end printHistory



//================== findCustomer ================
//Takes an int (id number)
//    and returns the corresponding customer (or null if it wasn't found)
//Pre-conditions: none
//Post-conditions: returns a Customer pointer if found, NULL if not
//================================================
Customer* MovieStore:: findCustomer(int id) {
    
    int index = hashCustomer(id);
    
    CustomerNode* temp=customerTable[index];
    while(temp!=NULL){
        if(temp->cust->getCustomerID()==id){
            return temp->cust;
        }
        temp=temp->next;

    }
    return NULL;


}
// end findCustomer



//================== findComedy ================
//Takes a string (movie title) and an int (release year)
//    and returns the corresponding comedy movie (or null if it wasn't found)
//Pre-conditions: none 
//Post-conditions: returns a ComedyMovie pointer if found, NULL if not
//================================================
ComedyMovie* MovieStore::findComedy(string title, int year) {
    
    title = trim(title);
    
    ComedyMovieNode *n=comedyHead;
    
    while(n!=NULL){
        if (n->movie->getTitle() == title && n->movie->getYear() == year) {
            return n->movie;
        }
        n=n->next;
    }
    
    // not found, return null
    return NULL;
}
// end findComedy


//================== findClassic ================
//Takes a string (major actor) and two ints (release year, and release month)
//     and returns the corresponding classic movie (or null if it wasn't found)
//Pre-conditions: none 
//Post-conditions: returns a ClassicMovie pointer if found, NULL if not
//====================================================
ClassicMovie* MovieStore::findClassic(int month, int year, string majorActor) {
    
    majorActor = trim(majorActor);
    
    ClassicMovieNode *n=classicHead;
    
    while(n!=NULL){
        if (n->movie->getMonthReleased() == month && n->movie->getYear() == year && n->movie->getMajorActor() == majorActor) {
            return n->movie;
        }
        n=n->next;
    }
    
    // not found, return null
    return NULL;
}
// end findClassic


//================== findDrama ================
//Takes two strings (movie title, movie director) and returns the corresponding drama movie (or null if it wasn't found)
//Pre-conditions: none 
//Post-conditions: returns a DramaMovie pointer if found, NULL if not
//====================================================
DramaMovie* MovieStore::findDrama(string director, string title) {
    
    title = trim(title);
    director = trim(director);
    
    DramaMovieNode *n=dramaHead;
    
    while(n!=NULL){
        if (n->movie->getDirector() == director && n->movie->getTitle() == title) {
            return n->movie;
        }
        n=n->next;
    }
    
    // not found, return null
    return NULL;
}

//================== checkoutMovie ================
//Takes a customer and a movie and performs a checkout transaction
//Pre-conditions: the customer and the movie are not NULL,
//     and the customer doesn't have the movie already checked out
//Post-conditions: if the customer didn't have the movie checked out,
//    they check it out (or an alternative if the stock was 0 and an alternative
//    was found) and the stock is decreased by 1
//====================================================
void MovieStore::checkoutMovie(Customer *customer, Movie *movie) {
    
    if (customer == NULL || movie == NULL)
        return;
    
    // display error if customer already has movie
    if (customer->hasMovie(movie)) {
        cout << "Error: Customer " << customer->getCustomerIDString() << " has already checked out \"" << movie->getTitle() << "\" without returning it" << endl;
        return;
    }
    
    // if the movie is in stock, check it out
    if (movie->getCurrentStock() > 0) {
        customer->checkoutMovie(movie);
        movie->checkoutRental();
    } else { // the movie is out of stock, display error
        cout << "Movie out of stock";
        
        // if the movie is a classic, check if there is another version of it
        if (movie->getType() == 'C') {
            ClassicMovie* altClassic = findAltClassic(movie);
            
            // if another version exists, check that one out instead
            if (altClassic != NULL) {
                cout << ", checking out the variation of \"" << altClassic->getTitle() << "\" with " << altClassic->getMajorActor() << " instead";
                customer->checkoutMovie(altClassic);
                altClassic->checkoutRental();
            }
        }
        
        cout << endl;
    }
}
// end checkoutMovie



//================== findAltClassic ================
//Takes classic movie and finds an alternative(same movie, but different major actor) and returns it if it was found  
//Pre-conditions: the given movie is not NULL
//Post-conditions: if an alternate movie is founded, it is return, else NULL is returned
//====================================================
ClassicMovie* MovieStore:: findAltClassic(Movie* movie){
    
    if (movie == NULL)
        return NULL;
    
    ClassicMovie *c = dynamic_cast<ClassicMovie*>(movie);
    
    // loop through the list of classics to find another variation
    ClassicMovieNode* temp=classicHead;
    while(temp!=NULL){
        
        // if they are the same movie but a different major actor, return that movie
        if(temp->movie->isSame(c)&&(temp->movie->getMajorActor()!=c->getMajorActor())){
            if(temp->movie->getCurrentStock()>0){
                return temp->movie;
            }
            
        }
        temp=temp->next;
        
    }
    
    // no alternate found, return NULL
    return NULL;
}
// end findAltClassic



//================== returnMovie ================
//Takes a customer and a movie and performs a return transaction
//Pre-conditions: the customer currently has the movie checked out
//Post-conditions: if the customer had the movie checked out,
//    the movie is now returned and the stock is increased by one
//====================================================
void MovieStore:: returnMovie(Customer* cust, Movie* movie){

    if(cust->hasMovie(movie)){
        movie->returnRental();
        cust->returnMovie(movie);
    }
}
// end returnMovie



////////////////////////////////////////////////////////////

//================== deleteComedy  ==================
//Takes a comedy node and deletes the entire comedy movie list
//Pre-conditions: none 
//Post-conditions: all of the comdedy movies will be de-allocated
//====================================================
void MovieStore::deleteComedy(ComedyMovieNode*& node){
	if(node==NULL){
		return;
	}

	deleteComedy(node->next);
	delete node->movie;
	node->movie=NULL;
	delete node;
	node=NULL;
}
// end deleteComedy



//================== deleteClassic  ==================
//Takes a classic node and deletes the entire classic movie list
//Pre-conditions: none 
//Post-conditions: all of the classic movies will be de-allocated
//====================================================
void MovieStore::deleteClassic(ClassicMovieNode*& node){
	if(node==NULL){
		return;
	}

	deleteClassic(node->next);
	delete node->movie;
	node->movie=NULL;
	delete node;
	node=NULL;


}
// end deleteClassic



//================== deleteDrama  ==================
//Takes a drama node and deletes the entire drama movie list
//Pre-conditions: none 
//Post-conditions: all of the drama movies will be de-allocated
//====================================================
void MovieStore::deleteDrama(DramaMovieNode*& node){
	if(node==NULL){
		return;
	}

	deleteDrama(node->next);
	delete node->movie;
	node->movie=NULL;
	delete node;
	node=NULL;
}
// end deleteDrama



//================== deleteCustomers  ==================
//Deletes all of the customers
//Pre-conditions: none 
//Post-conditions: all of the customers will be de-allocated
//====================================================
void MovieStore::deleteCustomers(){
	
	for(int i=0;i<defaultSize;i++){
		if(customerTable[i]!=NULL){
			deleteCustChain(customerTable[i]);
		}
		
	}


}
// end deleteCustomers



//================== deleteCustChain  ==================
//Takes a customer node and deletes the customers in the chain
//Pre-conditions: none 
//Post-conditions: all of the customers in the chain will be de-allocated
//====================================================
void MovieStore::deleteCustChain(CustomerNode*& node){

	if(node==NULL){
		return;

	}
	deleteCustChain(node->next);
	node->cust->deleteMovieNodes();
	node->cust->deleteTransactions();
	delete node->cust;
	node->cust=NULL;
	delete node;
	node=NULL;
}
// end deleteCustChain