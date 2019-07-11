#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e5 + 10;
int a[N],b[N];

int main() {
	int T;
	scanf("%d", &T);
	ll ans = 0, pos = 0;
	for(int o = 1; o <= T; ++o) {
		double x;
		cin >> x;
		a[o] = (int)x;
		if(x > 0) {
			if(x > a[o]) {
				b[o] = 1;
			}
		} else if(x < 0) {
			if(x < a[o]) {
				a[o]--;
				b[o] = 1;
			}
		}
		ans += a[o];
		pos += b[o];
	}
	ll tmp = -ans;
	for(int i = 1; i <= T; ++i) {
		if(tmp) {
			printf("%d\n", a[i] + b[i]);
			tmp -= b[i];
		} else {
			printf("%d\n", a[i]);
		}
	}
	return 0;
}