#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;
struct data {
	int nt, to;
} a[N << 1];
int head[N], col[N], dep[N], f[N], vs[N], vis[N], cnt = 0, h = 0;

void add(int x, int y) {
	// printf("%d %d\n", x, y);
	a[++cnt].to = y;
	a[cnt].nt = head[x];
	head[x] = cnt;
}

void Dfs(int u, int fa) {
	vis[u] = 1;
	for(int i = head[u]; i; i = a[i].nt) {
		int to = a[i].to;
		if(a[i].to == fa || vis[to]) {
			continue;
		}
		Dfs(to, u);
	}
}

void dfs(int u, int fa) {
	// printf("%d %d\n", u, fa);
	f[u] = fa, dep[u] = dep[fa] + 1, vs[u] = 1;
	if(h) return ;
	for(int i = head[u]; i; i = a[i].nt) {
		if(h) return ;
		int to = a[i].to;
		if(to == fa) {
			continue;
		}
		if(vs[to]) {
			int uu = u, vv = to;
			if(dep[uu] < dep[vv]) swap(uu, vv);
			for(; uu != vv; ) {
				uu = f[uu];
				h++;
			}
			h++;
			return ;
		}
		dfs(to, u);
	}
}

int main() {
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &col[i]);
		if(col[i] != i) {
			add(i, col[i]), add(col[i], i);
		}
	}
	int pos = 7 * n + 1, tmp = 3 * n, ans = 0;
	for(int i = 1; i <= n; ++i) {
		if(!vis[i]) {
			h = 0;
			dfs(i, 0);
			Dfs(i, 0);
			// printf("qq%d %d\n", i, h);
			if(h) {
				ans += h - 1;
			}
		}
	}
	pos -= ans, tmp -= ans;
	if(pos & 1) {
		printf("Petr\n");
	} else if(tmp & 1) {
		printf("Um_nik\n");
	}
	return 0;
}