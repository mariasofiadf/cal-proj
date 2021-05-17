//
// Created by ritaramada on 16/05/21.
//
#include <iostream>
#include "utils.h"

using namespace std;
int getInt(int lower, int upper) // Inclusive
{
    int choice;
    while (!(cin >> choice) || choice < lower || choice > upper) {
        cout << "Invalid Input: ";
        cin.clear();
        cin.ignore(1000000, '\n');
    }
    cin.ignore(1000000, '\n');
    return choice;
}

void clear()
{
    cout << "\x1B[2J\x1B[H";
}

bool getYesNo()
{
    char choice;
    while(!(cin >> choice) || (toupper(choice) != 'Y' && toupper(choice) != 'N')){
        cout << "Invalid Input! Try again... ";
        cin.clear();
        cin.ignore(1000000, '\n');
    }
    cin.ignore(1000000, '\n');
    return (toupper(choice) == 'Y');
}


