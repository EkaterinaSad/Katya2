
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
	stringstream ss;
	infile.open("in.txt", ios_base::in);
	infile >> x0;
	infile >> y0;

	bool finished = false;
	//cout << "x0=" << x0 << " y0=" << y0<<endl;
	int N = 0;
	double angl = -0, angr = 0, xl = 0, xr = 0, yl = 0, yr = 0;
	double norm0 = sqrt(x0 * x0 + y0 * y0);

	while (!finished) { // посчитаем к-во пар чисел оставшихся
		double x, y;
		infile >> x;
		infile >> y;
		if (infile.eof()) break;
		double dotpr = x0 * x + y0 * y;
		double norm1 = sqrt(x * x + y * y);
		double cos_val = dotpr / (norm0 * norm1);
		double z_val = x0 * y - y0 * x; // из векторного произведения
		double ang = acos(cos_val) * 180 / PI;
		if (z_val <= 0) ang = -ang;
		//cout << ang << " ("<<x[i]<<","<<y[i]<<")\n";
		if (angr >= ang) {
			angr = ang;
			xr = x;
			yr = y;
		}
		if (angl <= ang) {
			angl = ang;
			xl = x;
			yl = y;
		}
	}
	//cout << endl << endl;
	//cout << "Leftmost: " << angl << " (" << xl << "," << yl << ")\n";
	//cout << "Rightmost: " << angr << " (" << xr << "," << yr << ")\n";
	cout << "Leftmost: " <<  xl << " " << yl << "\n";
	cout << "Rightmost: " <<  xr << " " << yr << "\n";
	cout << endl;
}



