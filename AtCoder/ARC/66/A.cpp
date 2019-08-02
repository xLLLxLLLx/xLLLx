#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e5 + 10, mod = 1e9 + 7;
int a[N];

int main() {
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) a[abs(n - i - (i - 1))]++;
	for(int i = 1, x; i <= n; ++i) {
		scanf("%d", &x);
		a[x]--;
		if(a[x] < 0) return printf("0\n"), 0;
	}
	ll pos = 1;
	for(int i = 1; i <= n / 2; ++i) pos = pos * 2 % mod;
	printf("%lld\n", pos);
	return 0;
}