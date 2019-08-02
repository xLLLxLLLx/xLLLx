#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e6 + 10, mod = 1e6 + 3;
ll a[N];

int main() {
	int n;
	a[1] = 1;
	for(int i = 2; i < N; ++i)
		a[i] = a[i - 1] * i % mod;
	while(scanf("%d", &n) == 1) {
		if(n >= mod) puts("0");
		else {
			printf("%lld\n", a[n]);
		}
	}
	return 0;
}