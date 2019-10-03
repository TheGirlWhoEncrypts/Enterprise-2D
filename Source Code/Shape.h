
#ifndef SHAPE_H
#define SHAPE_H

#include "Point.h"

#include <vector>

namespace Shape
{
std::string addPointsToString(std::string title, const std::vector<Point> &points);

int getMin(const int a, const int b);
int getMax(const int a, const int b);

void getMinMaxFor4SidedShape(const std::vector<Point> &points, int &minX, int &maxX, int &minY, int &maxY);

bool isPointInShape(const int x, const int y, const int &minX, const int &maxX, const int &minY, const int &maxY);
bool isPointOnShape(const int x, const int y, const int &minX, const int &maxX, const int &minY, const int &maxY);

void getPoints_OnShape(std::vector<Point> &points, const int &minX, const int &maxX, const int &minY, const int &maxY);
void getPoints_InShape(std::vector<Point> &points, const int &minX, const int &maxX, const int &minY, const int &maxY);

/* ----------------------------------------------------------------------------- */
void getPointsOnCross(const std::vector<Point> &points, std::vector<Point> &pointsOnCross);
void getAllCoordinatesOnBorder(const std::vector<Point> &points, std::vector<Point> &pointsOnCross, const int index_1, const int index_2);
void getCoordinateOnBorder(std::vector<Point> &pointsOnCross, const int min, const int max, const int coord, const bool isHorizontalCoordinate);

/* ----------------------------------------------------------------------------- */

void getPoly(float poly[], int size, const std::vector<Point> &points, bool isX);
bool pointInPolygon(int x, int y, float polyX[], float polyY[]);

bool isWithin_Or_On_Rectangle(int &minX, int &maxX, int &minY, int &maxY, Point point);

bool isPointOnCrossBorder(std::vector<Point> &pointsOnCross, Point point);
bool isGivenPoint(std::vector<Point> &points, Point point);
bool isPointWithinCross(int x, int y, Point point, std::vector<Point> &points, std::vector<Point> &pointsWithinCross, std::vector<Point> &pointsOnCross, int &minX, int &maxX, int &minY, int &maxY, float polyX[], float polyY[]);

void getPointsWithinCross(std::vector<Point> &points, std::vector<Point> &pointsWithinCross, std::vector<Point> &pointsOnCross, int &minX, int &maxX, int &minY, int &maxY, float polyX[], float polyY[]);
}

#endif