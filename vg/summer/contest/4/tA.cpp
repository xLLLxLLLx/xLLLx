#include <bits/stdc++.h>
using namespace std;
const int N = 1010;
char lx[N], ll[N];

int main() {
	scanf("%s%s", lx + 1, ll + 1);
	int lenx = strlen(lx + 1);
	int lenl = strlen(ll + 1);
	int pos = 0, tmp = 0;
	for(int i = 1; i <= lenx; ++i) {
		pos += (lx[i] == '1');
	}
	for(int i = 1; i <= lenl; ++i) {
		tmp += (ll[i] == '1');
	}
	if(pos & 1) pos++;
	if(pos >= tmp) {
		printf("YES\n"); 
	} else {
		printf("NO\n");
	}
	return 0;
}