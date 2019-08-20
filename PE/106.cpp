#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
vector<int> g[N];
int b[N][10], c[10], res = 0, ans = 0;

bool judge(int x, int y) {
	int flg = 1;
	for(int i = 1; i <= 6; ++i) {
		if(b[x][i] < b[y][i])
			flg = 0;
	}
	if(flg) return false;
	flg = 1;
	for(int i = 1; i <= 6; ++i) {
		if(b[x][i] > b[y][i])
			flg = 0;
	}
	if(flg) return false;
	int pos = 0, tmp = 0;
	for(int i = 1; i <= 6; ++i) {
		pos |= (1 << (b[x][i] - 1));
		tmp |= (1 << (b[y][i] - 1));
	}
	int gg = pos & tmp;
	pos ^= gg, tmp ^= gg;
	if(pos < tmp) swap(pos, tmp);
	g[tmp].push_back(pos);
	return true;
}

void check() {
	printf("res=%d\n", res);
	for(int i = 1; i <= res; ++i)
		for(int j = i + 1; j <= res; ++j) {
			if(judge(i, j)) {
				ans++;
			}
		}
}

void dfs(int dep, int last) {
	if(dep > 6) {
		++res;
		for(int i = 1; i <= 6; ++i) {
			b[res][i] = c[i];
		}
		return ;
	}
	for(int i = last + 1; i <= 12; ++i) {
		c[dep] = i;
		dfs(dep + 1, i);
	}
}

int main() {
	dfs(1, 0);
	check();
	printf("%d\n", ans);
	int pos = 0;
	for(int i = 1; i <= (1 << 12); ++i) {
		sort(g[i].begin(), g[i].end());
		g[i].erase(unique(g[i].begin(), g[i].end()), g[i].end());
		pos += g[i].size();
	}
	printf("%d\n", pos);
	return 0;
}