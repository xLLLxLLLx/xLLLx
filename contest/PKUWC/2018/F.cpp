#include <bits/stdc++.h>
using namespace std;
const int N = 20, M = (1 << 20), mod = 998244353;
struct data {
	int nt, to;
} a[N << 1];
int head[N], A[N], B[N], d[N];
int cnt = 0, n, q, rt;

void read(int &x) {
	char ch = getchar(); x = 0;
	for(; ch < '0' || ch > '9'; ch = getchar()) ;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = (x << 1) + (x << 3) +(ch ^ 48);
}

int f[N][M];

int mul(int x, int y) {
	return 1ll * x * y % mod;
}

int sub(int x, int y) {
	return (x - y + mod) % mod;
}

int add(int x, int y) {
	return (x + y) % mod;
}

void Add(int &x, int y) {
	x = add(x, y);
}

void Mul(int &x, int y) {
	x = mul(x, y);
}

void adde(int x, int y) {
	a[++cnt].to = y;
	a[cnt].nt = head[x];
	head[x] = cnt;
}

int q_pow(int x, int y) {
	int ans = 1;
	for(; y; y >>= 1) {
		if(y & 1) ans = mul(ans, x);
		x = mul(x, x);
	}
	return ans;
}

int mask;

void predfs(int u, int fa) {
	int opt = (mask >> u) & 1;
	if(u != rt && d[u] == 1) {
		if(opt) {
			if((1 << u) != mask) A[u] = 0, B[u] = add(f[fa][mask ^ (1 << u)], 1); 
			else A[u] = B[u] = 0;
		} else {
			A[u] = B[u] = 1;
		}
		return ;
	}
	int xs = q_pow(d[u], mod - 2);
	if(opt) {
		A[u] = 0;
		if((1 << u) == mask) B[u] = 0;
		else {
			for(int i = head[u]; i; i = a[i].nt) {
				int to = a[i].to;
				Add(B[u], add(f[to][mask ^ (1 << u)], 1));
			}
			Mul(B[u], xs);
		}
		for(int i = head[u]; i; i = a[i].nt) {
			int to = a[i].to;
			if(to == fa) continue;
			predfs(to, u);
		}
	} else {
		int pos = d[u], tmp = 0;
		for(int i = head[u]; i; i = a[i].nt) {
			int to = a[i].to;
			if(to == fa) {
				continue;
			}
			predfs(to, u);
			pos = sub(pos, A[to]), tmp = add(tmp, add(B[to], 1));
		}
		int gg = q_pow(pos, mod - 2);
		if(u != rt) A[u] = gg, B[u] = mul(tmp + 1, gg);
		else A[u] = 0, B[u] = mul(tmp, gg);
	}
}

void dfs(int u, int fa) {
	if(u == rt) {
		f[u][mask] = B[u];
	} else {
		f[u][mask] = add(mul(f[fa][mask], A[u]), B[u]);
	}
	for(int i = head[u]; i; i = a[i].nt) {
		int to = a[i].to;
		if(to == fa) continue;
		dfs(to, u);
	}
}

int main() {
	read(n), read(q), read(rt);
	rt--;
	for(int i = 1, x, y; i < n; ++i) {
		read(x), read(y);
		x--, y--;
		adde(x, y), adde(y, x);
		d[x]++, d[y]++;
	}
	int tot = (1 << n) - 1;
	for(int i = 1; i <= tot; ++i) {
		memset(A, 0, sizeof A);
		memset(B, 0, sizeof B);
		mask = i;
		predfs(rt, -1), dfs(rt, -1);
	}
	for(int o = 1, num; o <= q; ++o) {
		read(num);
		int now = 0;
		for(int i = 1, x; i <= num; ++i) {
			read(x);
			x--;
			now |= (1 << x);
		}
		// printf("now = %d\n", now);
		printf("%d\n", f[rt][now]);
	}
	return 0;
}