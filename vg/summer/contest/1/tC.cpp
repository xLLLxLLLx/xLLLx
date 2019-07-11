#include <bits/stdc++.h>
using namespace std;
const int N = 9e6 + 10;
queue<int> q;
int v[N], vis[N];
int n, m, tot;

void go(int x) {
	if(vis[x]) return ;
	// printf("%d\n", x);
	vis[x] = 1;
	if(x <= tot) {
		if(v[x]) go(x + tot + 1);
	} else {
		x = x - tot - 1;
		if(v[tot ^ x]) go(tot ^ x);
		for(int i = 0; i < n; ++i) {
			if((x >> i) & 1) {
				continue;
			}
			int pos = (x | (1 << i)) + tot + 1;
			go(pos);
		}
	}
}

int main() {
	scanf("%d%d", &n, &m);
	tot = (1 << n) - 1;
	for(int i = 1, x; i <= m; ++i) {
		scanf("%d", &x);
		v[x] = 1;
	}
	int ans = 0;
	for(int i = 0; i <= tot; ++i) {
		if(v[i] && !vis[i]) {
			go(i);
			ans++;
		}
	}
	printf("%d\n", ans);
	return 0;
}