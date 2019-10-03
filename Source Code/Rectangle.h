#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "ShapeTwoD.h"
#include "Point.h"

#include <vector>

class Rectangle : public ShapeTwoD
{
private:
  std::vector<Point> points;

  int minX, maxX, minY, maxY;

  std::vector<Point> points_OnShape;
  std::vector<Point> points_InShape;

public:
  Rectangle(std::vector<Point> points, bool containsWarpSpace = false, std::string name = "Rectangle");

  std::vector<Point> getPoints() const;

  std::string toString();

  bool isPointInShape(int x, int y);
  bool isPointOnShape(int x, int y);

  double computeArea() const;
};
#endif
