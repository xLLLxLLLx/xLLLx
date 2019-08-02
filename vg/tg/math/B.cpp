#include <bits/stdc++.h>
using namespace std;
const int N = 5e6 + 10, M = 5e5 + 10;
unsigned long long qz[N];
int pr[M], phi[N];

typedef unsigned long long ull;

void init() {
	for(int i = 2; i < N; ++i) {
		if(!phi[i]) {
			pr[++pr[0]] = i;
			phi[i] = i - 1;
		}
		for(int j = 1; j <= pr[0]; ++j) {
			if(pr[j] * i >= N) break;
			if(i % pr[j] == 0) {
				phi[i * pr[j]] = phi[i] * pr[j];
				break;
			} else {
				phi[i * pr[j]] = phi[i] * (pr[j] - 1);
			}
		}
	}
	qz[1] = 0;
	for(int i = 2; i < N; ++i) {
		qz[i] = qz[i - 1] + (ull)phi[i] * phi[i];
	}
}

int main() {
	int T;
	scanf("%d", &T);
	init();
	for(int o = 1; o <= T; ++o) {
		int l, r;
		scanf("%d%d", &l, &r);
		printf("Case %d: %llu\n", o, qz[r] - qz[l - 1]);
	}
	return 0;
}