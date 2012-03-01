/**
  * Name: Order.cpp
  * Author: Darren Butcher
  * Student #: 012882098
  * Assignment: Assignment #3 - OOP244
  * Last Date Updated: November 26th 2010
  * 
  * Student Oath:
  * "This assignment represents my own work in accordance with Seneca Academic Policy"
  * Signature: Darren Butcher
 **/

#include "Order.h"
#include "ISBNPrefix.h"
#define PREFIX "prefixRanges.txt"  

/*
 * Set object to a safe empty state
 */
void Order::setIsbn(){
    ordered = 0;
    delivered = 0;
    outputStyle = 1;
    this->isbnNo;
}

/*
 * A one-argument constructor that receives a reference to an ISBN object 
 * and initializes an Order object for that ISBN
 */
Order::Order(const ISBN& isbn) {
    setIsbn();
    this->isbnNo = isbn;
}

/*
 * A modifier that receives a style character and resets the output format for the Order object
 */
void Order::style(char c) {
    if(c == ' '){
        outputStyle = 3;
    }
    else if(c == '-'){
        outputStyle = 2;
    }
    else if(c == '\0'){
        outputStyle = 1;
    }
    else{
        outputStyle = 1;
    }
}

/*
 * A query that receives a reference to an ISBN object and returns true 
 * if the Order object is for that ISBN, false otherwise
 */
int Order::has(const ISBN& isbn) const {
    bool flag = false;
    ISBNPrefix list(PREFIX);

    if (isbn == ISBN(isbnNo.getISBN(), list)) 
        flag = true;
    return flag;
}

/*
 * A modifier that receives a reference to an istream object and increases 
 * the number of copies to be ordered based upon data received from input stream is
 */
int Order::order(istream& is){
    bool flag = false;
    bool continueGoing = true; 
    bool isChanged = false;
    int iStream;

    while (continueGoing){
        cout << "Quantity (0 to quit) : ";
        is >> iStream;
        if (!is){
             is.clear();
             is.ignore(2000, '\n');
             cerr << "Error. Try Again " << endl;
        }
        else if(iStream == 0){
             cerr << "**No delivery recorded!" << endl; 
             continueGoing = false;
        }
        else if(iStream < 0){ 
             cerr << "Enter a positive number.  Try again." << endl; 
        }
        else{
             ordered = ordered + iStream;
             isChanged = true;
             continueGoing = false;
        }  
    }
    if(isChanged) 
        flag = true;
    return flag;
}

/*
 * A modifier that receives the number of copies to be added to the current order
 */
int Order::order(int add) {
    bool flag = false;
    ISBNPrefix list(PREFIX);
    ISBN thisISBN(isbnNo.getISBN(), list);

    if (add > 0 && thisISBN.registered()){
        ordered = ordered + add;
        flag = true;
    } 
    return flag;
}

/*
 * A modifier that receives a reference to an istream object 
 * and records receipt of copies based upon data from the input stream
 */
int Order::receive(istream& is){
    bool flag = false;
    bool continueGoing = true; 
    bool isChanged = false;
    int iStream;
 
    while (continueGoing){
        cout << "Quantity (0 to quit) : ";
        is >> iStream;
        if (!is) {
            is.clear();
            is.ignore(2000, '\n');
            cerr << "Error. Try Again " << endl;
        }
        else if (iStream == 0){
            continueGoing = false;
        }
        else if (iStream < 0){
            cerr << "Positive value only. Try again." << endl;
        }
        else if (iStream > ordered){
            cerr << iStream << " not on order. Only " << ordered << " are on order. Try again. " << endl;
        }
        else{
            delivered = delivered + iStream;
            isChanged = true;
            continueGoing = false;
        }
         
    }
    if (isChanged) 
        flag = true;
    return flag;
}

/*
 * A query that receives a reference to an ostream object and displays the current object on the output stream
 */
void Order::display(ostream& os) const {
    ISBNPrefix list(PREFIX);
    ISBN thisISBN(isbnNo.getISBN(), list);
    thisISBN.setStyle(outputStyle);
   
    os << thisISBN << "  " << *this;
}

/*
 * An overloaded operator that receives a reference to an ostream object along with 
 * a reference to an unmodifiable Order object and inserts that object's 
 * information into the specified output stream
 */ 
ostream& operator<<(ostream& os, const Order& order) {
    os << "     " << order.ordered << "       " << order.delivered;
    return os;
}