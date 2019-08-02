#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 4e5 + 10;
struct data {
	int x, y;
} a[N];
int b[N];
int dx[4] = {0, 1, 0, 1};
int dy[4] = {1, 0, 0, 1};
int d[4][4][4], qz[4][N], cnt[4][N][2];

int main() {
	freopen("integral.in", "r", stdin);
	freopen("integral.out", "w", stdout);
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		scanf("%d%d", &a[i].x, &a[i].y);
		a[i].x = max(a[i].x, -a[i].x);
		a[i].y = max(a[i].y, -a[i].y);
		a[i].x %= 2, a[i].y %= 2;
		for(int j = 0; j < 4; ++j) 
			if(a[i].x == dx[j] && a[i].y == dy[j]) b[i] = j;
	}
	for(int i = 0; i < 4; ++i)
		for(int j = 0; j < 4; ++j) 
			for(int k = 0; k < 4; ++k) {
				d[k][i][j] = abs((dx[i] - dx[k]) * (dy[j] - dy[k]) - (dx[j] - dx[k]) * (dy[i] - dy[k])) % 2;
		}
	int tot = 0;
	for(int i = 3; i <= n; ++i) {
		tot += d[b[1]][b[i - 1]][b[i]];
		tot %= 2;
	}
	if(tot) {
		return printf("0\n"), 0;
	}
	for(int i = 1; i <= n; ++i) b[i + n] = b[i];
	for(int i = 0; i < 4; ++i) {
		for(int j = 2; j <= n * 2; ++j) {
			qz[i][j] = qz[i][j - 1];
			cnt[i][j][0] = cnt[i][j - 1][0];
			cnt[i][j][1] = cnt[i][j - 1][1];
			qz[i][j] += d[i][b[j]][b[j - 1]];
			qz[i][j] %= 2;
			cnt[i][j][qz[i][j]]++;
		}
	}
	ll ans = 0;
	for(int i = 1; i <= n; ++i) {
		int tp = b[i];
		int pos = qz[tp][i + 1];
		ans += cnt[tp][n + i - 2][pos] - cnt[tp][i + 1][pos];
	}
	printf("%lld\n", ans / 2);
	return 0;
}