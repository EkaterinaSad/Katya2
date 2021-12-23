#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
using namespace std;
const double PI = atan(1) * 4;
int main()
{
    double x0, y0; // базовый вектор (1й в списке)
    double *x, *y;
    string line;
    ifstream infile=ifstream();
    ofstream outfile = ofstream();
    infile.open("in.txt", ios::in);
    infile >> x0;
    infile >> y0;
    bool finished = false;
    //cout << "x0=" << x0 << " y0=" << y0<<endl;
    int N = 0;
    double angl = -0, angr = 0, xl = 0, xr = 0, yl = 0, yr = 0;
    double norm0 = sqrt(x0 * x0 + y0 * y0);
    outfile << x0 << " " << y0 << endl;
    while (!finished && !infile.eof()) { // посчитаем к-во пар чисел оставшихся
        double x, y;
        infile >> x;
        if (infile.eof()) break;
        infile >> y;
        double dotpr = x0 * x + y0 * y;
        double norm1 = sqrt(x * x + y * y);
        double cos_val = dotpr / (norm0 * norm1);
        double z_val = x0 * y - y0 * x; // из векторного произведения
        /* от точности вычислений зависит правильный ответ */
        float ang = acos(cos_val) * 180.0 / PI; // "правильный" ответ
        if (z_val <= 0) ang = -ang;
 
        if ((angr - ang)>=0.0) {
            angr = ang;
            xr = x;
            yr = y;
        }
        
        if ((angl - ang)<0.0) {
            angl = ang;
            xl = x;
            yl = y;
        }
       
    }
    
    cout << "Leftmost: " <<  xl << " " << yl << "\n";
    cout << "Rightmost: " <<  xr << " " << yr << "\n";
    cout << endl;
}



