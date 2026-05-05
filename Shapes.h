#ifndef SHAPES_H
#define SHAPES_H

#include <vector>
#include <algorithm>
#include <cmath>
#include <vector>
#include "XYPoint.h"

using namespace std;

class XYPoint; 

class Shape {
public:
    virtual double area() const = 0; // pure virtual function
    virtual ~Shape() {}
};

class Circle : public Shape {
private:
    XYPoint center;
    double radius;
public:
    Circle(const XYPoint &c, double r) {
        this->center = c;
        this->radius = r;
    }
    double area() const override;
};

class Triangle : public Shape {
private:
    XYPoint p1, p2, p3;
public:
    Triangle(const XYPoint &a, const XYPoint &b, const XYPoint &c) {
        this->p1 = a;
        this->p2 = b;
        this->p3 = c;
    }
    double area() const override;
};

class Rectangle : public Shape {
private:
    XYPoint p1, p2, p3, p4;
public:
    Rectangle(const XYPoint &a, const XYPoint &b,
              const XYPoint &c, const XYPoint &d) {
        this->p1 = a;
        this->p2 = b;
        this->p3 = c;
        this->p4 = d;
    }
    double area() const override;
};

void ShapeSorter(vector<Shape*> &shapes);

#endif
