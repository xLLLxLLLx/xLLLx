#include<bits/stdc++.h>
using namespace std;
const int N = 110;
int a[N];

int main() {
	int n, h, m;
	scanf("%d%d%d", &n, &h, &m);
	for(int i = 1; i <= n; ++i) {
		a[i]=h;
	}
	for(int i = 1; i <= m; ++i) {
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		for(int j = x; j <= y; ++j) {
			a[j] = min(a[j], z);
		}
	}
	int ans = 0;
	for(int i = 1; i <= n; ++i) {
		ans += a[i] * a[i];
	}
	printf("%d\n", ans);
	return 0;
}