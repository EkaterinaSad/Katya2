

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;
struct point {
	float x;
	float y;
	float vx;
	float vy;
};

struct border {
	float x;
	float h;
};

float g = -9.81;

float get_time_of_intersection(point p, border curr_border) {
	return (curr_border.x - p.x) / p.vx;
}

int check_intersection(point *p, border curr_border) {
	float t = get_time_of_intersection(*p, curr_border);
	float y_of_intersection = p->y + p->vy * t + g*t*t / 2;
	if ((y_of_intersection < curr_border.h)&&(y_of_intersection>=0)) {
		p->x = p->x + p->vx*t;
		p->y = y_of_intersection;
		p->vx = p->vx * (-1);
		p->vy = p->vy + g*t;
		return true;
	}
	return false;
}

void get_first_intersection(point *p, vector<border> borders, bool direction, int first_index) {
	bool intersected = false;
	int intersection_index;
	if (direction) {//движение вправо
		for (int i = first_index; i < borders.size(); ++i) {
			if (check_intersection(p, borders[i])) {//если произошло столкновение с преградой
				intersected = true;
				intersection_index = i - 1;
				direction = !direction;
				break;
			}
		}
	}
	else {//движение влево
		for (int i = first_index; i >= 0; --i) {
			//cout << i << "\n";
			if (check_intersection(p, borders[i])) {//если произошло столкновение с преградой
				intersected = true;
				intersection_index = i + 1;
				direction = !direction;
				break;
			}
		}
	}
	if (intersected) {
		//cout << p->x<<" "<<p->y << " " << p->vx << " " << p->vy << "\n";
		get_first_intersection(p, borders, direction, intersection_index);
	}
}

int get_landig_interval(point p, vector<border> borders) {
	float t1 = (-p.vy - sqrt(p.vy*p.vy - 2 * p.y*g)) / (g);
	float t2 = (-p.vy + sqrt(p.vy*p.vy - 2 * p.y*g)) / (g);
	float t;
	if (t1 >= 0) {
		t = t1;
	}
	else {
		t = t2;
	}
	float x_of_landing = p.x + p.vx*t;
	int ans = 0;
	
	for (int i = 0; i < borders.size(); ++i) {
		if (x_of_landing > borders[i].x) {
			ans = i+1;
		}
	}
	return ans;
}

int main(int argc, char** argv) {
	if (argc == 2) {
		// есть один агрумент
		 //в argv[1] содержится строка с первым агрументом (имя файла)
		std::cout << "1st argument : " << argv[1] << std::endl;
		}
		else{
			return -1;
		}
        
	ifstream file(argv[1]);
	if (file) {// файл верно открыт
		point p;
		vector<border> b;
		border tempb;
		float s;
		int i = 0;
		for (file >> s; !file.eof(); file >> s) {
			if (i == 0) {//первая строчка
				p.x = 0;
				p.y = s;
			}
			else if (i == 1) {//вторая строка первое значение
				p.vx = s;
			}
			else if (i == 2) {//вторая строка второе значение
				p.vy = s;
			}
			else {
				if (i % 2 == 1) {//n-я строка первое значение
					tempb.x = s;
				}
				else {//n-я строка второе значение
					tempb.h = s;
					b.push_back(tempb);

				}
			}
			++i;
		}
		if (b.size() != 0) {	//если перегородки есть
			file >> s;	//еще раз считываем, потому что в конце файла нет пробела
			tempb.h = s;
			b.push_back(tempb);
		}

		else {	//если перегородок вообще не передали
			tempb.x = 0;
			tempb.h = 0;
			b.push_back(tempb);
		}
		

		get_first_intersection(&p, b, true, 0);
		cout << get_landig_interval(p, b);
		return get_landig_interval(p, b);
	}
}

