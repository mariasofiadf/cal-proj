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
    PointTask(double x, double y, const string &name);
};

class PointGas : public PointTask{
public:
    PointGas(double x, double y, const string &name);
};

class PointCoffe : public PointTask{
public:
    PointCoffe(double x, double y, const string &name);
};

class StorePoint : public PointTask{
public:
    StorePoint(double x, double y, const string &name);
};


#endif //POINT_H
