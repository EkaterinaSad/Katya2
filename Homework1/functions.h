#pragma once
#include <iostream>
#include <fstream>
#include <cmath>
#include <exception>

struct Point{
    int x;
    int y;
};

struct Answer
{
    Point left;
    Point right;        
};
Answer firstVar(Point* input, int n);
Point* readFile(char* path, int& n);

