#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int a[N], sum = 0;

int main() {
	int n;
	cin >>n;
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
		sum += a[i];
	}
	int maxn = 1e9, pos = 0;
	for(int i = 1; i <= n; ++i) {
		pos += a[i];
		sum -= a[i];
		maxn = min(maxn, abs(pos - sum));
	}
	printf("%d\n", maxn);
	return 0;
}