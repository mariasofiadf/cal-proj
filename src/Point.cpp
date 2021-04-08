//
// Created by pedro on 08/04/21.
//

#include "Point.h"

Point::Point(double x, double y, string name) {
    Position position(x,y);
    this->position = position;
}

bool Point::operator==(const Point &rhs) const {
    return name == rhs.name;
}

ostream &operator<<(ostream &os, const Point &point) {
    os << "name: " << point.name;
    return os;
}

PointPark::PointPark(double x, double y, double price) : Point(x, y, std::string()), price(price) {}

PointTask::PointTask(double x, double y, const string &name) : Point(x, y, std::string()), name(name) {}

GasPoint::GasPoint(double x, double y, const string &name) : PointTask(x, y, name) {}

CoffePoint::CoffePoint(double x, double y, const string &name) : PointTask(x, y, name) {}

StorePoint::StorePoint(double x, double y, const string &name) : PointTask(x, y, name) {}
