#include <bits/stdc++.h>
using namespace std;
const int N = 3e5 + 10, LOG = 20;
struct data {
	int nt, to;
} a[N << 1];
int con[N], f[N], be[N], af[N], st[N], rem[N], c[N];
int head[N], g[N][LOG + 1], dep[N], sz[N], dfn[N];
int n, cnt = 0, res = 0, now = 0, top = 0;

void add(int x, int y) {
	a[++cnt].to = y;
	a[cnt].nt = head[x];
	head[x] = cnt;
}

void predfs(int x, int fa) {
	dfn[x] = ++res;
	dep[x] = dep[fa] + 1;
	sz[x] = 1, g[x][0] = fa;
	for(int i = head[x]; i; i = a[i].nt) {
		int to = a[i].to;
		if(to == fa) {
			continue;
		}
		predfs(to, x);
		sz[x] += sz[to];
	}
}

void prepare() {
	for(int j = 1; j <= LOG; ++j)
		for(int i = 1; i <= n; ++i)
			g[i][j] = g[g[i][j - 1]][j - 1];
}

int GetLCA(int A, int B) {
	if(dep[A] > dep[B]) 
		swap(A, B);
	for(int i = LOG; i >= 0; --i)
		if(dep[g[B][i]] >= dep[A])
			B = g[B][i];
	if(A == B)
		return A;
	for(int i = LOG; i >= 0; --i)
		if(g[A][i] != g[B][i])
			A = g[A][i], B = g[B][i];
	return g[A][0];
}

int dis(int x, int y) {
	return dep[x] + dep[y] - 2 * dep[GetLCA(x, y)];
}

void dfs(int x) {
	c[++now] = x, rem[x] = sz[x];
	for(int i = head[x]; i; i = a[i].nt) {
		int to = a[i].to;
		dfs(to);
		if(!con[to]) continue;
		int d1 = dis(x, con[to]), d2 = dis(x, con[x]);
		if((d1 == d2 && (con[to] < con[x])) || d1 < d2 || !con[x])
			con[x] = con[to];
	}
}

void Dfs(int x) {
	if(!con[x]) return ;
	for(int i = head[x]; i; i = a[i].nt) {
		int to = a[i].to;
		int d1 = dis(to, con[to]), d2 = dis(to, con[x]);
		if((d1 == d2 && (con[x] < con[to])) || d1 > d2 || !con[to])
			con[to] = con[x];
		Dfs(to);
	}
}

void work(int x, int y) {
	int ny = y, mid = y;
	for(int i = LOG; i >= 0; --i)
		if(dep[g[ny][i]] > dep[x])
			ny = g[ny][i];
	rem[x] -= sz[ny];
	if(con[x] == con[y]) {
		f[con[x]] += sz[ny] - sz[y];
		return ;
	}
	for(int i = LOG; i >= 0; --i) {
		int nxt = g[mid][i];
		if(dep[nxt] <= dep[x]) continue;
		int d1 = dis(con[x], nxt), d2 = dis(con[y], nxt);
		if(d1 > d2 || (d1 == d2 && con[y] < con[x])) mid = nxt;
	}
	f[con[x]] += sz[ny] - sz[mid];
	f[con[y]] += sz[mid] - sz[y];
}

bool cmp(int x, int y) {
	return dfn[x] < dfn[y];
}

void go() {
	now = cnt = top = 0;
	int num;
	scanf("%d", &num);
	for(int i = 1; i <= num; ++i) {
		scanf("%d", &be[i]);
		con[be[i]] = be[i], af[i] = be[i];
	}
	sort(af + 1, af + 1 + num, cmp);
	if(con[1] != 1) st[++top] = 1;
	for(int i = 1; i <= num; ++i) {
		int pos = af[i], fa = 0;
		for(; top;) {
			fa = GetLCA(st[top], pos);
			if(top > 1 && dep[fa] < dep[st[top - 1]]) {
				add(st[top - 1], st[top]), top--;
			} else if(dep[fa] < dep[st[top]]) {
				add(fa, st[top]), top--;
				break;
			} else {
				break;
			}
		}
		if(st[top] != fa) 
			st[++top] = fa;
		st[++top] = pos;
	}
	for(; top > 1; --top)
		add(st[top - 1], st[top]);
	dfs(1), Dfs(1);
	for(int i = 1; i <= now; ++i)
		for(int j = head[c[i]]; j; j = a[j].nt)
			work(c[i], a[j].to);
	for(int i = 1; i <= now; ++i)
		f[con[c[i]]] += rem[c[i]];
	for(int i = 1; i <= num; ++i) 
		printf("%d ", f[be[i]]);
	puts("");
	for(int i = 1; i <= now; ++i)
		head[c[i]] = con[c[i]] = f[c[i]] = rem[c[i]] = 0;
}

int main() {
	scanf("%d", &n);
	for(int i = 1, x, y; i < n; ++i) {
		scanf("%d%d", &x, &y);
		add(x, y), add(y, x);
	}
	predfs(1, 0), prepare();
	memset(head, 0, sizeof head);
	int m;
	scanf("%d", &m);
	for(int o = 1; o <= m; ++o) {
		go();
	}
	return 0;
}