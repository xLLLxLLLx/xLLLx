#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
char lx[N];

int main() {
	int T;
	scanf("%d", &T);
	for(int o = 1; o <= T; ++o) {
		scanf("%s", lx + 1);
		int len = strlen(lx + 1), flg = 0;
		for(int i = 1; i <= len; ++i) {
			if(lx[i] == '1') {
				flg ^= 1;
			} 
		}
		if(flg) {
			printf("WIN\n");
		} else {
			printf("LOSE\n");
		}
	}
	return 0;
}