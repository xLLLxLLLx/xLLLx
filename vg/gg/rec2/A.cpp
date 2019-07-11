#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 2e5 + 10, mod = 1e9 + 7;
struct data{
	int nt, to;
} a[N << 1];
int head[N], dep[N], f[N], vis[N], vs[N], cnt = 0, h = 0, res = 0;

void add(int x, int y) {
	a[++cnt].to = y;
	a[cnt].nt = head[x];
	head[x] = cnt;
}

void Mul(ll &x, ll y) {
	x = (x * y) % mod;
}

ll q_pow(ll x, int y) {
	ll ans = 1;
	for(; y; y >>= 1) {
		if(y & 1) Mul(ans, x);
		Mul(x, x);
	}
	return ans;
}

void dfs(int u, int fa) {
	if(h) return ;
	f[u] = fa, dep[u] = dep[fa] + 1, vs[u] = 1;
	for(int i = head[u]; i; i = a[i].nt) {
		int to = a[i].to;
		if(to == fa) {
			continue;
		}
		if(h) return ;
		if(vs[to]) {
			int uu = u, vv = to;
			if(dep[uu] < dep[vv]) {
				swap(uu, vv);
			}
			for(; uu != vv; ) {
				h++;
				vs[uu] = 1;
				uu = f[uu];
				vs[uu] = 1;
			}
			h++;
		} else {
			dfs(to, u);
		}
	}
}

void Dfs(int u, int fa) {
	res++;
	vis[u] = 1;
	for(int i = head[u]; i; i = a[i].nt) {
		int to = a[i].to;
		if(vis[to]) {
			continue;
		}
		Dfs(to, u);
	}
}

int main() {
	int n;
	scanf("%d", &n);
	for(int i = 1, x; i <= n; ++i) {
		scanf("%d", &x);
		add(i, x), add(x, i);
	}
	ll ans = 1;
	for(int i = 1; i <= n; ++i) {
		if(vis[i]) {
			continue;
		}
		h = 0, res = 0;
		dfs(i, 0), Dfs(i, 0);
		if(h) {
			Mul(ans, (q_pow(2, h) - 2 + mod) % mod);
			Mul(ans, q_pow(2, res - h));
		} else {
			Mul(ans, q_pow(2, res));
		}
	}
	printf("%lld\n", ans);
	return 0;
}