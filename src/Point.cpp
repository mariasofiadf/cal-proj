//
// Created by pedro on 08/04/21.
//

#include "Point.h"


Point::Point( int id, double x, double y) {
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


PointPark::PointPark( const int id, double x, double y, double price) : Point(x, y, id), price(price) {
    this->pointType = PARK;
}


PointTask::PointTask(const int id, double x, double y) : Point(x, y, id) {

}

PointGas::PointGas(const int id, double x, double y) : PointTask(x, y, id) {
    this->pointType = GAS;
}


PointCoffe::PointCoffe(const int id, double x, double y) : PointTask(x, y, id) {
    this->pointType = COFFE;
}


PointStore::PointStore(const int id, double x, double y) : PointTask(x, y, id) {
    this->pointType = STORE;
}
