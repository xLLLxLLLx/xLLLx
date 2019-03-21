#include<bits/stdc++.h>
#define rep(i,a,b) for (int i=(a); i<=int(b); i++)
using namespace std;

inline int read() {
	char ch = getchar(); int x = 0, op = 1;
	while (ch < '0' || '9' < ch) { if (ch == '-') op = -1; ch = getchar(); }
	while ('0' <= ch && ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
	return op * x;
}

const int maxn = 200009;
struct node { int u, v, s, t; } a[maxn];
int pa[maxn], rk[maxn], val[maxn], ans[maxn], n, m, T, top;
int stk[maxn]; vector<int> p;

int getpa(int x) {
	while (pa[x] != x) x = pa[x];
	return x;
}

int getdist(int x) {
	int res = 0;
	while (pa[x] != x) {
		res ^= val[x]; x = pa[x];
	}
	return res;
}

void link(int x, int y) {
	int tmp = getdist(x) ^ getdist(y) ^ 1;
	x = getpa(x); y = getpa(y);
	if (rk[x] < rk[y]) swap(x, y);
	if (rk[x] == rk[y]) { rk[x]++; stk[++top] = -x; }
	pa[y] = x; val[y] = tmp; stk[++top] = y;
}

void del(int bot) {
	int x;
	while (top != bot) {
		x = stk[top--];
		if (x > 0) pa[x] = x;
		else rk[-x]--;
	}
}

void solve(int l, int r, vector<int> &p) {
	int mid = (l + r) >> 1, u, v, bot = top;
	vector<int> L, R;
	rep (i, 0, p.size()-1) {
		if (a[p[i]].s <= l && r <= a[p[i]].t) {
			u = a[p[i]].u; v = a[p[i]].v;
			if (getpa(u) == getpa(v)){
				if (!(getdist(u) ^ getdist(v))) {
					del(bot); return;
				}
			}
			else link(u, v);
		}
		else {
			if (!(a[p[i]].t < l || mid < a[p[i]].s)) L.push_back(p[i]);
			if (!(a[p[i]].t < mid+1 || r < a[p[i]].s)) R.push_back(p[i]);
		}
  }
	if (l == r) { ans[l] = 1; del(bot); return; }
	solve(l, mid, L); solve(mid+1, r, R);  del(bot);
}

int main() {
	n = read(); m = read(); T = read();
	rep (i, 1, m) {
		a[i].u = read(); a[i].v = read();
		a[i].s = read()+1; a[i].t = read();
		p.push_back(i);
	}
	rep (i, 1, n) { pa[i] = i; rk[i] = 1; }
	solve(1, T, p);
	rep (i, 1, T) puts(ans[i] ? "Yes" : "No");
	return 0;
}
