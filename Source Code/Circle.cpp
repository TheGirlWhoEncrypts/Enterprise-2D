#include "Circle.h"
#include "Shape.h"

#include <iostream>
#include <cmath>
using namespace std;

Circle::Circle(Point center, int radius, bool containsWarpSpace, string name) : center(center), ShapeTwoD(containsWarpSpace, name)
{
    this->radius = radius;

    this->points_OnShape = {};
    this->points_InShape = {};

    getPoints_OnShape();
    getPoints_InShape();
}

double Circle::getArea() const { return computeArea(); }

void Circle::getPoints_OnShape()
{
    Point north(center.getX(), center.getY() - radius);
    Point east(center.getX() + radius, center.getY());
    Point south(center.getX(), center.getY() + radius);
    Point west(center.getX() - radius, center.getY());
    points_OnShape = {north, east, south, west};
}

void Circle::getPoints_InShape()
{
    int startY = center.getY() - radius, endY = center.getY() + radius;
    int startX = center.getX() - radius, endX = center.getX() + radius;

    for (int i = startY; i <= endY; i++)
    {
        for (int j = startX; j <= endX; j++)
        {
            if (isPointInShape(j, i) && !(j == center.getX() && i == center.getY()))
            {
                Point point(j, i);
                points_InShape.push_back(point);
            }
        }
    }
}

string Circle::toString()
{
    string str = ShapeTwoD::toString();
    str += ShapeTwoD::formatAlignment("Area", to_string(getArea()), false);
    str += " units square\n";
    str += ShapeTwoD::formatAlignment("Radius (units)", to_string(radius));
    str += ShapeTwoD::formatAlignment("x-ordinate of center", to_string(center.getX()));
    str += ShapeTwoD::formatAlignment("y-ordinate of center", to_string(center.getY()));

    str += Shape::addPointsToString("on perimeter", points_OnShape);
    str += Shape::addPointsToString("within shape", points_InShape);
    return str;
}

bool Circle::isPointInShape(int x, int y)
{
    double lhs = 0.0, rhs = 0.0;
    checkPoint(x, y, lhs, rhs);
    return (lhs < rhs);
}

bool Circle::isPointOnShape(int x, int y)
{
    double lhs = 0.0, rhs = 0.0;
    checkPoint(x, y, lhs, rhs);
    return (lhs == rhs);
}

void Circle::checkPoint(int x, int y, double &lhs, double &rhs)
{
    lhs = pow((x - center.getX()), 2) + pow((y - center.getY()), 2); // Distance ^ 2
    rhs = pow(radius, 2);                                            // Radius ^ 2
}

double Circle::computeArea() const { return M_PI * pow(radius, 2); }