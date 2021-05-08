//
// Created by pedro on 08/04/21.
//

#include "Point.h"


Point::Point(double x, double y, int id) {
    Position position(x,y);
    this->id = id;
    this->position = position;
}

bool Point::operator==(const Point &rhs) const {
    return id == rhs.id;
}

ostream &operator<<(ostream &os, const Point &point) {
    os << point.id;
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

int Point::getId() const {
    return id;
}

void Point::setId(int id) {
    Point::id = id;
}


PointPark::PointPark(double x, double y, const int id, double price) : Point(x, y, id), price(price) {
    this->pointType = PARK;
}


PointTask::PointTask(double x, double y, const int id) : Point(x, y, id) {

}

PointGas::PointGas(double x, double y, const int id) : PointTask(x, y, id) {
    this->pointType = GAS;
}


PointCoffe::PointCoffe(double x, double y, const int id) : PointTask(x, y, id) {
    this->pointType = COFFE;
}


PointStore::PointStore(double x, double y, const int id) : PointTask(x, y, id) {
    this->pointType = STORE;
}
