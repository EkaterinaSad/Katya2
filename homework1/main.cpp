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

int main(int argc, char** argv){
	if (argc == 2) {
		// есть один агрумент
		//в argv[1] содержится строка с первым агрументом (имя файла)
		//std::cout << "1st argument : " << argv[1] << std::endl;
		string filePath = "in.txt";
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
			cout << "Leftmost: " << points[temp_index].x << " " << points[temp_index].y<< endl;
			cout << "Rightmost does not exist";
		}
		else if (temp_index == points.size() - 1) {
			cout << "Leftmost does not exist"<< endl;
			cout << "Rightmost: " << points[temp_index-1].x << " " << points[temp_index].y;
		}
		else {
			cout << "Leftmost: " << points[temp_index].x << " " << points[temp_index].y << endl;
			cout << "Rightmost: " << points[temp_index-1].x << " " << points[temp_index].y;
		}
		int a;
		cin >> a;
	}

}
