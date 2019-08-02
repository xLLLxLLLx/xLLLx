#include <bits/stdc++.h>
#define ll long long
using namespace std;

void get(ll x) {
	int pos = sqrt(x);
	if(1ll * pos * pos == x) {
		if(pos & 1) {
			printf("1 %d\n", pos);
		} else {
			printf("%d 1\n", pos);
		}
		return ;
	}
	int yu = x - 1ll * pos * pos;
	if(pos & 1) {
		if(yu <= pos) {
			printf("%d %d\n", yu, pos + 1);
		} else {
			printf("%d %d\n", pos + 1, 2 * pos - yu + 2);
		}
	} else {
		if(yu <= pos) {
			printf("%d %d\n", pos + 1, yu);
		} else {
			printf("%d %d\n", 2 * pos - yu + 2, pos + 1);
		}
	}
}

int main() {
	int T;
	scanf("%d", &T);
	for(int o = 1; o <= T; ++o) {
		ll x;
		scanf("%lld", &x);
		printf("Case %d: ", o);
		get(x);
	}
	return 0;
}