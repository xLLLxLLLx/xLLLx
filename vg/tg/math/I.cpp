#include <bits/stdc++.h>
#define ll long long
const int N = 1e7 + 1, M = 1e6 + 1;
bool flg[N];
int pr[M], nm[25];

void init() {
	for(int i = 2; i < N; ++i) {
		if(!flg[i])
			pr[++pr[0]] = i;
		for(int j = 1; j <= pr[0]; ++j) {
			if(i * pr[j] >= N) break;
			flg[i * pr[j]] = 1;
			if(i % pr[j] == 0) break;
		}
	}
	// printf("%d\n", pr[0]);
}

int main() {
	init();
	int T;
	scanf("%d", &T);
	for(int o = 1; o <= T; ++o) {
		ll x, pos = 1;
		scanf("%lld", &x);
		for(int i = 1; i <= pr[0]; ++i) {
			if(x % pr[i] == 0) {
				int res = 0;
				while(x % pr[i] == 0) {
					x /= pr[i];
					res++;
				}
				pos *= (2ll * res + 1);
			}
			if(x == 1)
				break;
		}
		if(x > 1) {
			pos *= 3ll;
		}
		pos = (pos + 1) / 2;
		printf("Case %d: %lld\n", o, pos);
	}
	return 0;
}