#include <bits/stdc++.h>
using namespace std;
int a[20];

int main() {
	int pos = 1, ans = 0;
	a[1] = 31, a[2] = 28, a[3] = 31, a[4] = 30;
	a[5] = 31, a[6] = 30, a[7] = 31, a[8] = 31;
	a[9] = 30, a[10] = 31, a[11] = 30, a[12] = 31;
	for(int i = 1900; i <= 2000; ++i) {
		int tag = 0;
		if(i % 4 == 0 && (i % 100)) tag = 1;
		if(i % 400 == 0) tag = 1;
		for(int j = 1; j <= 12; ++j) {
			if(!pos && i > 1900) ++ans;
			pos += a[j];
			if(j == 2) pos += tag;
			pos %= 7;
		}
	}
	printf("%d\n", ans);
	return 0;
}