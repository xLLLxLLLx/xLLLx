#include <bits/stdc++.h>
using namespace std;
const int N = 1e4 + 10;
int flg[N], pr[N];

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

int nm[10], nx[10], ny[10];

bool check(int x, int y, int z) {
	// printf("%d %d %d\n", x, y, z);
	memset(nm, 0, sizeof nm);
	memset(nx, 0, sizeof nx);
	memset(ny, 0, sizeof ny);
	for(;x;x /= 10) nm[x % 10]++;
	for(;y;y /= 10) nx[y % 10]++;
	for(;z;z /= 10) ny[z % 10]++;
	for(int i = 0; i <= 9; ++i) {
		if(nm[i] != nx[i] || nm[i] != ny[i])
			return false;
	}
	return true;
}

int main() {
	init();
	int maxn = 1e4;
	for(int i = 1; i <= pr[0]; ++i) {
		if(pr[i] < 1000 || pr[i] >= maxn) continue;
		for(int j = 1; j <= maxn; ++j) {
			if(pr[i] + 2 * j >= maxn) break;
			if(flg[pr[i] + j] || flg[pr[i] + j + j]) continue;
			if(check(pr[i], pr[i] + j, pr[i] + j + j)) {
				printf("%d%d%d\n", pr[i], pr[i] + j, pr[i] + j +j);
			}
		}
	}
	return 0;
}