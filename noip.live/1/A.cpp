#include <bits/stdc++.h>
using namespace std;
const int N = 25;
struct data {
	int x, y;
} c[N];
int n, flg = 0, minn = 14, maxn = 0;
int nm[N], a[N], b[N], d[N], p[N];

bool cmp(data A, data B) {
	return A.x == B.x ? A.y < B.y : A.x < B.x;
}

bool upd() {
	if(!flg) return true;
	for(int i = 1; i <= 2 * n; ++i) {
		if(p[i] < d[i]) return true;
		else if(p[i] > d[i]) return false;
	}
	return false;
}

void check() {
	memset(nm, 0, sizeof nm);
	for(int i = 1; i <= n; ++i) {
		nm[b[i]]++, nm[a[i]]++;
		c[i].x = b[i], c[i].y = a[i];
	}
	for(int i = 1; i <= n; ++i) {
		if(nm[a[i]] != b[i]) return ;
	}
	sort(c + 1, c + 1 + n, cmp);
	int now = 0;
	for(int i = 1; i <= n; ++i)
		p[++now] = c[i].x, p[++now] = c[i].y;
	if(upd()) {
		for(int i = 1; i <= 2 * n; ++i) {
			d[i] = p[i];
		}
	}
	flg = 1;
}

void go(int dep, int now) {
	if((n - dep + 1) * minn > now || (n - dep + 1) * maxn < now) return ;
	if(dep == n) {
		b[dep] = now;
		check();
		return ;
	}
	for(int i = 1; i <= n; ++i) {
		if(!a[i]) continue;
		b[dep] = a[i];
		go(dep + 1, now - a[i]);
	}
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
		maxn = max(maxn, a[i]);
		if(a[i]) minn = min(minn, a[i]);
	}
	if(n == 1) {
		if(a[1] != 2) printf("-1\n");
		else printf("22\n");
		return 0;
	}
	sort(a + 1, a + 1 + n);
	go(1, 2 * n);
	if(!flg) printf("-1\n");
	else {
		for(int i = 1; i <= 2 * n; ++i)
			printf("%d", d[i]);
		puts("");
	}
	return 0;
}