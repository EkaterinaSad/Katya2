#include "HWfunctions.h"

////////////////////// 2ND HW ///////////////////////

Answer firstVar(Point* input, int n)
{
    /* расстояние d = x*cos(a) + b*sin(a) ; x,y - точка, cos(a), sin(a) - компоненты нормали 
    к направляющему вектору прямой разделяющей плооскость 
    d > 0 - точка справа от прямой, d < 0 - точка слева*/
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

Answer secondVar(Point* in, int n)
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



///////////////////// 1ST HW /////////////////////


using namespace std;
int factorial(int n){
    if(n > 1)
        return n*factorial(n-1);
    else if(n < 0)
        cout << "Иди учи гамма функцию Эйлера";
    else
        return 1;
} 

int C_n_k(int n, int k){
    return factorial(n)/(factorial(k)*factorial(n-k));
}

double** funcValue(double x0, double xmax, double st, int& size, double (*fnc)(double))
{
    size = (xmax - x0)/st;
    double* x = new double[size]; 
    double* y = new double[size];

    for (int i = 0; i < size; i++)
    {
        x[i] = x0 + i*st;
        y[i] = fnc(x0 + i*st);
    }

    return new double*[2]{x, y};
}
