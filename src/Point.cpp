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
    os << point.name;
    return os;
}

const string &Point::getName() const {
    return name;
}

Position &Point::getPosition(){
    return position;
}

enum pointType Point::getPointType() const {
    return pointType;
}


PointPark::PointPark(double x, double y, const string &name, double price) : Point(x, y, name), price(price) {
    this->pointType = PARK;
}


PointTask::PointTask(double x, double y, const string &name) : Point(x, y, name) {

}

PointGas::PointGas(double x, double y, const string &name) : PointTask(x, y, name) {
    this->pointType = GAS;
}


PointCoffe::PointCoffe(double x, double y, const string &name) : PointTask(x, y, name) {
    this->pointType = COFFE;
}


PointStore::PointStore(double x, double y, const string &name) : PointTask(x, y, name) {
    this->pointType = STORE;
}
