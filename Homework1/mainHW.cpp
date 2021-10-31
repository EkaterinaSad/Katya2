#include "functions.h"

using namespace std;

int main()
{
    int n = 0;

    Point* points = readFile("in.txt", n);
    Answer res = firstVar(points, n);

    cout << "Leftmost: " << res.left.x << ' ' << res.left.y << '\n' <<
            "Rightmost: " <<  res.right.x << ' ' << res.right.y << endl;

    delete points;


    return 0;
}
