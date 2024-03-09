// File: task2.cpp
// Purpose: BIGCLASS
// Author: ahmed mohamed tolba
// Section: S7,8
// ID: 20220033
// TA: khaled ibrahem
// Date: 5 NOV 2023

#ifndef BIGREAL_H
#define BIGREAL_H

#include <iostream>
#include <deque>
using namespace std;

bool isValid(string s);

class BigReal
{
private:
    deque<int> integer;
    deque<int> fraction;
    bool postive = true;                                   // if the number is positive #true
    bool decimal = false;                                  // if the number have fraction side #true
public:
    BigReal();                                             // default 0.0 positive and decimal
    BigReal(string num);                                   // is valid
    void operator=(string num);                            // is valid
    BigReal operator+(BigReal &n);
    BigReal operator+(string n);                           // is valid
    BigReal operator-(BigReal &n);                         // is valid
    bool operator<(BigReal n);                             // is valid
    bool operator>(BigReal n);                             // is valid
    bool operator==(BigReal n);                            // is valid
    friend ostream &operator<<(ostream &out, BigReal num); // is valid
};

#endif