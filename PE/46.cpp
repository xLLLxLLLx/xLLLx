#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 1;
bool flg[N];
int pr[N];

bool check(int x) {
	if(x & 1) return false;
	x /= 2;
	int len = sqrt(x);
	return len * len == x;
}

void init() {
	for(int i = 2; i < N; ++i) {
		if(!flg[i])
			pr[++pr[0]] = i;
		else if(i & 1){
			int f = 0;
			for(int j = 1; j <= pr[0]; ++j) {
				if(check(i - pr[j]))
					f = 1;
			}
			if(!f) {
				printf("%d\n", i);
				exit(0);
			}
		}	
		for(int j = 1; j <= pr[0]; ++j) {
			if(i * pr[j] >= N) break;
			flg[i * pr[j]] = 1;
			if(i % pr[j] == 0) break;
		}
	}
}

int main() {
	init();
	return 0;
}