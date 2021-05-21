//
// Created by pedro on 08/04/21.
//

#include <sys/time.h>
#include <unistd.h>
#include "Point.h"


Point::Point( int id, double x, double y) {
    Position position(x,y);
    this->id = id;
    this->position = position;
}

bool Point::operator==(const Point &rhs) const {
    return id == rhs.id;
}

bool Point::operator!=(const Point &rhs) const {
    return id != rhs.id;
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

unsigned int hash3(unsigned int h1, unsigned int h2, unsigned int h3)
{
    return (h1 * 2654435789U + h2) * 2654435789U + h3;
}

PointPark::PointPark( const int id, double x, double y) : Point(id, x, y){
    this->pointType = PARK;
    struct timeval time;
    gettimeofday(&time, NULL);
    srand(hash3(time.tv_sec, time.tv_usec, getpid()));

    this->priceRate =  rand() % 15 + 50; //entre 50 e 65 centimos
    this->fixPrice = rand() % 100 + 50; // entre 50 e 150 centimos
}

double PointPark::getPricePaid(int time) {
    return priceRate * time + fixPrice;
}


PointTask::PointTask(const int id, double x, double y) : Point(id, x, y) {

}

PointGas::PointGas(const int id, double x, double y) : PointTask(id, x, y) {
    this->pointType = GAS;
}


PointCoffe::PointCoffe(const int id, double x, double y) : PointTask(id, x, y) {
    this->pointType = COFFE;
}


PointStore::PointStore(const int id, double x, double y) : PointTask(id, x, y) {
    this->pointType = STORE;
}
