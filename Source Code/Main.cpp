// g++ -std=c++11 Main.cpp Rectangle.cpp Cross.cpp Square.cpp Circle.cpp Point.cpp ShapeTwoD.cpp Shape.cpp -o main.exe

#include "Cross.h"
#include "Rectangle.h"
#include "Square.h"
#include "Circle.h"
#include "Point.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

/* ------------------------------------ Global Constant Variables ------------------------------------ */
const string DIVIDER = "-----------------------------------------------------------\n";
const string STUDENT_INFORMATION[4] = {
    "Student ID", ": 123456", "Stduent Name", ": Jane Doe"};

const string OPTIONS[] = {
    "1)", "Input sensor data",
    "2)", "Compute area (for all records)",
    "3)", "Print shapes report",
    "4)", "Sort shape data",
    "5)", "Quit\n"};

const string PLEASE_ENTER = "Please enter ";

const string VALID_SHAPES_NAMES[4] = {"CROSS", "RECTANGLE", "SQUARE", "CIRCLE"};
const string VALID_SPECIAL_TYPES[2] = {"WS", "NS"};

const string SORT_OPTIONS[]{
    "a)", "Sort by area (ascending)",
    "b)", "Sort by area (descending)",
    "c)", "Sort by special type and area"};

ShapeTwoD *shape2DArray[100];
int shape2D_index = 0;
/* --------------------------------------- Function Definitions --------------------------------------- */
// Main()
void execute2DShapesProgram();

void printMainMenu();
void printStringArray(const string arrayName[], int size, int width);
void setWidth(string str, int width);

int getUserChoiceInput();
bool integerValidation(int userInput, int min, int max);
void clearInputBuffer();
void printErrorMessage();

void printOption(int userChoiceInput);

void processUserChoiceInput(int userChoiceInput, bool &isQuit);
void executeUserChoiceInput(int choiceNumber);

// Input Sensor Data
void inputSensorData();
string getShapeInput(string question, const string validStrings[], int size);
bool stringValidation(string &userInput, const string validStrings[], int size);
void getPoints(vector<Point> &points, const int noOfTimes);
void deallocateShape2DArray();

// Calculate Area
void calculateArea();
double shoelace(const vector<Point> &points);

// Print Shapes Report
void printShapesReport();

// Sort Shape Data
void sortShapeData();
char getUserSortChoiceInput();
bool charValidation(string userInput, char min, char max);
void processUser_SortChoiceInput(char sortChoiceInput, bool &isQuit);

bool sortByAreaAscending(const ShapeTwoD *lhs, const ShapeTwoD *rhs);
bool sortByAreaDescending(const ShapeTwoD *lhs, const ShapeTwoD *rhs);
bool sortBySpecialType_Area(const ShapeTwoD *lhs, const ShapeTwoD *rhs);
void executeUser_SortChoiceInput(char choiceNumber);
/* ---------------------------------------- Main() -------------------------------------------------- */

int main()
{

    execute2DShapesProgram();
    deallocateShape2DArray();
}
/* ------------------------------------------------------------------------------------- */
void execute2DShapesProgram()
{
    bool isQuit = false;
    do
    {
        printMainMenu();
        int userChoiceInput = getUserChoiceInput();
        printOption(userChoiceInput);
        processUserChoiceInput(userChoiceInput, isQuit);

    } while (!isQuit);
}

void printMainMenu()
{
    printStringArray(STUDENT_INFORMATION, 4, 15);
    cout << DIVIDER << "Welcome to Assn2 program!"
         << endl;
    printStringArray(OPTIONS, sizeof(OPTIONS) / sizeof(string), 7);
}

void printStringArray(const string arrayName[], int size, int width)
{
    for (int i = 0; i < size; i++)
    {
        if (i % 2 == 0)
        {
            setWidth(arrayName[i], width);
        }
        else
        {
            cout << arrayName[i] << endl;
        }
    }
}

void setWidth(string str, int width)
{
    cout << left << setw(width) << str;
}

int getUserChoiceInput()
{
    int validatedInput = -1, userInput;
    bool isInteger = false;
    do
    {
        cout << PLEASE_ENTER << "your choice : ";
        cin >> userInput;
        isInteger = integerValidation(userInput, 1, 5);
    } while (!isInteger);

    validatedInput = userInput;
    return validatedInput;
}

bool integerValidation(int userInput, int min, int max)
{
    bool isInteger = false;

    if (!isdigit(userInput) && !(userInput >= min && userInput <= max))
    {
        clearInputBuffer();
        printErrorMessage();
    }
    else
    {
        isInteger = true;
    }
    return isInteger;
}

void clearInputBuffer()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void printErrorMessage()
{
    cerr << "ERROR : Invalid Input\n"
         << endl;
}

void printOption(int userChoiceInput)
{
    cout << "\n[" << OPTIONS[(userChoiceInput * 2) - 1] << "]" << endl;
    if (userChoiceInput != 1)
    {
        cout << "\n";
    }
}

void processUserChoiceInput(int userChoiceInput, bool &isQuit)
{
    if (userChoiceInput == 5)
    {
        isQuit = true;
    }
    else
    {
        executeUserChoiceInput(userChoiceInput);
    }
}

void executeUserChoiceInput(int choiceNumber)
{
    switch (choiceNumber)
    {
    case 1:
        inputSensorData();
        break;
    case 2:
        calculateArea();
        break;
    case 3:
        printShapesReport();
        break;
    case 4:
        sortShapeData();
        break;
    }
}
/* ------------------------------------- Input Sensor Data ------------------------------------- */
void inputSensorData()
{
    string validShapeName = getShapeInput("name of shape", VALID_SHAPES_NAMES, 4);
    string validSpecialType = getShapeInput("special type", VALID_SPECIAL_TYPES, 2);
    bool isWarpSpace = (validSpecialType.compare("WS") == 0) ? true : false;

    cout << endl;

    if (validShapeName.compare(VALID_SHAPES_NAMES[0]) == 0)
    {
        vector<Point> points;
        getPoints(points, 12);
        shape2DArray[shape2D_index++] = new Cross(points, isWarpSpace);
        points.clear(); // To delete all stored elements
    }
    else if (validShapeName.compare(VALID_SHAPES_NAMES[3]) == 0)
    {
        int x, y, radius = -1;
        cout << PLEASE_ENTER << "x-ordinate of center : ";
        cin >> x;
        cout << PLEASE_ENTER << "y-ordinate of center : ";
        cin >> y;
        cout << PLEASE_ENTER << "radius (units) : ";
        cin >> radius;

        Point point(x, y);
        shape2DArray[shape2D_index++] = new Circle(point, radius, isWarpSpace);
    }
    else
    {
        vector<Point> points;
        getPoints(points, 4);

        if (validShapeName.compare(VALID_SHAPES_NAMES[1]) == 0)
        {
            shape2DArray[shape2D_index++] = new Rectangle(points, isWarpSpace);
        }
        else
        {
            shape2DArray[shape2D_index++] = new Square(points, isWarpSpace);
        }
        points.clear();
    }
    cout << "\nRecord succesfully stored. Going back to main menu ... \n"
         << endl;
}

string getShapeInput(string question, const string validStrings[], int size)
{
    string userInput, validShapeInput;
    bool isValidShapeInput = false;
    do
    {
        cout << PLEASE_ENTER << question << " : ";
        cin >> userInput;
        isValidShapeInput = stringValidation(userInput, validStrings, size);

        if (isValidShapeInput)
        {
            validShapeInput = userInput;
        }
        else
        {
            clearInputBuffer();
            printErrorMessage();
        }
    } while (!isValidShapeInput);
    return validShapeInput;
}

bool stringValidation(string &userInput, const string validStrings[], int size)
{
    transform(userInput.begin(), userInput.end(), userInput.begin(), ::toupper);

    bool isValidString = false;
    int i = 0;

    while (!isValidString && i < size)
    {
        if (validStrings[i].compare(userInput) == 0)
        {
            isValidString = true;
        }
        else
        {
            i++;
        }
    }
    return isValidString;
}

void getPoints(vector<Point> &points, const int noOfTimes)
{
    for (int i = 0; i < noOfTimes; i++)
    {
        int x, y;
        cout << PLEASE_ENTER << "x-ordinate of pt. " << (i + 1) << " : ";
        cin >> x;
        cout << PLEASE_ENTER << "y-ordinate of pt. " << (i + 1) << " : ";
        cin >> y;
        cout << endl;

        Point point(x, y);
        points.push_back(point);
    }
}

void deallocateShape2DArray()
{
    for (int i = 0; i < shape2D_index; ++i)
    {
        delete shape2DArray[i];
    }
}

/* ------------------------------------- calculate Area ------------------------------------- */
void calculateArea()
{
    for (int i = 0; i < shape2D_index; i++)
    {
        // For all ShapeTwoD except Circle
        if (shape2DArray[i]->getName().compare("Circle") != 0)
        {
            const vector<Point> &points = shape2DArray[i]->getPoints();
            shape2DArray[i]->setArea(shoelace(points));
        }
    }

    cout << "Computation Completed! ( " << shape2D_index << " records were updated )\n"
         << endl;
}

double shoelace(const vector<Point> &points)
{
    double area = 0.0;
    int j = points.size() - 1;
    for (int i = 0; i < points.size(); i++)
    {
        area += (points.at(j).getX() + points.at(i).getX()) * (points.at(j).getY() - points.at(i).getY());
        j = i;
    }
    return abs(area / 2.0);
}
/* ------------------------------------- Print Shapes Report ------------------------------------- */
void printShapesReport()
{
    for (int i = 0; i < shape2D_index; i++)
    {
        cout << shape2DArray[i]->toString() << endl;
    }
}

/* ------------------------------------- Sort Shape Data ------------------------------------- */
void sortShapeData()
{
    bool isQuit = false;
    do
    {
        printStringArray(SORT_OPTIONS, sizeof(SORT_OPTIONS) / sizeof(string), 7);
        char sortChoiceInput = getUserSortChoiceInput();
        processUser_SortChoiceInput(sortChoiceInput, isQuit);
        printShapesReport();
    } while (!isQuit);
}

char getUserSortChoiceInput()
{
    char validatedInput;
    string userInput;
    bool isChar = false;
    do
    {
        cout << "\nPlease select sort option ('q' to go main menu ) : ";
        cin >> userInput;
        isChar = charValidation(userInput, 'a', 'c');
    } while (!isChar);

    validatedInput = userInput.at(0);
    return validatedInput;
}

bool charValidation(string userInput, char min, char max)
{
    bool isChar = false;

    char userInput_char = userInput.at(0);
    if (!((userInput_char >= min && userInput_char <= max) || (userInput_char == 'q')) ||
        !isalpha(userInput_char) ||
        userInput.length() != 1)
    {
        clearInputBuffer();
        printErrorMessage();
    }
    else
    {
        isChar = true;
    }
    return isChar;
}

void processUser_SortChoiceInput(char sortChoiceInput, bool &isQuit)
{
    if (sortChoiceInput == 'q')
    {
        isQuit = true;
    }
    else
    {
        executeUser_SortChoiceInput(sortChoiceInput);
    }
}

bool sortByAreaAscending(const ShapeTwoD *lhs, const ShapeTwoD *rhs)
{
    return lhs->getArea() < rhs->getArea();
}

bool sortByAreaDescending(const ShapeTwoD *lhs, const ShapeTwoD *rhs)
{
    return lhs->getArea() > rhs->getArea();
}

bool sortBySpecialType_Area(const ShapeTwoD *lhs, const ShapeTwoD *rhs)
{
    string lhs_str = (lhs->getContainsWarpSpace()) ? "WS" : "NS";
    string rhs_str = (rhs->getContainsWarpSpace()) ? "WS" : "NS";

    return (lhs_str == rhs_str) ? sortByAreaDescending(lhs, rhs) : ((lhs_str > rhs_str) ? true : false);
}

void executeUser_SortChoiceInput(char choiceNumber)
{
    cout << "\n\nSort by ";
    switch (choiceNumber)
    {
    case 'a':
        cout << "area (smallest to largest) ... " << endl;
        sort(shape2DArray, shape2DArray + shape2D_index, sortByAreaAscending);
        break;
    case 'b':
        cout << "area (largest to smallest) ... " << endl;
        sort(shape2DArray, shape2DArray + shape2D_index, sortByAreaDescending);
        break;
    case 'c':
        cout << "special type and area (largest to smallest) ... " << endl;
        sort(shape2DArray, shape2DArray + shape2D_index, sortBySpecialType_Area);
        break;
    }
    cout << endl;
}