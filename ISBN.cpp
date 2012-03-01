/**
  * Name: ISBN.cpp
  * Author: Darren Butcher
  * Student #: 012882098
  * Assignment: Assignment #3 - OOP244
  * Last Date Updated: Nov 26th 2010
  * 
  * Student Oath:
  * "This assignment represents my own work in accordance with Seneca Academic Policy"
  * Signature: Darren Butcher
 **/

#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;
#include "ISBN.h"
#include "ISBNPrefix.h"

/*
 * A no-argument constructor that creates an ISBN object in a safe empty state 
 */
ISBN::ISBN(){
    strcpy(isbnNumber, "");
    strcpy(area, "");
    strcpy(publisher, "");
    strcpy(title, "");
    outputStyle = 1; //Default sytle
    isbnRegistered = false; //Registered starts as false	
}

/*
 * A two-argument constructor that creates an ISBN object from a C-style, 
 * null-terminated string and checks for registration using a 
 * reference to an ISBNPrefix object 
 */
ISBN::ISBN(const char* str, const ISBNPrefix& list){
    isbnRegistered = false;
    if(isValid(str)){
        strcpy(isbnNumber, str);
        if(isRegistered(list)){
            this->outputStyle = 2;
        }else{
            this->outputStyle = 1;
        }       
    }else{
        // Set to Safe State
        strcpy(isbnNumber, "");
        strcpy(area, "");
        strcpy(publisher, "");
        strcpy(title, "");
        outputStyle = 1; 
    }		
}

/*
 * A modifier that receives a single character and sets the output style 
 * If the ISBN is registered and the character received is ' ', '-'  or '\0', 
 * this member function sets the output style to the corresponding one.  
 * Otherwise, this member function leaves the style unchanged. 
 */
void ISBN::style(char c){
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
 * A query that returns true if the object is in a safe empty state, false otherwise
 */ 
bool ISBN::empty() const{
    bool flag = false;
    if(strcmp(isbnNumber, "") == 0 && strcmp(area, "") == 0 && strcmp(publisher, "") == 0 && strcmp(title, "") == 0){
        flag = true;
    }
    return flag;
}

/*
 * A query that returns true if the object is registered, false otherwise 
 */
bool ISBN::registered() const{
    bool flag = false;
    if(isbnRegistered == true){
        flag = true;
    }
    return flag;
}

/*
 * A query that passes the ISBN string through the function's parameter 
 * in the form of an unformatted, C-style, null-terminated string 
 */
void ISBN::toStr(char* str) const{
    strcpy(str, isbnNumber);
}

/*
 * A query that returns the ISBN string through the function's parameter 
 * in the form of a formatted C-style null-terminated string 
 * This string consists of the area, publisher and title components separated by the style delimiter 
 * for a registered object (as shown above).  The string is in 
 * the concatenated style if the object is unregistered. 
 */
void ISBN::toStrWithStyle(char* str) const{
    if(outputStyle == 3){
        strcpy(str,area);
        strcat(str," ");
        strcat(str,publisher);
        strcat(str," ");
        strcat(str,title);
        strcat(str," ");
        str[12] = isbnNumber[9];
        str[13] = '\0';
    }
    else if(outputStyle == 2){
        strcpy(str,area);
        strcat(str,"-");
        strcat(str,publisher);
        strcat(str,"-");
        strcat(str,title);
        strcat(str,"-");
        str[12] = isbnNumber[9];
        str[13] = '\0';
    }
    else if(outputStyle == 1){
        strcpy(str, isbnNumber);
    }
}

/*
 * A private modifier that receives a reference to an ISBNPrefix object and, 
 * if possible, decomposes an ISBN string into area, publisher and title components 
 */
bool ISBN::isRegistered(const ISBNPrefix& list){
    int i = 0;
    char value[6]; 
    int areaFound = 0;  
    int valueToInt = 0;
    int valueLen = 0;
    int pubLen = 0;
    char tempVal[6];
    char pub[8];
    char tempPub[8];
    char titleLine[6];
    int notFound = 0;

    // If the string is valid ex. "0000000000"
    // While areaFound is not true and the area is less than 5 example.
    // area->[99926] publisher range->[600 - 999].
    
    if(isValid(isbnNumber) == true){ 
        while(!areaFound && i<5){
	    
           // Copy ISBN into temporary area called Value.
           // Convert value from string to a integer, so
           // that it can be passed into registeredArea as an Int.

            value[i] = isbnNumber[i];
            value[i+1] = '\0';
            valueToInt = atoi(value);
	     
            // Checks is integer is a registered Area 
            // If so adds a NULL byte end of temp Area string
            // Set areaFound to true.
            // Else set areaFound to false and increment i. 
            // The process will continue to loop until area found or 
            // 5 numbers are copied into the Area. 

            if(list.registered(valueToInt) == true){
                valueLen = strlen(value); 
                strcpy(area,value);               
                areaFound = 1;
            }else{
                areaFound = 0;
                i++;
            } 
        }
	
        if(areaFound){

            // If area is FOUND copy chars into publisher. 
            // (strlen(str) - valueLen) - Tells how much chars need to be copied.
            // str[valueLen + i] - Tells start of Publisher chars.
            // Adds the NULL byte to the string. 

            for(i = 0; i <(strlen(isbnNumber) - valueLen) && isbnNumber[i] != '\0'; i++){     
                pub[i] = isbnNumber[valueLen + i];
                pub[i+1] = '\0';      
            }

            // On every repitition, checks if tempPub is a registered ISBN
            // Loops until end of string or Publisher Found.
            // Returns true if found.

            for(i = 0; i < (strlen(isbnNumber) - valueLen) && !notFound; i++){
                tempPub[i] = pub[i];
                tempPub[i+1] = '\0';
	     
                if(list.registered(valueToInt, tempPub)== true){
                    pubLen = strlen(tempPub); 
                    strcpy(publisher, tempPub);
		  
                    for(i = 0; i < ((strlen(isbnNumber) -  (valueLen + pubLen))-1); i++){
                        titleLine[i] = isbnNumber[(valueLen + pubLen) +i];
                        titleLine[i+1] = '\0';
                    }
                    strcpy(title, titleLine);
                    notFound = 1;
                    isbnRegistered = true;
                    return notFound;
                }
            }
        }
        else{
            // Return False if area NOT found.
            return false;
        } 
    }
    else{
	// Return False if ISBN is NOT valid.
	return false;
    }
}

/*
 * A query that receives a reference to an  ostream object and inserts the ISBN string 
 * in the current output style into the output stream os
 */  
void ISBN::display(ostream& os) const{
    char displayString[14];
    strcpy(displayString, isbnNumber);

    if(isbnRegistered){
        toStrWithStyle(displayString);
    }
    else{
        toStr(displayString);
    }
    os.width(13);
    os << right << displayString;
}

/* 
 * A modifier that receives a reference to an istream object along with a reference 
 * to an ISBNPrefix object, reads an ISBN string from the input stream and, 
 * if possible, stores it in the current object 
 */
bool ISBN::read(istream& is, const ISBNPrefix& list){
    char isbnString[11];
    int continueGoing = true;
    int flag = false;
	
    do{
        cout << "ISBN (0 to quit): ";
        is.getline(isbnString, 11);
        if(is == false){
            is.clear();
	     is.ignore(2000, '\n');
            cerr << "Error. Try Again " << endl;
        }else if(strcmp(isbnString, "0") == 0){ 
            continueGoing = false;
        }else if(strlen(isbnString) != 10){ 
            cerr << "Too few characters. Try again." << endl;
        }else if(isValid(isbnString) == false){
            cerr << "Invalid check digit. Try again." << endl;
        }else{
            strcpy(isbnNumber, isbnString);
            isRegistered(list);
            ISBN(isbnString, list);
            flag = true;
            continueGoing = false;
         }
		
    }while(continueGoing == true);
    return flag;
}

/*
 * A GLOBAL function that checks whether an ISBN number is valid
 */
bool isValid(const char* str){
    int strLength = 0;
    int i = 0;
    int subTotal = 0;
    int tenDecrementToTwo = 10;
    int remainder = 0;
    int returnCase = 1;
   
    // Checks if string is empty.
    // If empty return false.
    if (str != NULL && str !=""){
        strLength = strlen(str); 
    }else{      
        return false; 
    }

    // Decrements from 10 to 2 and multiplying the products
    // and then adding them into subtotal.
    // Checks subtotal Modulo 11 and gets value.
    // Returns true if str is valid else returns false.
 
    if (strLength == 10){
        for (i = 0; i < (strLength -1); i++){
            if (str[i] >= '0' && str[i] <= '9')
                subTotal =  subTotal + ((str[i] - '0') * ((--tenDecrementToTwo)+1)); 
        }

        if (str[9] == 'X'){     
            subTotal = subTotal + 10;
        }
        else{
            subTotal = subTotal + (str[i] - '0');
        }
        remainder = subTotal % 11; 
    }
    else{
        remainder = 1;
    }

    if (remainder){ 
       returnCase = 0;
    }
    return returnCase;
}

/*
 * An overloaded operator that receives references to two unmodifiable ISBN objects 
 * and compares the objects for equality.
 */
int operator==(const ISBN& left, const ISBN& right) {
    bool flag = false;

    if (strcmp(left.isbnNumber, right.isbnNumber) == 0) 
        flag = true;
    return flag;
}

/*
 * An overloaded operator that receives a reference to an ostream object 
 * along with a reference to an unmodifiable ISBN object and display 
 * the object on the specified output stream. 
 */
ostream& operator<<(ostream& os, const ISBN& isbn) {
    char isbnString[14];

    strcpy(isbnString, isbn.isbnNumber);
    
    if (isbn.isbnRegistered){
        isbn.toStrWithStyle(isbnString);
    }
    else{
        isbn.toStr(isbnString);
    }	
    cout.width(13);        
    cout << right << isbnString; 
}