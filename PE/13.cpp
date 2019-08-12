#include <bits/stdc++.h>
using namespace std;
const int N = 1e4 + 10;
int a[N], b[N], c[N];

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
	for(int i = 0; i <= c[0]; ++i)
		b[i] = c[i];
}

int main() {
	for(int i = 1; i <= 50; ++i)
		scanf("%1d", &a[i]);
	a[0] = b[0] = 50;
	for(int i = 1; i <= 50; ++i)
		scanf("%1d", &b[i]);
	reverse(a + 1, a + 1 + 50), reverse(b + 1, b + 1 + 50);
	add();
	for(int i = 1; i <= 98; ++i) {
		for(int j = 1; j <= 50; ++j)
			scanf("%1d", &a[i]);
		reverse(a + 1, a + 1 + 50);
		add();
	}
	for(int i = c[0]; i >= c[0] - 9; --i)
		printf("%d", c[i]);
	puts("");
	return 0;
}