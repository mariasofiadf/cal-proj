//
// Created by pedro on 08/04/21.
//

#ifndef POINT_H
#define POINT_H

#include <ostream>
#include "Position.h"
#include "string"
#include<string.h>
#include <iostream>

using namespace std;

class Point {
protected:
    string name;
    Position position = Position(0, 0);
public:
    Point(double x, double y, string name);

    const string &getName() const;

    bool operator==(const Point &rhs) const;

    friend ostream &operator<<(ostream &os, const Point &point);

};


class PointPark : public Point{
private:
    static int numParks;
    double price;
public:
    PointPark(double x, double y, const string &name, double price);
};


class PointTask : public Point{
public:
};

class GasPoint : public PointTask{
public:
};

class CoffePoint : public PointTask{
public:
};

class StorePoint : public PointTask{
public:
};


#endif //POINT_H
