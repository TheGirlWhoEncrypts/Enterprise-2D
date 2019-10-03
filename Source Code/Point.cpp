#include "Point.h"

#include <string>
#include <sstream>

using namespace std;

Point::Point(int x, int y)
{
    this->x = x;
    this->y = y;
}

int Point::getX() const { return x; }
int Point::getY() const { return y; }
string Point::getXY() const
{
    ostringstream os;
    os << "(" << x << ", " << y << ")";
    return os.str();
}

void Point::setX(int x) { this->x = x; }
void Point::setY(int y) { this->y = y; }

string Point::toString(const int index) const
{
    ostringstream os;
    os << "Point [" << index << "] : " << getXY() << endl;
    return os.str();
}

bool Point::operator==(const Point &rhs) const
{
    return this->x == rhs.x && this->y == rhs.y;
}
