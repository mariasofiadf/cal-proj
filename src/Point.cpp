//
// Created by pedro on 08/04/21.
//

#include "Point.h"

Point::Point(double x, double y) {
    Position position(x,y);
    this->position = position;
}

PointPark::PointPark(double x, double y, double price) : Point(x, y), price(price) {}

PointTask::PointTask(double x, double y, const string &name) : Point(x, y), name(name) {}

GasPoint::GasPoint(double x, double y, const string &name) : PointTask(x, y, name) {}

CoffePoint::CoffePoint(double x, double y, const string &name) : PointTask(x, y, name) {}

StorePoint::StorePoint(double x, double y, const string &name) : PointTask(x, y, name) {}
