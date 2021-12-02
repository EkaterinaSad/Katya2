
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
	//stringstream ss;
	//infile.open("input1.txt", ios_base::in);

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
		//float ang = acos(cos_val) * 180.0 / PI;
		double ang = acos(cos_val) * 180.0 / PI;
		if (z_val <= 0) ang = -ang;
		//cout << ang << " ("<<x[i]<<","<<y[i]<<")\n";
		//if (angr >= ang) {
		if ((angr - ang)>=0.0) {
			angr = ang;
			xr = x;
			yr = y;
		}
		//if (angl <= ang) {
		if ((angl - ang)<=0.0) {
			angl = ang;
			xl = x;
			yl = y;
		}
		if ((x == -2) && (y == 6))
			printf("%g %g %.12f\n", x, y, ang);
		if ((x == -3) && (y == 9))
			printf("%g %g %.12f\n", x, y, ang);

		outfile << x << " " << y << " " << ang << endl;
	}
	//cout << endl << endl;
	//cout << "Leftmost: " << angl << " (" << xl << "," << yl << ")\n";
	//cout << "Rightmost: " << angr << " (" << xr << "," << yr << ")\n";
	cout << "Leftmost: " <<  xl << " " << yl << "\n";
	cout << "Rightmost: " <<  xr << " " << yr << "\n";
	cout << endl;
}

/*
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






*/

