//
// Created by pedro on 08/04/21.
//

#include "Position.h"

Position::Position(double x, double y) : x(x), y(y) {}

double Position::distance(Position &position) {
    return sqrt(pow(abs(this->getX() - position.getX()), 2) + pow(abs(this->getY() - position.getY()), 2));
}

double Position::getX() const {
    return x;
}

double Position::getY() const {
    return y;
}

bool Position::operator==(const Position &rhs) const {
    return x == rhs.x &&
           y == rhs.y;
}

bool Position::operator!=(const Position &rhs) const {
    return !(rhs == *this);
}
