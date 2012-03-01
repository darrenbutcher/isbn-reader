/**
  * Name: ISBN.h
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

class ISBNPrefix;

class ISBN{
        char isbnNumber[13];
        char area[6];
        char publisher[8];
        char title[8];
        int outputStyle;
        bool isbnRegistered;
        bool isRegistered(const ISBNPrefix& list);

    public:
        ISBN();
        ISBN(const char* str, const ISBNPrefix& list);
        bool isregistered(const ISBNPrefix& list);
        void style(char c);
        bool empty() const;
        bool registered() const;
        void toStr(char* str) const;
        void toStrWithStyle(char* str) const;
        void display(ostream& os) const;
        bool read(istream& is, const ISBNPrefix& list);
		
        // Accessors and Mutators
        const char * getArea() const { return area; }
        const char * getPublisher() const {return publisher; }
        const char * getTitle() const { return title; }
        const char * getISBN() const { return isbnNumber; }
        void setStyle(int style){ outputStyle = style; }
              
        // Overloaded Operators
        friend int operator==(const ISBN& left, const ISBN& right);
        friend ostream& operator<<(ostream& os, const ISBN& isbn);
};

bool isValid(const char* str);
