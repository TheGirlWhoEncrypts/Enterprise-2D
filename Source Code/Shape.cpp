#include "Shape.h"
#include "Point.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

string Shape::addPointsToString(string title, const vector<Point> &points)
{
    ostringstream os;
    os << "\nPoints " << title << " : ";
    for (int i = 0; i < points.size(); i++)
    {
        os << points.at(i).getXY();
        os << ((i < points.size() - 1) ? ", " : "\n");
    }
    return os.str();
}

int Shape::getMin(const int a, const int b) { return (a < b) ? a : b; }
int Shape::getMax(const int a, const int b) { return (a > b) ? a : b; }

void Shape::getMinMaxFor4SidedShape(const vector<Point> &points, int &minX, int &maxX, int &minY, int &maxY)
{
    minX = points.at(0).getX();
    maxX = points.at(0).getX();
    minY = points.at(0).getY();
    maxY = points.at(0).getY();

    for (int i = 1; i < points.size(); i++)
    {
        minX = getMin(points.at(i).getX(), minX);
        maxX = getMax(points.at(i).getX(), maxX);
        minY = getMin(points.at(i).getY(), minY);
        maxY = getMax(points.at(i).getY(), maxY);
    }
}

bool Shape::isPointInShape(const int x, const int y, const int &minX, const int &maxX, const int &minY, const int &maxY)
{
    return ((x > minX && x < maxX) && (y > minY && y < maxY));
}

bool Shape::isPointOnShape(const int x, const int y, const int &minX, const int &maxX, const int &minY, const int &maxY)
{
    return (((x > minX && x < maxX) && (y == minY || y == maxY)) ||
            ((y > minY && y < maxY) && (x == minX || x == maxX)));
}

void Shape::getPoints_OnShape(vector<Point> &points, const int &minX, const int &maxX, const int &minY, const int &maxY)
{
    for (int i = minY; i <= maxY; i++)
    {
        for (int j = minX; j <= maxX; j++)
        {
            if (isPointOnShape(j, i, minX, maxX, minY, maxY))
            {
                Point point(j, i);
                points.push_back(point);
            }
        }
    }
}

void Shape::getPoints_InShape(vector<Point> &points, const int &minX, const int &maxX, const int &minY, const int &maxY)
{
    for (int i = minY; i <= maxY; i++)
    {
        for (int j = minX; j <= maxX; j++)
        {
            if (isPointInShape(j, i, minX, maxX, minY, maxY))
            {
                Point point(j, i);
                points.push_back(point);
            }
        }
    }
}

/* ----------------------------------------------------------------------------- */

void Shape::getPointsOnCross(const vector<Point> &points, vector<Point> &pointsOnCross)
{
    for (int i = 0; i < points.size(); i++)
    {
        (i == points.size() - 1) ? getAllCoordinatesOnBorder(points, pointsOnCross, 0, points.size() - 1)
                                 : getAllCoordinatesOnBorder(points, pointsOnCross, i, (i + 1));
    }
}

void Shape::getAllCoordinatesOnBorder(const vector<Point> &points, vector<Point> &pointsOnCross, const int index_1, const int index_2)
{
    int min_X = getMin(points.at(index_1).getX(), points.at(index_2).getX());
    int max_X = getMax(points.at(index_1).getX(), points.at(index_2).getX());
    int min_Y = getMin(points.at(index_1).getY(), points.at(index_2).getY());
    int max_Y = getMax(points.at(index_1).getY(), points.at(index_2).getY());

    int xDiff = max_X - min_X;
    int yDiff = max_Y - min_Y;

    // Horizontal Coordinate
    if ((min_Y == max_Y) && xDiff > 1)
    {
        getCoordinateOnBorder(pointsOnCross, min_X, max_X, min_Y, true);
    }

    // Vertical Coordinate
    if ((min_X == max_X) && yDiff > 1)
    {
        getCoordinateOnBorder(pointsOnCross, min_Y, max_Y, min_X, false);
    }
}

void Shape::getCoordinateOnBorder(vector<Point> &pointsOnCross, const int min, const int max, const int coord, const bool isHorizontalCoordinate)
{
    for (int i = min + 1; i < max; i++)
    {
        Point point = (isHorizontalCoordinate) ? Point(i, coord) : Point(coord, i);
        pointsOnCross.push_back(point);
    }
}

/* ----------------------------------------------------------------------------- */

void Shape::getPoly(float poly[], int size, const vector<Point> &points, bool isX)
{
    for (int i = 0; i < points.size(); i++)
    {
        poly[i] = (isX) ? (float)points.at(i).getX() : (float)points.at(i).getY();
    }
}

bool Shape::pointInPolygon(int x, int y, float polyX[], float polyY[])
{
    int polyCorners = 12;
    int i, j = polyCorners - 1;
    bool oddNodes = false;

    for (i = 0; i < polyCorners; i++)
    {

        if (((polyY[i] < y && polyY[j] >= y) || (polyY[j] < y && polyY[i] >= y)) && (polyX[i] <= x || polyX[j] <= x))
        {
            oddNodes ^= (polyX[i] + (y - polyY[i]) / (polyY[j] - polyY[i]) * (polyX[j] - polyX[i]) < x);
        }

        j = i;
    }

    return oddNodes;
}

bool Shape::isWithin_Or_On_Rectangle(int &minX, int &maxX, int &minY, int &maxY, Point point)
{
    return ((point.getX() >= minX && point.getX() <= maxX) && (point.getY() >= minY && point.getY() <= maxY));
}

bool Shape::isPointOnCrossBorder(vector<Point> &pointsOnCross, Point point)
{
    vector<Point>::iterator it = find(pointsOnCross.begin(), pointsOnCross.end(), point);
    return (it != pointsOnCross.end()) ? true : false;
}

bool Shape::isGivenPoint(vector<Point> &points, Point point)
{
    vector<Point>::iterator it = find(points.begin(), points.end(), point);
    return (it != points.end()) ? true : false;
}

bool Shape::isPointWithinCross(int x, int y, Point point, vector<Point> &points, vector<Point> &pointsWithinCross, vector<Point> &pointsOnCross, int &minX, int &maxX, int &minY, int &maxY, float polyX[], float polyY[])
{
    return (isWithin_Or_On_Rectangle(minX, maxX, minY, maxY, point) && !isPointOnCrossBorder(pointsOnCross, point) && !isGivenPoint(points, point) && pointInPolygon(x, y, polyX, polyY));
}

void Shape::getPointsWithinCross(vector<Point> &points, vector<Point> &pointsWithinCross, vector<Point> &pointsOnCross, int &minX, int &maxX, int &minY, int &maxY, float polyX[], float polyY[])
{
    for (int i = minY; i <= maxY; i++)
    {
        for (int j = minX; j <= maxX; j++)
        {
            Point point(j, i);
            if (isPointWithinCross(j, i, point, points, pointsWithinCross, pointsOnCross, minX, maxX, minY, maxY, polyX, polyY))
            {
                pointsWithinCross.push_back(point);
            }
        }
    }
}