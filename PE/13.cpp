#include <bits/stdc++.h>
using namespace std;
const int N = 1010;
int a[N];

int main() {
	for(int i = 1; i <= 100; ++i) {
		for(int j = 1, x; j <= 50; ++j) {
			scanf("%1d", &x);
			a[j] += x;
		}
	}
	reverse(a + 1, a + 1 + 50);
	a[0] = 1000;
	for(int i = 1; i <= 1000; ++i) {
		a[i + 1] += a[i] / 10;
		a[i] %= 10;
	}
	while(a[0] > 1 && !a[a[0]]) --a[0];
	int ans = 0;
	for(int i = a[0]; i >= a[0]-9; --i)
		printf("%d", a[i]);
	return 0;
}