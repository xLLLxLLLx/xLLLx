#include <bits/stdc++.h>
#define ll long long
using namespace std;

bool check(ll x) {
	ll len = sqrt(x);
	int res = 0;
	for(ll i = 1; i <= len; ++i) {
		if(x % i == 0) {
			res ++;
			if(i * i != x) res++;
		}
	}
	return res >= 500;
}

int main() {
	ll now = 0;
	for(int i = 1; i; ++i) {
		now += i;
		if(check(now)) {
			printf("%lld\n", now);
		}
	}
	return 0;
}