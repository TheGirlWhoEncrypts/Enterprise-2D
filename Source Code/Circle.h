#ifndef CIRCLE_H
#define CIRCLE_H

#include "ShapeTwoD.h"
#include "Point.h"

class Circle : public ShapeTwoD
{
private:
  Point center;
  int radius;
  std::vector<Point> points_OnShape;
  std::vector<Point> points_InShape;

public:
  Circle(Point center, int radius = 0, bool containsWarpSpace = false, std::string name = "Circle");

  double getArea() const;
  void getPoints_OnShape();
  void getPoints_InShape();

  std::string toString();

  bool isPointInShape(int x, int y);
  bool isPointOnShape(int x, int y);

  double computeArea() const;

  void checkPoint(int x, int y, double &lhs, double &rhs);
};
#endif
