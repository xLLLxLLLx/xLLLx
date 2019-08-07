#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 2e6 + 1, M = 2e5 + 1;
int pr[M];
bool flg[N];

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
	ll ans = 0;
	for(int i = 1; i <= pr[0]; ++i)
		ans += pr[i];
	printf("%lld\n", ans);
}

int main() {
	init();
	return 0;
}