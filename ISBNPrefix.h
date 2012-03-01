/**
  * Name: ISBNPrefix.h
  * Author: Darren Butcher
  * Student #: 012882098
  * Assignment: Assignment #3 - OOP244
  * Last Date Updated: Nov 26th 2010
  * 
  * Student Oath:
  * "This assignment represents my own work in accordance with Seneca Academic Policy"
  * Signature: Darren Butcher
 **/

class ISBNPrefix{
        FILE* fp;
        ISBNPrefix(const ISBNPrefix& source);           
        ISBNPrefix& operator=(const ISBNPrefix& source);
     
    public:
        ISBNPrefix(const char* filename);
        bool registered(int area) const;
        int minNoDigits(int area) const;
        int registered(int area, const char* publisher) const;
        ~ISBNPrefix();
};
