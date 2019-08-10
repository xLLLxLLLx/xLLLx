#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int a[N], b[N];
char lx[N], ll[N];

int main() {
	int T;
	scanf("%d", &T);
	for(int o = 1; o <= T; ++o) {
		a[0] = 0, b[0] = 0;
		scanf("%s%s", lx + 1, ll + 1);
		int len = strlen(lx + 1), n = strlen(ll + 1);
		for(int i = len; i >= 1; --i) {
			if(lx[i] == '1') {
				a[++a[0]] = len - i + 1;
			}
		}
		for(int i = n; i >= 1; --i) {
			if(ll[i] == '1') {
				b[++b[0]] = n - i + 1;
			}
		}
		if(!a[0] || !b[0]) {
			printf("0\n");
			continue;
		} else {
			for(int i = 1; i <= a[0]; ++i) {
				if(a[i] >= b[1]) {
					printf("%d\n", a[i] - b[1]);
					break;
				}
			}
		}
	}
	return 0;
}