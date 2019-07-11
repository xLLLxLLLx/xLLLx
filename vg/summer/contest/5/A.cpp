#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
vector <int> g[N];
int vis[N], st[N];
char lx[N];

void fail() {
	printf("-1\n");
	exit(0);
}

int main() {
	scanf("%s", lx + 1);
	int len = strlen(lx + 1), res = 0, now = 0;
	for(int i = 1; i <= len; ++i) {
		if(lx[i] == '0') {
			g[++now].push_back(i);
		} else {
			if(!now) fail();
			g[now--].push_back(i);
		}
		res = max(res, now);
	}
	if(now != res) fail();
	printf("%d\n", res);
	for(int i = 1; i <= res; ++i) {
		int l = g[i].size();
		printf("%d ", l);
		for(int j = 0; j < l; ++j) {
			printf("%d ", g[i][j]);
		}
		puts("");
	}
	return 0;
}