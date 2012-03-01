// Bookstore Order Processor
// OOP244.101 - Assignment 3
// a3main.cpp
// Version 1.00
// Chris Szalwinski
// Jan 10 2010

#include <cstdio>
#include <iostream>
using namespace std;
#include "ISBNPrefix.h"
#include "Order.h"

#define MAXORDERS 100
char menu(istream& is);
char style(istream& is);

int main() {
    char c, choice;
    int noOrders = 0;
    Order* order[MAXORDERS];
    ISBNPrefix prefixList("prefixRanges.txt");

    cout << "Bookstore Order Processor\n"
         << "=========================\n";

    // process user input
    do {
        choice = menu(cin);
        cout << endl;
        switch(choice) {
            case 'P':
                {
                    ISBN isbn;
                    if (isbn.read(cin, prefixList)) {
                        int index = -1, created = false;
                        for (int i = 0; i < noOrders && index == -1; i++)
                            if (order[i]->has(isbn))
                                index = i;
                        if (index == -1)
                            if (noOrders < MAXORDERS) {
                                index = noOrders;
                                order[noOrders++] = new Order(isbn);
                                created = true;
                            }
                            else
                                cerr << "No space for more orders!" << endl;
                        if(!order[index]->order(cin) && created)
                            delete order[--noOrders];
                    }
                }
                break;
            case 'A':
                {
                    ISBN isbn;
                    if (isbn.read(cin, prefixList)) {
                        int index = -1;
                        for (int i = 0; i < noOrders && index == -1; i++)
                            if (order[i]->has(isbn))
                                index = i;
                        if (index != -1)
                            order[index]->order(1);
                        else {
                            cerr << "No order for ";
                            isbn.display(cerr);
                            cerr << " found!" << endl;
                        }
                    }
                }
                break;
            case 'D':
                {
                    ISBN isbn;
                    if (isbn.read(cin, prefixList)) {
                        int index = -1;
                        for (int i = 0; i < noOrders && index == -1; i++)
                            if (order[i]->has(isbn))
                                index = i;
                        if (index != -1)
                            order[index]->receive(cin);
                        else {
                            cerr << "No order for ";
                            isbn.display(cerr);
                            cerr << " found!" << endl;
                        }
                    }
                }
                break;
            case 'V':
                cout << "         ISBN  Ordered  Delivered\n";
                cout << "---------------------------------\n";
                for (int i = 0; i < noOrders; i++) {
                    order[i]->display(cout);
                    cout << endl;
                }
                break;
            case 'C':
                c = style(cin);
                for (int i = 0; i < noOrders; i++) {
                    order[i]->style(c);
                }
                break;
        }
    } while (choice != 'Q');

    cout << "\nSigning off ... " << endl;
    // deallocate order memory
    for (int i = 0; i < noOrders; i++)
        delete order[i];
    return 0;
}

// menu prompts for and accepts an option selection from standard input and
// returns the character identifying the selected option
//
char menu(istream& is) {
    char c;
    int  ok = false;

    cout << '\n';
    cout << "Please select from the following options :\n";
    cout << " P - Place an order with a publisher\n";
    cout << " A - Add one copy to an existing order\n";
    cout << " D - Record a delivery from a publisher\n";
    cout << " V - View status of books on order\n";
    cout << " C - Configure order display\n";
    cout << " Q - Quit\n";
    do {
        cout << " Your selection : ";
        c = ' ';
        is.get(c);
        if (c >= 'a' && c <= 'z')
            c -= 'a' - 'A';
        if (is.fail()) {
            is.clear();
            is.ignore(2000, '\n');
            cerr << " Invalid input.  Try again." << endl;
        } else if (c == '\n') {
            ; // no input - try again
        } else if (c != 'P' && c != 'A' && c != 'D' && c != 'V'
         && c != 'C' && c != 'Q') {
            is.ignore(2000, '\n');
            cerr << " Invalid Character.  Try again." << endl;
        } else if (is.get() != '\n') {
            is.ignore(2000, '\n');
            cerr << " Trailing Characters.  Try Again. " << endl;
        } else if (c == 'P' || c == 'A' || c == 'D' || c == 'V'
         || c == 'C' || c == 'Q')
            ok = true;
    } while (ok == 0);

    return c;
}

// style prompts for and accepts a character identifying the output style
// to be used and returns the character itself
//
char style(istream& is) {
    char cc;
    int c, ok = 0;

    do {
        cout << "Style Mark (enter ' ','-' or '') : ";
        c = is.get();
        cc = (char)c;
        if (is.fail()) {
            is.clear();
            is.ignore(2000, '\n');
            cerr << " Invalid input.  Try again." << endl;
        }
        else if (cc != ' ' && cc != '-' && cc != '\n') {
            is.ignore(2000, '\n');
            cerr << "Invalid character.  Try again." << endl;
        }
        else if ((cc == ' ' || cc == '-') && is.get() != '\n') {
            is.ignore(2000, '\n');
            cerr << "Trailing characters.  Try again." << endl;
        }
        else {
            ok = 1;
            if (cc == '\n') cc = '\0';
        }
    } while (ok == 0);

    return cc;
}
