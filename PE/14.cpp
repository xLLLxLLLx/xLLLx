#include <bits/stdc++.h>
#define ll long long
using namespace std;
int res = 0;

void dfs(ll x) {
	// printf("%lld ", x);
	res++;
	if(x == 1) {
		return ;
	}
	if(x & 1) {
		dfs(x * 3 + 1);
	} else {
		dfs(x / 2);
	}
}

int main() {
	int m = 1000000, maxn = 0, be = 0;
	// dfs(113383);
	for(int i = 1; i <= m; ++i) {
		res = 0;
		// printf("qwq%d\n", i);
		dfs(i);
		if(res > maxn) {
			maxn = res;
			be = i;
		}
	}
	printf("%d %d\n", maxn, be);
	return 0;
}