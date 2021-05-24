//
// Created by ritaramada on 16/05/21.
//
#include <iostream>
#include "utils.h"

using namespace std;

void printText( string text ) {
    cout << std::setfill( '*' ) << setw( 40 ) << '*' <<  endl;
    cout << '*' << left << setfill(' ' )<< setw( 40 - 2 ) << text<< setw( 40 - 2 )<< " *"<< endl;
    cout << setfill( '*') << setw( 40 ) << '*' <<  endl;
}

int getInt(int lower, int upper) // Inclusive
{
    int choice;
    while (!(cin >> choice) || choice < lower || choice > upper) {
        cout << "Input inválido!\n";
        cin.clear();
        cin.ignore(1000000, '\n');
    }
    cin.ignore(1000000, '\n');
    return choice;
}

int getID(Graph * g){
    int id;
    while (!(cin >> id) || g->findVertex(Point(id,0,0)) == nullptr) {
        cout << "Não existe nenhum ponto com esse ID\n";
        cin.clear();
        cin.ignore(1000000, '\n');
    }
    cin.ignore(1000000, '\n');
    return id;
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


