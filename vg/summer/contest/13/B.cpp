#include <bits/stdc++.h>
using namespace std;
const int N = 1010;
vector<int> g[N];
int flg[N], num[N];

int main() {
	int n;
	scanf("%d", &n);
	for(int i = 2, x; i <= n; ++i) {
		scanf("%d", &x);
		g[x].push_back(i);
	}
	for(int i = 1; i <= n; ++i) {
		if(g[i].size() == 0) flg[i] = 1;
	}
	for(int i = 1; i <= n; ++i) {
		for(int j = 0; j < g[i].size(); ++j) {
			num[i] += flg[g[i][j]];
		}
	}
	for(int i = 1; i <= n; ++i) {
		if(!flg[i] && num[i] < 3) {
			puts("No");
			return 0;
		}
	}
	puts("Yes");
	return 0;
}