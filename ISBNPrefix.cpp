/**
  * Name: ISBNPrefix.cpp
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
#include <cstring>
#include <cstdlib>
#include "ISBNPrefix.h"

/* 
 * A one-argument constructor that receives a C-style, 
 * null-terminated string containing the name of a file that holds the prefix table 
 */
ISBNPrefix::ISBNPrefix(const char* filename) 
{	
    fp = fopen(filename, "r");
}   

/*
 * A query that receives an area identifier and determines if the area is listed 
 */
bool ISBNPrefix::registered(int area) const
{
    char fld2[8], fld3[8];
    int areaNum = 0;
    bool found = false;
   
    rewind (fp);
    while(!found && (3 == fscanf(fp, "%d %s %s\n", &areaNum, fld2, fld3))){
        if(area == areaNum){
            found = true;
	 }
    }
    return found;
}

/*
 * A query that receives an area identifier and determines the minimum number of digits 
 * in any publisher identifier registered under that area 
 */
int ISBNPrefix::minNoDigits(int area) const
{
    char fld2[8], fld3[8];
    int areaNum;

    rewind (fp);
    while(3 == fscanf(fp, "%d %s %s\n", &areaNum, fld2, fld3)){
        if(area == areaNum)
        return strlen(fld2);
    }
    return 0;
}

/* 
 * A query that receives an area identifier along with a publisher identifier 
 * and determines if the publisher identifier is within a publisher range listed under that area
 */ 
int ISBNPrefix::registered(int area, const char* publisher) const
{
    char fld2[8], fld3[8];
    int areaNum = 0;
    bool found = false;
    int fld2toInt;
    int fld3toInt;
    int publishertoInt;

    rewind (fp);
    while(!found && (3 == fscanf(fp, "%d %s %s\n", &areaNum, fld2, fld3))){
        fld2toInt = atoi(fld2);
        fld3toInt = atoi(fld3);
        publishertoInt = atoi(publisher);
        if(area == areaNum){
            if(strlen(publisher) >= strlen(fld2)){
                if(publishertoInt >= fld2toInt && publishertoInt <= fld3toInt){
                    found = true;
                }
            }
        }
    }
    return found;
}

/*
 * A destructor that cleans up before the current object goes out of scope  
 */
ISBNPrefix::~ISBNPrefix()
{
    fclose(fp);
}

/*
 *  A copy constructor that receives a reference to a ISBNPrefix object. 
 */
ISBNPrefix::ISBNPrefix(const ISBNPrefix& source){
    *this = source;
}

/*
 *  An assignment operator that receives a reference to an unmodifable ISBNPrefix object. 
 */
ISBNPrefix& ISBNPrefix::operator=(const ISBNPrefix& source){
    delete fp;
    fp = source.fp;	
    return *this;
}
