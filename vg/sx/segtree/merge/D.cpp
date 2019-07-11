#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
struct data {
	int nt, to;
} a[N << 1];
int head[N], col[N], cnt = 0;

void add(int x, int y) {
	a[++cnt].to = y;
	a[cnt].nt = head[x];
	head[x] = cnt;
}

int main() {
	int n;
	while(scanf("%d", &n) == 1) {
		for(int i = 1; i <= n; ++i) {
			scanf("%d", &col[i]);
		}
		for(int i = 1, x, y; i < n; ++i) {
			scanf("%d%d", &x, &y);
			add(x, y), add(y, x);
		}
	}
	return 0;
}