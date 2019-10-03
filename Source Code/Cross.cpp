#include "Cross.h"
#include "Shape.h"

#include <iostream>

using namespace std;

Cross::Cross(vector<Point> points, bool containsWarpSpace, string name) : points(points), ShapeTwoD(containsWarpSpace, name)
{
    this->minX = 0;
    this->maxX = 0;
    this->minY = 0;
    this->maxY = 0;

    this->points_OnShape = {};
    this->points_InShape = {};

    Shape::getPoly(polyX, 12, points, true);
    Shape::getPoly(polyY, 12, points, false);

    Shape::getMinMaxFor4SidedShape(points, minX, maxX, minY, maxY);
    Shape::getPointsOnCross(points, points_OnShape);

    Shape::getPointsWithinCross(points, points_InShape, points_OnShape, minX, maxX, minY, maxY, polyX, polyY);
}

vector<Point> Cross::getPoints() const { return this->points; }

string Cross::toString()
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

bool Cross::isPointInShape(int x, int y)
{
    Point point(x, y);
    return Shape::isPointWithinCross(x, y, point, points, points_InShape, points_OnShape, minX, maxX, minY, maxY, polyX, polyY);
}

bool Cross::isPointOnShape(int x, int y)
{
    Point point(x, y);
    return Shape::isPointOnCrossBorder(points_OnShape, point);
}

double Cross::computeArea() const { return ShapeTwoD::getArea(); }