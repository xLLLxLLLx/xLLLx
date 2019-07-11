#include <bits/stdc++.h>
#define ll long long
using namespace std;
char lx[10];

bool ask(ll l, ll r) {
	printf("%lld %lld\n", l, r);
	fflush(stdout);
	scanf("%s", lx + 1);
	if(lx[1] == 'Y') {
		if(l == r) exit(0);
		return true;
	} else {
		return false;
	}
}

int main() {
	srand(time(NULL));
	ll n, k;
	cin >> n >> k;
	ll l = 1, r = n;
	for(; l <= r;) {
		ll mid = (l + r) >> 1;
		if(ask(l, mid)) {
			r = mid;
		} else {
			l = mid + 1;
		}
		l = max(1ll, l - k);
		r = min(n, r + k);
		mid = l + rand() % (r - l + 1);
		ask(mid, mid);
		l = max(1ll, l - k);
		r = min(n, r + k);
	}
	return 0;
}