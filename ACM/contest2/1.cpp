#include <bits/stdc++.h>
using namespace std;
int x[5], y[5];

int main() {
	int w, h;
	freopen("anniversary.in", "r", stdin);
	freopen("anniversary.out", "w", stdout);
	cin >> w >> h;
	for(int i = 0; i < 2; ++i)
		cin >> x[i] >> y[i];
	if(x[0] == x[1] || y[0] == y[1]) {
		if(x[0] == x[1]) {
			printf("0 %d %d %d\n", y[1], w, y[0]);
		} else {
			printf("%d 0 %d %d\n", x[1], x[0], h);
		}
	} else {
		printf("0 %d %d %d\n", y[1], w, y[0]);
	}
	return 0;
}