#include <bits/stdc++.h>
using namespace std;
const int N = 20;
int a[N], b[N], na[N], nb[N], cnt[N], ans = 0;

int zh(char ch) {
	if(ch >= '4' && ch <= '9') return ch - '3';
	if(ch == 'T') return 7;
	if(ch == 'J') return 8;
	if(ch == 'Q') return 9;
	if(ch == 'K') return 10;
	if(ch == 'A') return 11;
	if(ch == '2') return 12;
	if(ch == 'w') return 13;
	if(ch == 'W') return 14;
}

int c[N], d[N];

bool check(int x, int y) {
	for(int t = 0; t <= x; ++t) {
		int n = t, m = x + y - t;
		for(int i = 1; i <= 14; ++i) d[i] = b[i];
		for(int i = 14; i >= 1; --i) {
			while(n && d[i] >= 2) d[i] -= 2, n--;
			while(m && d[i] >= 1) d[i]--, m--;
		}
		if(n || m) continue;
		n = t, m = x + y - t;
		for(int i = 1; i <= 14; ++i) c[i] = a[i];
		for(int i = 1; i <= 14; ++i) {
			while(n && c[i] >= 2) c[i] -= 2, n--;
			while(m && c[i] >= 1) c[i]--, m--;
		}
		if(n || m) continue;
		int res = 0, flg = 1;
		for(int i = 1; i <= 14; ++i) {
			if(res < c[i]) {
				flg = 0;
				break;
			}
			res -= c[i], res += d[i];
		}
		if(flg) return true;
	}
	return false;
}

bool check(int dep, int A, int B, int th, int fo) {
	if(dep > 14) {
		return !th && !fo && check(A, B);
	}
	if(b[dep] >= 3) {
		b[dep] -= 3;
		int pos = check(dep + 1, A + 1, B, th + 1, fo);
		if(pos) return true;
		b[dep] += 3;
	}
	if(b[dep] >= 4) {
		b[dep] -= 4;
		int pos = check(dep + 1, A, B + 2, th, fo + 1);
		if(pos) return true;
		b[dep] += 4;
	}
	if(a[dep] >= 3 && th) {
		a[dep] -= 3;
		int pos = check(dep + 1, A, B, th - 1, fo);
		if(pos) return true;
		a[dep] += 3;
	}
	if(a[dep] >= 4 && fo) {
		a[dep] -= 4;
		int pos = check(dep + 1, A, B, th, fo - 1);
		if(pos) return true;
		a[dep] += 4;
	}
	return check(dep + 1, A, B, th, fo);
}

int be = 33;

void dfs(int dep, int now) {
	if(now > 17 || now + be < 17) return ;
	if(dep > 14) {
		if(now == 17) {
			for(int i = 1; i <= 14; ++i)
				a[i] = na[i], b[i] = nb[i];
			if(check(1, 0, 0, 0, 0)) ans++;
		}
		return ;
	}
	for(int i = 0; i <= cnt[dep]; ++i) {
		nb[dep] = i;
		be -= cnt[dep];
		dfs(dep + 1, now + i);
		be += cnt[dep];
	}
}

char lx[N];

int main() {
	while(scanf("%s", lx + 1) != EOF) {
		ans = 0;
		memset(na, 0, sizeof na);
		for(int i = 1; i <= 17; ++i) {
			na[zh(lx[i])]++;
		}
		for(int i = 1; i <= 12; ++i) cnt[i] = 4 - na[i];
		cnt[13] = !na[13], cnt[14] = !na[14];
		dfs(1, 0);
		printf("%d\n", ans);
	}
	return 0;
}