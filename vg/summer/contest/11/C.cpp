#include <bits/stdc++.h>
using namespace std;
const int N = 7010;
int a[N], cnt = 0;
char lx[N], ll[N];

void fail() {
	printf("-1\n");
	exit(0);
}

int n;

void get(int x) {
	if(!x) return ;
	a[++cnt] = x;
	reverse(lx, lx + n), reverse(lx + x, lx + n);
}

int main() {
	scanf("%d%s%s", &n, lx, ll);
	for(int i = 0; i < n; ++i) {
		int j = i;
		for(;j < n; ++j) {
			if(lx[j] == ll[n - i - 1]) break;
		}
		if(j >= n) fail();
		get(n), get(j), get(1);
	}
	printf("%d\n", cnt);
	for(int i = 1; i <= cnt; ++i) {
		printf("%d ", a[i]);
	}
	return 0;
}