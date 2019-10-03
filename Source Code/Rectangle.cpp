#include "Rectangle.h"
#include "Shape.h"

#include <iostream>

using namespace std;

Rectangle::Rectangle(vector<Point> points, bool containsWarpSpace, string name) : points(points), ShapeTwoD(containsWarpSpace, name)
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

vector<Point> Rectangle::getPoints() const { return this->points; }

string Rectangle::toString()
{
    string str = ShapeTwoD::toString();
    for (int i = 0; i < points.size(); i++)
    {
        str += points.at(i).toString(i);
    }
    str += Shape::addPointsToString("on perimeter", points_OnShape);
    str += Shape::addPointsToString("within shape", points_InShape);

    return str;
}

bool Rectangle::isPointInShape(int x, int y) { return Shape::isPointInShape(x, y, minX, maxX, minY, maxY); }
bool Rectangle::isPointOnShape(int x, int y) { return Shape::isPointOnShape(x, y, minX, maxX, minY, maxY); }

double Rectangle::computeArea() const { return ShapeTwoD::getArea(); }