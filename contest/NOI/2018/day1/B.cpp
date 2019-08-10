#include <bits/stdc++.h>
using namespace std;
const int N = 11;
int n, ans = 0, pos = 0, now = 0;
int tr[N];
int a[N], b[N], vis[N];

bool check() {
	if(pos != now * 2) return false;
	for(int i = 1; i <= n; ++i) {
		if(a[i] > b[i]) return false;
		if(a[i] < b[i]) return true;
	}
	return false;
}

int lower(int x) {
	return x & (-x);
}

void upd(int x, int v) {
	for(; x < N; x += lower(x))
		tr[x] += v;
}

int get(int x) {
	int val = 0;
	for(; x; x -= lower(x))
		val += tr[x];
	return val;
}

void dfs(int dep) {
	if(dep > n) {
		if(check()) ans++;
		return ;
	}
	for(int i = 1; i <= n; ++i) {
		if(!vis[i]) {
			pos += abs(i - dep);
			now += dep - 1 - get(i - 1);
			b[dep] = i;
			vis[i] = 1;
			upd(i, 1);
			dfs(dep + 1);
			pos -= abs(i - dep);
			now -= dep - 1 - get(i - 1);
			upd(i, -1);
			vis[i] = 0;
		}
	}
}

int main() {
	freopen("inverse.in", "r", stdin);
	freopen("inverse.out", "w", stdout);
	int T;
	scanf("%d", &T);
	for(int o = 1; o <= T; ++o) {
		ans = 0;
		scanf("%d", &n);
		for(int i = 1; i <= n; ++i) {
			scanf("%d", &a[i]);
		}
		dfs(1);
		printf("%d\n", ans);
	}
	return 0;
}