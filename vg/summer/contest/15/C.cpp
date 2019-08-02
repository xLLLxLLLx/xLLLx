#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int a[N];

void even() {
	printf("once again\n");
	exit(0);
}

void xs() {
	printf("tokitsukaze\n");
	exit(0);
}

void hs() {
	printf("quailty\n");
	exit(0);
}

int main() {
	int n, k;
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= n; ++i) {
		scanf("%1d", &a[i]);
	}
	if(k + 1 >= n) xs();
	else {
		int l = 1, r = n;
		for(int i = 2; i <= n; ++i) {
			if(a[i] != a[1]) break;
			l = i;
		}
		for(int i = n; i >= 1; --i) {
			if(a[i] != a[n]) break;
			r = i;
		}
		if(a[1] == a[n] && (r - l - 1) <= k) xs();
		else if(max(l, n - r + 1) + k >= n) xs();
	} 
	if(a[1] != a[n]) {
		int l = 1, r = n;
		for(int i = 2; i <= n; ++i) {
			if(a[i] != a[1]) break;
			l = i;
		}
		for(int i = n; i >= 1; --i) {
			if(a[i] != a[n]) break;
			r = i;
		}
		// printf("%d %d\n", l, r);
		if(k * 2 >= n && 1 + k >= r - 1 && n - k <= l + 1) hs();
	}
	even();
	return 0;
}