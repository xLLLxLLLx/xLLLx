#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 10;
struct data {
	int nt, to;
} a[N << 1];
int tr[N];
vector<int> g;
int f[N][2], head[N], cnt = 0;

void add(int x, int y) {
	a[++cnt].to = y;
	a[cnt].nt = head[x];
	head[x] = cnt;
}

void dfs(int u, int fa) {
	int pos = 0;
	for(int i = head[u]; i; i = a[i].nt) {
		int to = a[i].to;
		dfs(to, u);
		pos += f[to][0];
	}
	f[u][1] = pos + 1;
	f[u][0] = pos;
	for(int i = head[u]; i; i = a[i].nt) {
		int to = a[i].to;
		int tmp = f[to][1] + pos - f[to][0];
		if(f[u][0] < tmp) {
			f[u][0] = tmp;
			tr[u] = to;
		}
	}
}

void go(int x, int y) {
	if(y) {
		g.push_back(x);
		for(int i = head[x]; i; i = a[i].nt) {
			int to = a[i].to;
			go(to, 0);
		}
	} else {
		for(int i = head[x]; i; i = a[i].nt) {
			int to = a[i].to;
			if(tr[x] == to) {
				go(to, 1);
			} else {
				go(to, 0);
			}
		}
	}
}

int main() {
	freopen("grant.in", "r", stdin);
	freopen("grant.out", "w", stdout);
	int n;
	scanf("%d", &n);
	for(int i = 2, x; i <= n; ++i) {
		scanf("%d", &x);
		add(x, i);
	}
	dfs(1, 0);
	printf("%lld\n", 1ll * f[1][0] * 1000);
	go(1, 0);
	sort(g.begin(), g.end());
	for(int i = 0; i < g.size(); ++i) {
		printf("%d ", g[i]);
	}
	puts("");
	return 0;
}