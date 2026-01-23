#include "XYPoint.h"

XYPoint::XYPoint() {
    this->x = 0.0;
    this->y = 0.0;
}

XYPoint::XYPoint(double x, double y) {
    this->x = x;
    this->y = y;
}

double XYPoint::getX() const {
    return x;
}

double XYPoint::getY() const {
    return y;
}

void XYPoint::setX(double x) {
    this->x = x;
}

void XYPoint::setY(double y) {
    this->y = y;
}
