#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e5 + 10, LOG = 18, M = 1e7 + 1;
const int mod = 1e9 + 7;
struct data {
	int nt, to;
} a[N << 1];
struct node {
	int id, v;
};
vector<node> g[N];
int n, q, cnt = 0;
int pr[M], s[M], yz[N * 30];
int head[N], dep[N], f[N][LOG + 1];
int val[N], w[N], d[N];

void adde(int x, int y) {
	a[++cnt].to = y;
	a[cnt].nt = head[x];
	head[x] = cnt;
}

void Add(int &x, ll y) {
	x = (x * 1ll + y) % mod;
}

void Mul(int &x, ll y) {
	x = (x * 1ll * y) % mod;
}

ll add(ll x, ll y) {
	return (x + y) %mod;
}

ll mul(ll x, ll y) {
	return x * y % mod;
}

void init() {
	for(int i = 2; i < M; ++i) {
		if(!pr[i]) {
			pr[i] = i;
			yz[++yz[0]] = i;
		}
		for(int j = 1; j <= yz[0]; ++j) {
			if(i * yz[j] >= M) break;
			if(!pr[i * yz[j]]) {
				pr[i * yz[j]] = yz[j];
			}
			if(i % yz[j] == 0) break;
		}
	}
}

void dfs(int u, int fa) {
	dep[u] = dep[fa] + 1, f[u][0] = fa;
	for(int i = head[u]; i; i = a[i].nt) {
		int to = a[i].to;
		if(to == fa) {
			continue;
		}
		dfs(to, u);
	}
}

void yyqx() {
	for(int j = 1; j <= LOG; ++j) 
		for(int i = 1; i <= n; ++i) {
			f[i][j] = f[f[i][j - 1]][j - 1];
		}
}

int GetLCA(int A, int B) {
	if(dep[A] > dep[B]) swap(A, B);
	for(int i = LOG; i >= 0; --i)
		if(dep[f[B][i]] >= dep[A]) B = f[B][i];
	if(A == B) return A;
	for(int i = LOG; i >= 0; --i) {
		if(f[A][i] != f[B][i]) {
			A = f[A][i], B = f[B][i];
		}
	}
	return f[A][0];
}

int rev(int x) {
	int y = mod - 2;
	int ans = 1;
	for(; y; y >>= 1) {
		if(y & 1) Mul(ans, x);
		Mul(x, x);
	}
	return ans;
}

void work(int u, int fa) {
	for(int i = w[u]; i > 1; ) {
		for(int t = pr[i], j = t; i % t == 0; i /= t, j *= t) {
			Mul(s[j], t);
		}
	}
	int len = g[u].size();
	for(int k = 0; k < len; ++k) {
		for(int i = val[g[u][k].id]; i > 1; ) {
			for(int t = pr[i], j = t; i % t == 0; i /= t, j *= t) {
				if(g[u][k].v) Mul(d[g[u][k].id], rev(s[j]));
				else Mul(d[g[u][k].id], s[j]);
			}
		}
	}
	for(int i = head[u]; i; i = a[i].nt) {
		int to = a[i].to;
		if(to == fa) {
			continue;
		}
		work(to, u);
	}
	for(int i = w[u]; i > 1; ) {
		for(int t = pr[i], j = t; i % t ==0; i /= t, j *= t) {
			Mul(s[j], rev(t));
		}
	}
}

int main() {
	init();
	scanf("%d", &n);
	for(int i = 1, x, y; i < n; ++i) {
		scanf("%d%d", &x, &y);
		adde(x, y), adde(y, x);
	}
	dfs(1, 0), yyqx();
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &w[i]);
	}
	scanf("%d", &q);
	for(int o = 1, x, y; o <= q; ++o) {
		scanf("%d%d%d", &x, &y, &val[o]);
		int z = GetLCA(x, y);
		g[x].push_back((node){o, 0});
		g[y].push_back((node){o, 0});
		g[z].push_back((node){o, 1});
		g[f[z][0]].push_back((node){o, 1});
		d[o] = 1;
	}
	for(int i = 1; i < M; ++i) s[i] = 1;
	work(1, 0);
	for(int i = 1; i <= q; ++i) {
		printf("%d\n", d[i]);
	}
	return 0;
}