#ifndef SHAPE_TWO_D_H
#define SHAPE_TWO_D_H

#include "Point.h"

#include <vector>
#include <string>

class ShapeTwoD
{
private:
  double area;
  static int ShapeTwoD_Counter;
  int ShapeTwoD_ID;

protected:
  bool containsWarpSpace;
  std::string name;

public:
  ShapeTwoD(bool containsWarpSpace = false, std::string name = "");

  bool getContainsWarpSpace() const;
  std::string getName() const;
  std::string getShapeTwoD_ID();
  virtual double getArea() const;
  virtual std::vector<Point> getPoints() const;

  void setContainsWarpSpace(bool containsWarpSpace);
  void setName(std::string name);
  void setArea(double area);

  virtual std::string toString();

  virtual bool isPointInShape(int x, int y);
  virtual bool isPointOnShape(int x, int y);

  virtual double computeArea() const;

  std::string formatAlignment(std::string title, std::string details, bool isNewLine = true);
};

#endif