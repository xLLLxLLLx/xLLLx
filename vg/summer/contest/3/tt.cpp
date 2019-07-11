#include <bits/stdc++.h>
using namespace std;

int main() {
	int x;
	cin >> x;
	for(;;) {
		int y, z;
		cin >> y >> z;
		y %= x, z %= x;
		if(y >= z) printf("x\n");
		else printf("y\n");
	}
	return 0;
}