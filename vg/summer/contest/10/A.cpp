#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
struct data {
	int nt, to;
} a[N];
int dep[N], col[N], head[N], cnt = 0;

void add(int x, int y) {
	a[++cnt].to = y;
	a[cnt].nt = head[x];
	head[x] = cnt;
}

void dfs(int x, int fa) {
	dep[x] = dep[fa] + 1;
	for(int i = head[x]; i; i = a[i].nt) {
		dfs(a[i].to, x);
	}
}

int main() {
	int n;
	scanf("%d", &n);
	for(int i = 2, p; i <= n; ++i) {
		scanf("%d", &p);
		add(p, i);
	}
	dfs(1, 0);
	int ans = 0;
	for(int i = 1; i <= n; ++i) {
		col[dep[i]]++;
	}
	for(int i = 1; i <= n; ++i) {
		ans += (col[i] & 1);
	}
	printf("%d\n", ans);
	return 0;
}