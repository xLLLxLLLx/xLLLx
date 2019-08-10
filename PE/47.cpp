#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 1;
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

bool check(int x) {
	int num = 0;
	for(int i = 1; i <= pr[0]; ++i) {
		if(x % pr[i] == 0) {
			num++;
			while(x % pr[i] == 0) {
				x /= pr[i];
			}
		}
		if(x == 1) {
			break;
		}
	}
	return num == 4;
}

int main() {
	init();
	for(int i = 1; ; ++i) {
		int flg = 1;
		for(int j = 0; j <= 3; ++j) {
			if(!check(i + j)) {
				flg = 0;
				break;
			}
		}
		if(flg) {
			printf("%d\n", i);
			return 0;
		}
	}
	return 0;
}