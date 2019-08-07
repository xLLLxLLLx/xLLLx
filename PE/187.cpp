#include <bits/stdc++.h>
using namespace std;
const int N = 1e8 + 1, M = 1e7 + 1;
int pr[M];
bool flg[N];

void init() {
	for(int i = 2; i < N; ++i) {
		if(!flg[i])
			pr[++pr[0]] = i;
		for(int j = 1; j <= pr[0]; ++j) {
			if(1ll * i * pr[j] >= N) break;
			flg[i * pr[j]] = 1;
			if(i % pr[j] == 0) break;
		}
	}
}

int main() {
	init();
	printf("%d\n", pr[0]);
	int r = pr[0], maxn = 1e8;
	int ans = 0;
	for(int i = 1; i <= pr[0]; ++i) {
		while(r && 1ll * pr[i] * pr[r] > maxn) r--;
		if(i <= r) {
			ans += r - i + 1;
		}
	}
	printf("%d\n", ans);
	return 0;
}