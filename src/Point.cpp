//
// Created by pedro on 08/04/21.
//

#include "Point.h"


Point::Point(double x, double y, string name) {
    Position position(x,y);
    this->name = name;
    this->position = position;
}

bool Point::operator==(const Point &rhs) const {
    return name == rhs.name;
}

ostream &operator<<(ostream &os, const Point &point) {
    os << "name: " << point.name;
    return os;
}

const string &Point::getName() const {
    return name;
}

PointPark::PointPark(double x, double y, const string &name, double price) : Point(x, y, name), price(price) {}
