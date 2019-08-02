#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e5 + 10;
ll a[N];
ll n, k;
int m;

ll put(ll x) {
	return (x - 1)/ k + 1;
}

int main() {
	cin >> n >> m >> k;
	for(int i = 1; i <= m; ++i) {
		scanf("%lld", &a[i]);
	}
	int ans = 0, last = 0, num = 0;
	for(; last < m;) {
		num = last;
		last++, ans++;
		int i = last;
		for(; i <= m && put(a[i] - num) == put(a[last] - num); ++i);
		// printf("%d %d\n", last, i - 1);
		last = i - 1;
	}
	printf("%d\n", ans);	
	return 0;
}