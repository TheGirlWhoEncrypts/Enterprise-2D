#ifndef POINT_H
#define POINT_H

#include <string>

class Point
{
  private:
    int x, y;

  public:
    Point(int x = 0, int y = 0);

    // Getters
    int getX() const;
    int getY() const;
    std::string getXY() const;

    // Setters
    void setX(int x);
    void setY(int y);

    // Methods
    std::string toString(const int index) const;
    bool operator==(const Point &rhs) const;
};

#endif