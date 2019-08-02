#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 2e5 + 10, LOG = 20;
int st[N][LOG + 1], a[N], L[N];

int get(int l, int r) {
	int k = (int)(log(double(r - l + 1)) / log(2.0));
	return max(st[l][k], st[r - (1 << k) + 1][k]);
}

int main() {
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
		L[i] = 1;
	}
	int q;
	scanf("%d", &q);
	for(int i = 1; i <= q; ++i) {
		int tp;
		scanf("%d", &tp);
		if(tp == 1) {
			int x, y;
			scanf("%d%d", &x, &y);
			a[x] = y;
			L[x] = i;
		} else {
			int x;
			scanf("%d", &x);
			st[i][0] = x;
		}
	}
	for(int j = 1; j <= LOG; ++j)
		for(int i = 1; i <= q; ++i) {
			if(i + (1 << j) > q + 1) {
				continue;
			}
			st[i][j] = max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
		}
	for(int i = 1; i <= n; ++i) {
		a[i] = max(a[i], get(L[i] ,q));
		printf("%d ", a[i]);
	}
	return 0;
}