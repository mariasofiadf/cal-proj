//
// Created by pedro on 08/04/21.
//

#include "Point.h"

Point::Point(const Position &position) : position(position) {}

Point::Point(double x, double y) {
    Position position(x,y);
    this->position = position;
}
