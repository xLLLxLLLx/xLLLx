#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e6 + 10;
bool flg[N];
int pr[N];
ll qz[N];

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
	init();
	int maxn = 0, ans = 0,sum = 0, INF = 1e6;
	for(int i = 1; i <= pr[0]; ++i) {
		qz[i] = qz[i - 1];
		qz[i] += pr[i];
		for(int j = 0; j <= i; ++j) {
			ll pos = qz[i] - qz[j];
			if(pos <= INF && !flg[pos]) {
				if(maxn < i - j) {
					maxn = i - j;
					ans = pos;
				}
			}
		}
	}
	printf("%d\n", ans);
	return 0;
}