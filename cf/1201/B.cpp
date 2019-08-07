#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main() {
	int n;
	scanf("%d", &n);
	int pos = 0;
	ll maxn = 0, sum = 0;
	for(int i = 1, x; i <= n; ++i) {
		scanf("%d", &x);
		maxn = max(maxn, 1ll * x);
		sum += x;
		pos ^= (x & 1);
	}
	if(pos || maxn * 2 > sum) {
		printf("NO\n");
	} else {
		printf("YES\n");
	}
	return 0;
}