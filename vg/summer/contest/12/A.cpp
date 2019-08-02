#include <bits/stdc++.h>
using namespace std;
const int N = 2010;
int a[N], qz[N][3], mx[N];

int main() {
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
		qz[i][1] = qz[i - 1][1];
		qz[i][2] = qz[i - 1][2];
		qz[i][a[i]]++;
	}
	int ans = 0;
	for(int i = 0; i <= n; ++i) {
		ans = max(ans, qz[i][1] + qz[n][2] - qz[i][2]);
		if(i) mx[i] = max(mx[i - 1], qz[i][1] - qz[i][2]);
	}
	// printf("%d\n", ans);
	for(int i = 1; i <= n; ++i) {
		int now = 0;
		for(int j = i; j >= 1; --j) {
			now += (a[j] == 1);
			ans = max(ans, now + mx[j - 1] + qz[j - 1][2] + qz[n][2] - qz[i][2]);
		}
	}
	printf("%d\n", ans);
	return 0;
}