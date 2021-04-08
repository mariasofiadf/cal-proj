//
// Created by pedro on 08/04/21.
//

#ifndef POINT_H
#define POINT_H

#include "Position.h"

class Point {
    Position position = Position(0, 0);
public:
    Point(const Position &position);
    Point(double x, double y);

};


#endif //POINT_H
