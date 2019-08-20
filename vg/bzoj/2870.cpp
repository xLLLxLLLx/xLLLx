#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 5e4 + 10, inf = 1e9;
struct data {
	int nt, to, W;
}a[2][N * 10];
int n, now = 0;
int head[2][N * 10], cnt[2], w[N];

template <class T>
void read(T &x) {
	char ch = getchar(); x = 0;
	for(; ch < '0' || ch > '9'; ch = getchar()) ;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
}

void adde(int id, int x, int y, int W) {
	a[id][++cnt[id]].to = y;
	a[id][cnt[id]].W = W;
	a[id][cnt[id]].nt = head[id][x];
	head[id][x] = cnt[id];
}

void add(int id, int x, int y, int W) {
	adde(id, x, y, W), adde(id, y, x, W);
}

void predfs(int u, int fa) {
	// printf("%d %d\n", u, fa);
	int last = u;
	for(int i = head[0][u]; ~i; i = a[0][i].nt) {
		int to = a[0][i].to;
		if(to == fa) continue;
		predfs(to, u);
		add(1, last, ++now, 0);
		add(1, now, to, 1);
		last = now;
		w[now] = w[u];
	}
}

struct node {
	int val, num;
} b[N * 10], c[N * 10];
int res = 0, tmp = 0;

int bu, bv, bid, mx, tot;
int us[N * 10], sz[N * 10];
ll ans = 0;

bool cmp(node A, node B) {
	return A.val < B.val;
}

void gotsz(int x, int fa) {
	sz[x] = 1;
	for(int i = head[1][x]; ~i; i = a[1][i].nt) {
		int to = a[1][i].to;
		if(us[i >> 1] || to == fa) {
			continue;
		}
		gotsz(to, x);
		sz[x] += sz[to];
		int pos = min(tot - sz[to], sz[to]);
		if(mx < pos) {
			bu = x, bv = to, bid = i;
			mx = pos;
		}
	}
}

void gotpoint(int u, int fa, int val, int num) {
	if(u <= n) {
		b[++res] = (node){val, num};
	}
	for(int i = head[1][u]; ~i; i = a[1][i].nt) {
		int to = a[1][i].to;
		if(to == fa || us[i >> 1]) continue;
		gotpoint(to, u, min(val, w[to]), num + a[1][i].W);
	}
}

int nm[N];

void go(int x, int size) {
	if(size == 1) {
		return ;
	}
	tot = size, mx = bu = bv = 0;
	gotsz(x, 0);
	int x1 = bv, s1 = sz[bv], x2 = bu, s2 = tot - s1;
	us[bid >> 1] = 1;
	res = 0, gotpoint(x1, 0, w[x1], 0);
	for(int i = 1; i <= res; ++i) c[i] = b[i];
	tmp = res;
	res = 0, gotpoint(x2, 0, w[x2], 0);
	sort(b + 1, b + 1 + res, cmp), sort(c + 1, c + 1 + tmp, cmp);
	nm[res + 1] = 0;
	for(int i = res; i >= 1; --i)
		nm[i] = max(nm[i + 1], b[i].num);
	int l = 1;
	for(int i = 1; i <= tmp; ++i) {
		while(l <= res && b[l].val < c[i].val) l++;
		if(l <= res) {
			ans = max(ans, 1ll * (nm[l] + c[i].num + 1 + a[1][bid].W) * c[i].val);
		} else {
			break;
		}
	}
	go(x1, s1);
	go(x2, s2);
}

int main() {
	for(int i = 0; i < 2; ++i) {
		cnt[i] = -1;
		memset(head[i], -1, sizeof head[i]);
	}
	read(n), now = n;
	for(int i = 1; i <= n; ++i) {
		read(w[i]);
		ans = max(ans, (long long)w[i]);
	}
	for(int i = 1, x, y; i < n; ++i) {
		read(x), read(y);
		add(0, x, y, 0);
	}
	predfs(1, 0);
	go(1, now);
	printf("%lld\n", ans);
	return 0;
}