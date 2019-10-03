#ifndef SQUARE_H
#define SQUARE_H

#include "ShapeTwoD.h"
#include "Point.h"

#include <vector>
class Square : public ShapeTwoD
{
private:
  std::vector<Point> points;

  int minX, maxX, minY, maxY;

  std::vector<Point> points_OnShape;
  std::vector<Point> points_InShape;

public:
  Square(std::vector<Point> points, bool containsWarpSpace = false, std::string name = "Square");

  std::vector<Point> getPoints() const;

  std::string toString();

  bool isPointInShape(int x, int y);
  bool isPointOnShape(int x, int y);

  double computeArea() const;
};
#endif
