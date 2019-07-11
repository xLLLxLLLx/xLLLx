#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 2e5 + 10;
int x[N];
ll a[N], b[N];

void fail() {
	printf("No\n");
	exit(0);
}

int main() {
	int n;
	ll t;
	scanf("%d%lld", &n, &t);
	for(int i = 1; i <= n; ++i) {
		scanf("%lld", &a[i]);
	}
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &x[i]);
	}
	for(int i = 2; i <= n; ++i) {
		if(x[i] < i || x[i] < x[i - 1]) {
			fail();
		}
	}
	for(int i = 1; i <= n; ++i) {
		int r = n;
		for(int j = i; j <= n; ++j) {
			if(x[j] != x[i]) {
				r = j - 1;
				break;
			}
		}
		for(int j = i; j <= r; ++j) {
			if(x[j] != j) b[j] = a[j + 1] + t;
			else b[j] = max(b[j - 1] + 1, a[j] + t);
		}
		if(x[x[i]] != x[i] || (r != n && b[r] >= a[r + 1] + t)) fail();
		i = r;
	}
	printf("Yes\n");
	for(int i = 1; i <= n; ++i) {
		printf("%lld ", b[i]);
	}
	return 0;
}