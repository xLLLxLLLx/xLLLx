#include <bits/stdc++.h>
using namespace std;
const int N = 110;
char lx[N];

int main() {
	int n;
	scanf("%d", &n);
	scanf("%s", lx + 1);
	int pos = 0, tmp = 0;
	for(int i = 1; i <= n; ++i) {
		if(lx[i] == '1') pos++;
		else tmp++;
	}
	if(pos != tmp) {
		printf("1\n");
		for(int i = 1; i <= n; ++i) {
			cout<<lx[i];
		}
	} else {
		int tt = 0, uu = 0;
		for(int i = 1; i <= n; ++i) {
			if(lx[i] == '1') tt++, pos--;
			else uu++, tmp--;
			if(tt!=uu || pos!=tmp) {
				printf("2\n");
				for(int j = 1; j <= i; ++j) {
					cout<<lx[j];
				}
				printf(" ");
				for(int j = i + 1; j <= n; ++j) {
					cout<<lx[j];
				}
				return 0;
			}
		}
	}
	return 0;
}