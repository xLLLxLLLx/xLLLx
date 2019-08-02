#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main() {
	double h, l;
	cin >> h >> l;
	double pos = (l * l - h * h) / (2.0 * h);
	printf("%.9f\n", pos);
	return 0;
}