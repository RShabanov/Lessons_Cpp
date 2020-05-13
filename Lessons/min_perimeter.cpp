#include <iostream>
#include <algorithm>
#include <climits>
#include <fstream>
#include <ctime>
using namespace std;


struct point { int x, y, id; };

inline bool cmp_x(const point& a1, const point& a2) { return a1.x < a2.x || a1.x == a2.x && a1.y < a2.y; }

inline bool cmp_y(const point& a1, const point& a2) { return a1.y < a2.y; }

int N;
point* a;
point* temp;
double perimeter = DBL_MAX;
point triangle[3];

inline double distance(const point& a1, const point& a2) {
	return sqrt((a1.x - a2.x)*(a1.x - a2.x) + (a1.y - a2.y)*(a1.y - a2.y) + 0.0);
}

inline void applicant(const point& a1, const point& a2, const point& a3) {
	double per = distance(a1, a2) + distance(a1, a3) + distance(a2, a3);
	if (per < perimeter) {
		perimeter = per;
		triangle[0] = a1;
		triangle[1] = a2;
		triangle[2] = a3;
	}
}

void rec(int l, int r) {
	if (r - l <= 3) {
		applicant(a[l], a[l + 1], a[r]);
		return;
	}

	int m = (l + r) >> 1;
	point mid = a[m];
	rec(l, m), rec(m + 1, r);

	//merge(a + l, a + m + 1, a + m + 1, a + r + 1, temp, &cmp_y);

	copy(temp, temp + r - l + 1, a + l);

	int tsz = 0;
	for (int i = l; i <= r; i++)
		if (distance(mid, a[i]) <= (perimeter / 2)) {
			for (int j = tsz - 1; j >= 0 && distance(temp[j], a[i]) < (perimeter / 2); j--)
				applicant(a[i], temp[j], mid);
			temp[tsz++] = a[i];
		}
}

time_t example1(int N, bool flag) {
	int xmin = 0;
	int xmax = 359;
	int ymin = -90;
	int ymax = 90;

	temp = new point[N];
	a = new point[N];
	for (int i = 0; i < N; i++) {
		a[i].x = xmin + rand() % (xmax - xmin + 1);
		a[i].y = ymin + rand() % (ymax - ymin + 1);
		a[i].id = i;
	}

	time_t start, end;
	start = clock();
	sort(a, a + N, &cmp_x);
	rec(0, N - 1);
	end = clock();

	if (flag) {
		ofstream in("exmaple.dat");
		in << "ID\tX\tY\n";
		ofstream rez("nearest_pair.dat");
		rez << "ID\tX\tY\n";
		for (int i = 0; i < N; i++)
			in << a[i].id << '\t' << a[i].x << '\t' << a[i].y << '\n';
		in.close();

		cout << "Min_perimeter: " << perimeter << endl;
		cout << "ID\tX\tY\n";
		for (point t : triangle) {
			cout << t.id << '\t' << t.x << '\t' << t.y << endl;
			rez << t.id << '\t' << t.x << '\t' << t.y << endl;
		}
		rez.close();
	}

	delete[] a;
	delete[] temp;
	return end - start;
}

int main() {
	srand(time_t(NULL));

	ofstream rez_time("timer_algo.dat");

	int pow10 = 10;
	for (int raz = 2; raz <= 6; raz++) {
		cout << "raz = " << raz << '\t';
		pow10 *= 10;
		for (int i = 1; i < 10; i++) {
			cout << i << ' ';
			N = i * pow10;
			time_t t = example1(N, false);
			rez_time << N << '\t' << t << '\n';
		}
		cout << endl;
	}
	rez_time.close();
	cin.get();
	return 0;
}
