#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e8 + 1, M = 1e7 + 1;
const ll mod = (1ll << 32);
bool flg[N];
int pr[M];

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
}

int main() {
	int T;
	scanf("%d", &T);
	init();
	for(int o = 1; o <= T; ++o) {
		int n;
		scanf("%d", &n);
		ll ans = 1;
		for(int i = 1; i <= pr[0]; ++i) {
			ll pos = 1ll * pr[i];
			int num = 0;
			for(int j = 1; ; ++j) {
				if(pos > n) {
					pos /= pr[i];
					break;
				}
				pos *= 1ll * pr[i];
			}
			ans = ans * pos % mod;
		}
		printf("Case %d: %lld\n", o, ans);
	}
	return 0;
}