#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e5 + 10;
int a[N], b[N], c[N], nm[10];

bool check() {
	if(c[0] < 9) return false;
	memset(nm, 0, sizeof nm);
	for(int i = 1; i <= 9; ++i) {
		if(!c[i] || nm[c[i]]) return false;
		nm[c[i]] = 1;
	}
	memset(nm, 0, sizeof nm);
	for(int i = c[0]; i >= c[0] - 8; --i) {
		if(!c[i] || nm[c[i]]) return false;
		nm[c[i]] = 1;
	}
	return true;
}

void add() {
	for(int i = 1; i <= max(a[0], b[0]); ++i) {
		c[i] = a[i] + b[i];
	}
	c[0] = max(a[0],b[0]) + 1;
	for(int i = 1; i <= c[0]; ++i) {
		c[i + 1] += c[i] / 10;
		c[i] %= 10;
	}
	while(c[0] > 1 && !c[c[0]]) c[0]--;
	for(int i = 0; i <= b[0]; ++i)
		a[i] = b[i];
	for(int i = 0; i <= c[0]; ++i)
		b[i] = c[i];
}

int main() {
	a[0] = b[0] = a[1] = b[1] = 1;
	for(int i = 3; i < N; ++i) {
		add();
		if(i <= 15) {
			for(int j = c[0]; j >= 1; --j)
				printf("%d", c[j]);
			puts("");
		}
		if(check()) {
			return printf("%d\n", i), 0;
		}
	}
	return 0;
}