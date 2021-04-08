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

enum pointType{
    POINT, PARK, GAS, COFFE, STORE
};

class Point {
protected:
    enum pointType pointType = POINT;
    string name;
    Position position = Position(0, 0);
public:
    Point(double x, double y, string name);

    const string &getName() const;

    Position &getPosition();

    bool operator==(const Point &rhs) const;

    friend ostream &operator<<(ostream &os, const Point &point);

    enum pointType getPointType() const;

};


class PointPark : public Point{
private:
    static int numParks;
    double price;
public:
    PointPark(double x, double y, const string &name, double price);
    enum pointType getType();
};


class PointTask : public Point{
public:
    PointTask(double x, double y, const string &name);
};

class PointGas : public PointTask{
public:
    PointGas(double x, double y, const string &name);
    enum pointType getType();
};

class PointCoffe : public PointTask{
public:
    PointCoffe(double x, double y, const string &name);
    enum pointType getType();
};

class PointStore : public PointTask{
public:
    PointStore(double x, double y, const string &name);
    enum pointType getType();
};


#endif //POINT_H
