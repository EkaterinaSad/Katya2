#include "functions.h"


/* clill*/
Answer firstVar(Point* input, int n)
{
    double sin = -input[0].x/sqrt(input[0].x*input[0].x + input[0].y*input[0].y);
    double cos = input[0].y/sqrt(input[0].x*input[0].x + input[0].y*input[0].y);

    double maxRight = 0;
    Point maxRightPoint{0,0};

    double maxLeft = 0;
    Point maxLeftPoint{0,0};

    for (int i = 1; i < n; i++)
    {
        double dist = input[i].x*cos + input[i].y*sin;

        if (dist > maxRight)
        {
            maxRight = dist;
            maxRightPoint = input[i];
        }
        else if (dist <= maxLeft)
        {
            maxLeft = dist;
            maxLeftPoint = input[i];
        }
    }

    return Answer {maxLeftPoint, maxRightPoint};
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

