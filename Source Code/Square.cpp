#include "Square.h"
#include "Shape.h"

#include <iostream>

using namespace std;

Square::Square(vector<Point> points, bool containsWarpSpace, string name) : points(points), ShapeTwoD(containsWarpSpace, name)
{
    this->minX = 0;
    this->maxX = 0;
    this->minY = 0;
    this->maxY = 0;

    this->points_OnShape = {};
    this->points_InShape = {};

    Shape::getMinMaxFor4SidedShape(points, minX, maxX, minY, maxY);
    Shape::getPoints_OnShape(points_OnShape, minX, maxX, minY, maxY);
    Shape::getPoints_InShape(points_InShape, minX, maxX, minY, maxY);
}

vector<Point> Square::getPoints() const { return this->points; }

string Square::toString()
{
    string str = ShapeTwoD::toString();
    for (int i = 0; i < this->points.size(); i++)
    {
        str += this->points.at(i).toString(i);
    }
    str += Shape::addPointsToString("on perimeter", points_OnShape);
    str += Shape::addPointsToString("within shape", points_InShape);

    return str;
}

bool Square::isPointInShape(int x, int y) { return Shape::isPointInShape(x, y, minX, maxX, minY, maxY); }

bool Square::isPointOnShape(int x, int y) { return Shape::isPointOnShape(x, y, minX, maxX, minY, maxY); }

double Square::computeArea() const { return ShapeTwoD::getArea(); }