#include <iostream>
#include <iomanip>
using namespace std;

int main() {
  long double factorial = 1;
  cout << setprecision(0) << fixed;
  for (int i = 1; i < 101; i++)
    cout << i << "!:\t" << (factorial *= i) << endl;
  cin.get();
  return 0;
}
