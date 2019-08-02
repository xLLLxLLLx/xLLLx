#include <bits/stdc++.h>
using namespace std;
const int N = 1e4 + 10;
vector<int> g[N], u, v;
char lx[5];
int e[N], o[N];
int tot = 0;

bool Ask(int x, int y) {
	printf("? %d %d\n", x, y);
	fflush(stdout);
	scanf("%s", lx + 1);
	return lx[1] == '<';
}

void split(int now, int x) {
	u.clear(), v.clear();
	for(int i = 0; i < g[now].size(); ++i) {
		if(Ask(g[now][i], x)) 
			u.push_back(g[now][i]);
		else 
			v.push_back(g[now][i]);
	}
}

int insert(int x) {
	for(int i = tot; i > x; --i)
		g[i + 1] = g[i];
	g[x] = u, g[x + 1] = v, tot++;
	int ans = 0;
	for(int i = 1; i <= x; ++i)
		ans += (int)g[i].size();
	return ans * 2 + 1;
}

int main() {
	int n;
	scanf("%d", &n);
	if(n == 1) {
		printf("! 1\n");
		fflush(stdout);
		return 0;
	}
	tot = 1;
	for(int i = 1; i <= n / 2; ++i) {
		g[1].push_back(i);
	}
	// printf("%d\n", (int)g[1].size());
	for(int i = 1; i <= (n + 1) / 2; ++i) {
		int l = 1, r = tot, ans = 0;
		while(l <= r) {
			int mid = (l + r) >> 1;
			if(Ask(g[mid][0], i)) {
				ans = mid, l = mid + 1;
			} else {
				r = mid - 1;
			}
		}
		// printf("%d\n", ans);
		if(!ans) {
			// printf("???\n");
			split(1, i);
			if(!u.size()) {
				o[i] = 1;
			} else if(!v.size()) {
				o[i] = u.size() * 2 + 1;
			} else {
				o[i] = insert(1);
			}
			// printf(">??\n");
		} else {
			int now = 0;
			for(int i = 1; i < ans; ++i)
				now += (int)g[i].size();
			split(ans, i);
			if(!v.size()) {
				if(ans == tot) {
					o[i] = n;
				} else {
					now += (int)g[ans].size();
					split(ans + 1, i);
					if(!u.size()) {
						o[i] = now * 2 + 1;
					} else {
						o[i] = insert(ans + 1);
					}
				}
			} else {
				o[i] = insert(ans);
			}
		}
	}
	int cur = 0;
	for(int i = 1; i <= tot; ++i)
		for(int j = 0; j < g[i].size(); ++j)
			cur++, e[g[i][j]] = cur * 2;
	printf("! ");
	for(int i = 1; i <= n / 2; ++i) {
		printf("%d", e[i]);
		if(i != n / 2) printf(" ");
	}
	for(int i = 1; i <= (n + 1) / 2; ++i)
		printf(" %d", o[i]);
	puts("");
	fflush(stdout);
	return 0;
}