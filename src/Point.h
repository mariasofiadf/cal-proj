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
/** class Point
 *
 * @brief
 * A point can be of different Types:
 * PointPark
 * PointTask
 * PointGas
 * PointCoffe
 * PointStore
 *
 */
class Point {
protected:
    enum pointType pointType = POINT;
    /** @brief name is unique and is used in == operator
     *
     */
    string name;
    int id;
    Position position = Position(0, 0);
public:
    Point(int id, double x, double y);

    const string &getName() const;

    Position &getPosition();

    int getId() const;

    void setId(int id);

    /**
     * @brief Compares name attribute
     * @param rhs
     * @return true if Points have the same name
     */
    bool operator==(const Point &rhs) const;

    /**
     * @brief Outputs Point name
     * @param os
     * @param point
     * @return Point name
     */
    friend ostream &operator<<(ostream &os, const Point &point);

    enum pointType getPointType() const;

};

/** class PointPark
 *
 * @brief Child of Point
 *
 */
class PointPark : public Point{
private:
    static int numParks;
    double price;
public:
    PointPark(const int id, double x, double y, double price);
    enum pointType getType();
};

/** class PointTask
 *
 * @brief Child of Point
 *
 */
class PointTask : public Point{
public:
    PointTask(const int id, double x, double y);
};

/** class PointGas
 *
 * @brief Child of PointTask
 *
 */
class PointGas : public PointTask{
public:
    PointGas(const int id, double x, double y);
    enum pointType getType();
};

/** class PointCoffe
 *
 * @brief Child of PointTask
 *
 */
class PointCoffe : public PointTask{
public:
    PointCoffe( const int id, double x, double y);
    enum pointType getType();
};

/** class PointStore
 *
 * @brief Child of PointTask
 *
 */
class PointStore : public PointTask{
public:
    PointStore(const int id, double x, double y);
    enum pointType getType();

};


#endif //POINT_H
