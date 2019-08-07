#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 2e5 + 10;
const int mod = 998244353, inv = (mod + 1) / 2;

int n, L, R;
int w[N], lf[N], deg[N], dep[N];
int fa[N], sz[N], siz[N], val[N], son[N];
vector <int> g[N];

ll add(ll x, ll y) {
	return (x += y) > mod ? x - mod : x;
}

ll sub(ll x, ll y) {
	return ((x - y) % mod + mod) % mod;
}

ll mul(ll x, ll y) {
	return x * y % mod;
}

ll q_pow(ll x, int y) {
	ll ans = 1;
	for(; y; y >>= 1) {
		if(y & 1)
			ans = mul(ans, x);
		x = mul(x, x);
	}
	return ans;
}

struct node {
	ll val, num;
    node() {val=0,num=0;}
    node(ll x_,int t_) {val=x_,num=t_;}
    void operator *= (const ll &u) {
        if(!u) num++;
        else val=val*u%mod;
    }
    void operator /= (const ll &u) {
        if(!u) num--;
        else val=val*q_pow(u, mod - 2)%mod;
    }
    operator ll() {return num?0:val;}
};

struct Martix {
	ll k, b;
	Martix() {}
	Martix(ll _k, ll _b) {
		k = _k, b = _b;
	}
	Martix operator * (Martix &A) const {
		return Martix(mul(k, A.k), add(b, mul(k, A.b)));
	}
} I;

struct tree {
#define ls ch[x][0]
#define rs ch[x][1]
	Martix s[N];
	node dp[N];
	int flg, rt;
	int f[N], q[N], ch[N][2];

	void up(int x) {
		s[x] = Martix(-dp[x], dp[x]);
		if(ls) s[x] = s[ls] * s[x];
		if(rs) s[x] = s[x] * s[rs];
	}

	bool isroot(int x) {
		return (x != ch[f[x]][0]) && (x != ch[f[x]][1]);
	}

	int build(int l, int r) {
		if(l > r) return 0;
		int sum = 0;
		for(int i = l; i <= r; ++i)
			sum += val[q[i]];
		int mid = 0;
		for(int i = l; i <= r; ++i)
			if((sum -= 2 * val[q[i]]) <= 0) {
				mid = i;
				break;
			}
		int x = q[mid];
		// printf("%d %d %d %d\n", l, r, mid, x);
		ls = build(l, mid - 1);
		rs = build(mid + 1, r);
		if(ls) f[ls] = x;
		if(rs) f[rs] = x;
		if(lf[x]) {
			if(!flg) dp[x].val = (x < w[1]);
			else dp[x].val = 1 - (x > w[1]);
			if(!dep[x]) dp[x].val = sub(1, dp[x].val);
		}
		up(x);
		return x;
	}

	int dfs(int x) {
		// printf("x = %d\n", x);
		for(int y = x; y; y = son[y]) {
			dp[y].val = 1;
			for(int i = 0; i < g[y].size(); ++i) {
				int to = g[y][i];
				if(to == son[y] || to == fa[y]) continue;
				int pos = dfs(to);
				f[pos] = y;
				dp[y] *= sub(1, s[pos].b);
			}
		}
		int t = 0;
		for(int y = x; y; y = son[y]) q[++t] = y;
		return build(1, t);
	}

	void print() {
		printf("rt = %d\n", rt);
		for(int i = 1; i <= n; ++i) {
			printf("dp[%d]= %lld %lld\n", i, dp[i].val, dp[i].num);
			printf("s[%d] = %lld %lld\n", i, s[i].k, s[i].b);
			printf("fa=%d, ls = %d, rs = %d\n", f[i], ch[i][0], ch[i][1]);
		}
	}

	void init(int _flg) {
		flg = _flg;
		s[0] = I;
		rt = dfs(1);
	}

	void upd(int x, ll v) {
		dp[x] = (node){v, 0};
		for( ; x; x = f[x]) {
			if(isroot(x)) {
				ll gg = sub(1, s[x].b);
				dp[f[x]] /= gg;
			}
			up(x);
			if(isroot(x)) {
				dp[f[x]] *= sub(1, s[x].b);
			}
		}
	}

	ll get() {
		return s[rt].b;
	}
} tr[2];

void predfs(int u, int da) {
	fa[u] = da;
	dep[u] = dep[da] ^ 1;
	sz[u] = 1, siz[u] = lf[u];
	if(dep[u]) w[u] = 0;
	else w[u] = n;
	for(int i = 0; i < g[u].size(); ++i) {
		int to = g[u][i];
		if(to == da) {
			continue;
		}
		predfs(to, u);
		if(dep[u]) w[u] = max(w[u], w[to]);
		else w[u] = min(w[u], w[to]);
		sz[u] += sz[to], siz[u] += siz[to];
		if(sz[to] > sz[son[u]])
			son[u] = to;
	}
	if(lf[u]) w[u] = u;
	val[u] = sz[u] - sz[son[u]];
}

ll d[N];

int main() {
	I.k = 1, I.b = 0;
	scanf("%d%d%d", &n, &L, &R);
	for(int i = 1, x, y; i < n; ++i) {
		scanf("%d%d", &x, &y);
		g[x].push_back(y);
		g[y].push_back(x);
		deg[x]++, deg[y]++;
	}
	for(int i = 2; i <= n; ++i)
		if(deg[i] == 1) lf[i] = 1;
	predfs(1, 0);
	// for(int i = 1; i <= n; ++i) {
	// 	printf("i = %d, fa = %d, sz = %d, siz = %d, dep = %d, w = %d, leaf = %d, son = %d\n", i, fa[i], sz[i], siz[i], dep[i], w[i], lf[i], son[i]);
	// }
	for(int i = 0; i < 2; ++i) tr[i].init(i);//, tr[i].print();
	ll pos = q_pow(2, siz[1]), tmp = q_pow(2, siz[1] - 1);
	for(int i = 1; i < n; ++i) {
		int nw = w[1] - 1 + i;
		// printf("qq%d\n", nw);
		if(nw > w[1] && nw <= n && lf[nw]) 
			tr[0].upd(nw, inv);
		nw = w[1] + 1 - i;
		// printf("pp%d\n", nw);
		if(nw < w[1] && nw >= 1 && lf[nw]) 
			tr[1].upd(nw, inv);
		ll v1 = sub(1, tr[0].get()), v2 = tr[1].get();
		// printf("%lld %lld\n", v1, v2);
		// puts("----");
		// tr[0].print(), tr[1].print();
		d[i] = sub(pos, mul(tmp, mul(v1, v2)));
		// printf("%lld\n", d[i]);
	}
	d[n] = pos - 1;
	for(int i = L; i <= R; ++i) 
		printf("%lld ", sub(d[i], d[i - 1]));	
	return 0;
}