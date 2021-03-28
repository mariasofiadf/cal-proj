//
// Created by pedro on 28/03/21.
//

#ifndef CAL_TP_CLASSES_PRINTER_H
#define CAL_TP_CLASSES_PRINTER_H

#include <iostream>
#include <string>

using namespace std;

class Printer {
    std::string string;
public:
    Printer(const std::string &string) : string(string) {}
    std::string print(){
        return string;
    }
};


#endif //CAL_TP_CLASSES_PRINTER_H
