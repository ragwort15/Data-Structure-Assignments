#include "Shapes.h"


double Circle::area() const {
    return M_PI * this->radius * this->radius;
}

// using co-ordinate geometry(determinant formula)
double Triangle::area() const {
    return fabs(
        (this->p1.getX() * (this->p2.getY() - this->p3.getY()) +
         this->p2.getX() * (this->p3.getY() - this->p1.getY()) +
         this->p3.getX() * (this->p1.getY() - this->p2.getY())) / 2.0
    );
}

//used the same formula as triangle: 1 Rectangle == 2 identical area triangles
double Rectangle::area() const {
    return fabs(
        (this->p1.getX() * (this->p2.getY() - this->p3.getY()) +
         this->p2.getX() * (this->p3.getY() - this->p1.getY()) +
         this->p3.getX() * (this->p1.getY() - this->p2.getY())) 
    );
}

bool compareShapes(Shape* a, Shape* b) {
    return a->area() < b->area();
}

void ShapeSorter(vector<Shape*> &shapes) {
    sort(shapes.begin(), shapes.end(), compareShapes);
}
