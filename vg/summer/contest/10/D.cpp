#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 4e5 + 10, M = 1e5 + 10;
struct data {
	int x, y;
} a[M][2];
int num[2];
int bmax[N], bmin[N], amax[N], amin[N];

int add = 2e5;
ll ans = 0;

void Min(int &x, int y) {
	x = min(x, y);
}

void Max(int &x, int y) {
	x = max(x, y);
}

void work(int now) {
	memset(bmin, 0x3f, sizeof bmin);
	memset(amin, 0x3f, sizeof amin);
	memset(bmax, 0, sizeof bmax);
	memset(amax, 0, sizeof amax);
	for(int i = 1; i <= num[now]; ++i) {
		Min(bmin[a[i][now].x], a[i][now].y);
		Min(amin[a[i][now].x], a[i][now].y);
		Max(bmax[a[i][now].x], a[i][now].y);
		Max(amax[a[i][now].x], a[i][now].y);
	}
	for(int i = 1; i < N; ++i) {
		Min(bmin[i], bmin[i - 1]);
		Max(bmax[i], bmax[i - 1]);
	}
	for(int i = N - 2; i >= 0; --i) {
		Min(amin[i], amin[i + 1]);
		Max(amax[i], amax[i + 1]);
	}
	for(int i = 1; i < N; i += 2) {
		int pos = min(bmax[i], amax[i]);
		int tmp = max(bmin[i], amin[i]);
		if(pos > tmp) ans += 1ll * (pos - tmp) / 2;
	}
}

int main() {
	int n;
	scanf("%d", &n);
	for(int i = 1, x, y; i <= n; ++i) {
		scanf("%d%d", &x, &y);
		int pos = (x + y + add) & 1;
		a[++num[pos]][pos].x = x + y + add + pos;
		a[num[pos]][pos].y = x - y + add + pos; 
	}
	for(int i = 0; i < 2; ++i) {
		work(i);
		// printf("%lld\n", ans);
	}
	printf("%lld\n", ans);
	return 0;
}