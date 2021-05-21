//
// Created by ritaramada on 16/05/21.
//

#ifndef UNTITLED_UTILS_H
#define UNTITLED_UTILS_H

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

/**
 * @brief Get the integer input restricted to an inclusive interval.
 * @param lower lower limit of the interval.
 * @param upper upper limit of the interval.
 * @return integer contained in [lower, upper].
 */
int getInt(int lower, int upper);


/**
 * @brief Get Yes(Y/y) or No(N/n) from the user.
 * @return true (Yes).
 * @return false (No).
 */
bool getYesNo();

/**
 * @brief Clears the console
 *
 *
 */
void clear();

void printText( string text );




#endif //UNTITLED_UTILS_H
