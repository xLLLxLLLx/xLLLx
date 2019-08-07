#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 2e5 + 10;
int a[N];
int n, k;

int get(ll x) {
	int l = 1, r = n, ans = n;
	while(l <= r) {
		int mid = (l + r) >> 1;
		if(a[mid] <= x)
			ans = mid, l = mid + 1;
		else 
			r = mid - 1;
	}
	return ans;
}

bool check(ll x) {
	ll pos = 0;
	int id = get(x);
	for(int i = id; i >= (n + 1) / 2; --i)
		pos += x - a[i];
	return pos <= k;
}

int main() {
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
	}
	sort(a + 1, a + 1 + n);
	ll l = a[(n + 1) / 2], r = 2e9, ans = 0;
	while(l <= r) {
		ll mid = (l + r) >> 1;
		if(check(mid))
			l = mid + 1, ans = mid;
		else
			r = mid - 1;
	}
	printf("%lld\n", ans);
	return 0;
}