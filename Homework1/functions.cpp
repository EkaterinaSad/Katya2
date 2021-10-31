#include "functions.h"

/* clill*/
Answer firstVar(Point* in, int n)
{
    double cos = in[0].x/sqrt(in[0].x*in[0].x + in[0].y*in[0].y);
    double sin = in[0].y/sqrt(in[0].x*in[0].x + in[0].y*in[0].y);

    double maxRight = 1;
    Point maxRightPoint{0,0};

    double maxLeft = 1;
    Point maxLeftPoint{0,0};

    for( int i = 1; i < n; i++)
    {
        double temp = in[i].x*sin + in[i].y*(-cos);
        double cs = (in[i].x*cos + in[i].y*sin)/sqrt(in[i].x*in[i].x + in[i].y*in[i].y);

        if(cs <= maxRight && temp >= 0)
        {
            maxRight = cs;
            maxRightPoint = in[i];
        }
        else if(cs <= maxLeft && temp < 0)
        {
            maxLeft = cs;
            maxLeftPoint = in[i];
        }
    }
    return Answer{maxLeftPoint, maxRightPoint};
}



Point* readFile(char* path, int& n)
{   

    const int MAX = 10;
    char buffer[MAX];
    std::ifstream in(path);

    if(in.is_open()==true)
    {
        while(!in.eof())
        {
            in.getline(buffer, MAX);
            n++;
        }

        Point* points = new Point[n];

        n = 0;
        in.seekg(0);
        while(!in.eof())
        {
            Point inPoint;
            in >> inPoint.x >> inPoint.y;
            points[n] = inPoint;
            n++;
        }

        return points;
    }
    else {
        throw std::runtime_error("No file!");
    }    
}

