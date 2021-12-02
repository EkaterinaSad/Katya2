
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
		if ((angl - ang)<0.0) {
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




#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct vec {
    float x;
    float y;
    float sinus;
    float cosinus;
};

struct point {
    float x;
    float y;
};

bool compare_points_by_y(point a, point b) {
    return a.y < b.y;
}

void define_trigonometry(vec *pivot) {
    float length = sqrt(pivot->x*pivot->x + pivot->y*pivot->y);
    pivot->sinus = pivot->y / length;
    pivot->cosinus = pivot->x / length;
}

void rotate_points(vector<point> &points, vec pivot) {
    float temp_x;
    float temp_y;
    for (int i = 0; i < points.size(); ++i) {
        temp_x = points[i].x*pivot.cosinus + points[i].y*pivot.sinus;
        temp_y = -(points[i].x*pivot.sinus + points[i].y*pivot.cosinus);
        points[i].x = temp_x;
        points[i].y = temp_y;
    }
}

void undo_rotation(point *point, vec pivot) {
    float temp_x;
    float temp_y;
    temp_x = point->x*pivot.cosinus - point->y*pivot.sinus;
    temp_y = +point->x*pivot.sinus + point->y*pivot.cosinus;
    point->x = temp_x;
    point->y = temp_y;
}

void sort_points(vector<point> *points) {
    sort(points->begin(), points->end(), compare_points_by_y);
}

int return_index(vector<point> &points, vec pivot) {
    for (int i = 0; i < points.size(); ++i) {
        if (points[i].y > 0) {
            if (i > 0) {
                undo_rotation(&points[i - 1], pivot);
            }
            undo_rotation(&points[i], pivot);
            return i;
        }
    }
    return points.size() - 1;
}

int main(int argc, char** argv) {
    if (argc == 2) {
        // есть один агрумент
        //в argv[1] содержится строка с первым агрументом (имя файла)
        //std::cout << "1st argument : " << argv[1] << std::endl;
        string filePath = "in6.txt";
    }
    else {
        return -1;
    }

    ifstream file("in.txt");
    //ifstream file(argv[1]);
    if (file) {// файл верно открыт
        vec pivot;
        vector<point> points;
        point temp_point;
        float s;
        int i = 0;
        for (file >> s; !file.eof(); file >> s) {
            if (i == 0) {//первая сткочка первое значение
                pivot.x = s;
            }
            else if (i == 1) {//первая сткочка второе значение
                pivot.y = s;
            }
            else {
                if (i % 2 == 0) {//n-я строка первое значение
                    temp_point.x = s;
                }
                else {//n-я строка второе значение
                    temp_point.y = s;
                    points.push_back(temp_point);
                }
            }
            ++i;
        }

        file >> s;	//еще раз считываем, потому что в конце файла нет пробела
        temp_point.y = s;;
        points.push_back(temp_point);

        define_trigonometry(&pivot);
        rotate_points(points, pivot);
        sort_points(&points);
        int temp_index = return_index(points, pivot);
        if (temp_index == 0) {
            cout << "Leftmost: " << points[temp_index].x << " " << points[temp_index].y << endl;
            cout << "Rightmost does not exist";
        }
        else if (temp_index == points.size() - 1) {
            cout << "Leftmost does not exist" << endl;
            cout << "Rightmost: " << points[temp_index - 1].x << " " << points[temp_index].y;
        }
        else {
            cout << "Leftmost: " << points[temp_index].x << " " << points[temp_index].y << endl;
            cout << "Rightmost: " << points[temp_index - 1].x << " " << points[temp_index].y;
        }
    }
    return 1;
}


*/

