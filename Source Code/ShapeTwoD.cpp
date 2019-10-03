#include "ShapeTwoD.h"

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

using namespace std;

int ShapeTwoD::ShapeTwoD_Counter = -1;

ShapeTwoD::ShapeTwoD(bool containsWarpSpace, string name)
{
    this->containsWarpSpace = containsWarpSpace;
    this->name = name;

    this->area = 0.0;
    this->ShapeTwoD_ID = ++ShapeTwoD_Counter;
}

bool ShapeTwoD::getContainsWarpSpace() const { return containsWarpSpace; }
string ShapeTwoD::getName() const { return name; }
string ShapeTwoD::getShapeTwoD_ID()
{
    ostringstream os;
    os << "Shape [" << ShapeTwoD_ID << "]" << endl;
    return os.str();
}
double ShapeTwoD::getArea() const { return this->area; }
std::vector<Point> ShapeTwoD::getPoints() const { return vector<Point>(); }

void ShapeTwoD::setArea(double area) { this->area = area; }
void ShapeTwoD::setContainsWarpSpace(bool containsWarpSpace) { this->containsWarpSpace = containsWarpSpace; }
void ShapeTwoD::setName(string name) { this->name = name; }

string ShapeTwoD::toString()
{
    string str = getShapeTwoD_ID();
    str += formatAlignment("Name", name);
    str += formatAlignment("Special Type", (containsWarpSpace) ? "WS" : "NS");

    if (this->name.compare("Circle") != 0)
    {
        str += ShapeTwoD::formatAlignment("Area", to_string((int)computeArea()), false);
        str += " units square\n";
        str += ShapeTwoD::formatAlignment("Vertices", "");
    }
    return str;
}
double ShapeTwoD::computeArea() const { return getArea(); }

bool ShapeTwoD::isPointInShape(int x, int y) { return false; }
bool ShapeTwoD::isPointOnShape(int x, int y) { return false; }

string ShapeTwoD::formatAlignment(string title, string details, bool isNewLine)
{
    ostringstream os;
    os << left << setw(15) << title << " : " << details;
    os << ((isNewLine) ? "\n" : "");
    return os.str();
}
