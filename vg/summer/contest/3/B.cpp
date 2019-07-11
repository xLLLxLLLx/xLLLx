#include <bits/stdc++.h>
using namespace std;
char lx[2], ll[10];

bool ask(int x, int y) {
	printf("? %d %d\n", x, y);
	fflush(stdout);
	scanf("%s", lx + 1);
	return lx[1] == 'x';
}

void print(int x) {
	printf("! %d\n", x);
	fflush(stdout);
}

int main() {
	while(scanf("%s", ll + 1)) {
		if(ll[1] == 'e') {
			break;
		}
		int l, r;
		for(int i = 0; ; ++i) {
			if(ask(1 << i, 1 << (i + 1))) {
				l = (1 << i) - 1, r = 1 << (i + 1);
				break;
			}
		}
		while(l + 1 < r) {
			int mid = (l + r) >> 1;
			if(ask(l, mid)) {
				r = mid;
			} else {
				l = mid;
			}
		}
		print(l + 1);
	}
	return 0;
}