#include <bits/stdc++.h>
using namespace std;
const int N = 10010;
int a[N], b[N], c[N];

void add(int x) {
	b[0] = 0;
	for(; x; x /= 10) b[++b[0]] = x % 10;
	c[0] = a[0] + b[0] + 1;
	for(int i = 1; i <= c[0]; ++i) c[i] = 0;
	for(int i = 1; i <= b[0]; ++i)
		for(int j = 1; j <= a[0]; ++j) {
			c[i + j - 1] += b[i] * a[j];
		}
	for(int i = 1; i <= c[0]; ++i) {
		c[i + 1] += c[i] / 10;
		c[i] %= 10;
	}
	while(c[0] > 1 && !c[c[0]]) --c[0];
	for(int i = 0; i <= c[0]; ++i)
		a[i] = c[i];
}

int main() {
	a[0] = a[1] = 1;
	for(int i = 1; i <= 1000; ++i) {
		add(2);
		printf("now=%d\n", i);
		for(int j = a[0]; j >= 1; --j)
			printf("%d", a[j]);
		puts("\n");
	}
	int ans = 0;
	for(int i = 1; i <= a[0]; ++i)
		ans += a[i];
	printf("%d\n", ans);
	return 0;
}