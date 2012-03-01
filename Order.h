/**
  * Name: Order.h
  * Author: Darren Butcher
  * Student #: 012882098
  * Assignment: Assignment #3 - OOP244
  * Last Date Updated: November 26th 2010
  * 
  * Student Oath:
  * "This assignment represents my own work in accordance with Seneca Academic Policy"
  * Signature: Darren Butcher
 **/
#include <cstdio>  
#include <cstdlib>  
#include <cstring>
#include <iostream>
using namespace std;
#include "ISBN.h"

class Order {
        int ordered;
        int delivered;
        int outputStyle;
        ISBN isbnNo;

    public:
        Order(){ setIsbn(); } // Set safe emty calling setIsbn mutator method
        Order(const ISBN& isbn);
        void setIsbn(); // Mutator 
        void style(char c);
        int has(const ISBN& isbn) const;
        int onOrder() const{ return ordered; } // Returns Ordered
        int order(istream& is);
        int order(int add);
        int receive(istream& is);
        void display(ostream& os) const;
      
        // Overloaded Operator
        friend ostream& operator<<(ostream& os, const Order& order);
};