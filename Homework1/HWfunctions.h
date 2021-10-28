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

/* 2nd HW */
Answer firstVar(Point* input, int n);
Answer secondVar(Point* in, int n);
Point* readFile(char* path, int& n);

/*  1st HW */
int factorial(int);
int C_n_k(int, int);
double** funcValue(double x0, double xmax, double st, int& size, double (*fnc)(double));