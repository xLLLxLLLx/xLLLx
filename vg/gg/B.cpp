#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;
char lx[N], ll[N];

int main() {
	scanf("%s%s", lx + 1, ll + 1);
	int lenx = strlen(lx + 1);
	int lenl = strlen(ll + 1);
	int pos = 0, tmp = 0, ans = 0;
	for(int i = 1; i <= lenl; ++i) {
		if(ll[i] == '1') {
			pos ^= 1;
		}
		if(lx[i] == '1') {
			tmp ^= 1;
		}
	}
	if(pos == tmp) {
		ans++;
	}
	for(int i = 2; i <= lenx - lenl + 1; ++i) {
		if(lx[i - 1] == '1') {
			tmp ^= 1;
		}
		if(lx[i + lenl - 1] == '1') {
			tmp ^= 1;
		}
		if(tmp == pos) {
			ans++;
		}
	}
	printf("%d\n", ans);
	return 0;
}