#include <fstream>
#include <cstring>
#include <iostream>

using namespace std;

const int CAP = 100;
const int MAX_CHAR = 101;
//This needs to come from main()
const int size = 0;

//enum origin {US, Europe, Japan};


enum whereFrom {US, Europe, Japan, Illegal};

struct car
{
    char name[MAX_CHAR];
    double mpg;
    int cylinders;
    double displacement;
    double horsepower;
    double weight;
    double acceleration;
    int model;
    whereFrom origin;
};
