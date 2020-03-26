#include <iostream>
using namespace std;

int hike();
int main()
{
  cout << hike() << endl;
  system("pause");
  return 0;
}

int hike()
{
	short N, M;
	float L, V, W, time{};
	cout << "Enter N (amount of runners): ";
	cin >> N;
	cout << "Enter M (amount of bicycles): ";
	cin >> M;
	cout << "Enter L (distance): ";
	cin >> L;
	cout << "Enter V (speed without a bike): ";
	cin >> V;
	cout << "Enter W (speed with a bike): ";
	cin >> W;
	if (N < 1 || N > 19 || M < 0 || M > 19 || L < 0 || L > 100 || V < 0 || V > 10 || W < 0 || W > 50)
	{
		cout << "Input error!\n";
		return -1;
	}
	if (N <= M)
	{
		(W > V) ? time = 3600 * L / W : time = 3600 * L / V;
		return time;
	}
	if ((N -= M) == M)	//можно менять
	{
		float dif = W - V;
		float dtimeBiker = dif / W; // время, которое проходит велосипедист разницу
		float dtimeRunner = dif / V; //время, которое бегун проходит разницу
		float sumD = W*dtimeBiker + V * dtimeRunner;
		float r = L - int(L / sumD)*sumD; //остаток
		time += (int(L / sumD) * (dtimeBiker + dtimeRunner) + r / V);
		return time*3600;
	}
	else	//менять нельзя
		return (time = 3600 * L / V);
}
