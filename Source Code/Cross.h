#ifndef CROSS_H
#define CROSS_H

#include "ShapeTwoD.h"
#include "Point.h"

#include <vector>
class Cross : public ShapeTwoD
{
private:
  std::vector<Point> points;

  int minX, maxX, minY, maxY;

  float polyX[12], polyY[12];

  std::vector<Point> points_OnShape;
  std::vector<Point> points_InShape;

public:
  Cross(std::vector<Point> points, bool containsWarpSpace = false, std::string name = "Cross");

  std::vector<Point> getPoints() const;

  std::string toString();

  bool isPointInShape(int x, int y);
  bool isPointOnShape(int x, int y);

  double computeArea() const;
};
#endif
