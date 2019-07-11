#include <bits/stdc++.h>
using namespace std;
const int N = 1010;
char lx[N];

int main() {
	scanf("%s", lx + 1);
	int len = strlen(lx + 1), pos = 0, tmp = 0;
	for(int i = 1; i <= len; ++i) {
		if(lx[i] == '0') {
			printf("1 %d\n", pos + 1);
			pos = (pos + 1) % 4;
		} else {
			printf("3 %d\n", tmp * 2 + 1);
			tmp = (tmp + 1) % 2;
		}
	}
	return 0;
}