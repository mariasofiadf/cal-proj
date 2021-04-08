//
// Created by pedro on 08/04/21.
//

#ifndef POSITION_H
#define POSITION_H

#include "math.h"

//A position consists of 2 coordinates that will be longitude and latitude
class Position {
    double x, y;
public:
    Position(double x, double y);
    double distance(Position &position);
    double getX() const;
    double getY() const;
};


#endif //POSITION_H
