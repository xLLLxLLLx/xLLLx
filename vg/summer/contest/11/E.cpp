#include <bits/stdc++.h>
#define p pair<int, int>
#define fi first
#define se second
using namespace std;
const int N = 4e5 + 10; 
queue<int> q;
p zb[N], dis[N];
map<p, int> id;
set<int> tree[N];
vector<int> side[N], g[N], gg[N], path;
vector<p> put, Ques, add;
int appear[N], flg[N], qz[N], hz[N], cnt[N], ys[N], mx[N], ans[N], sz[N];
int tot = 0;
int n;
 
void dfs(int x) {
	path.push_back(x);
	mx[x] = 0, sz[x] = 1;
	for(set<int> :: iterator sit = tree[x].begin(); sit != tree[x].end(); ++sit) {
		if(!sz[(*sit)]) {
			dfs(*sit);
			sz[x] += sz[*sit];
			mx[x] = max(mx[x], sz[*sit]);
		}
	}
}
 
void Min(int &x, int y) {
	x = min(x, y);
}
 
 
int cct = 0;
void check(int c) {
	//assert(0);
	if(c > 100000000) {
		assert(0);
	}
}
void solve(int rt) {
 
	path.clear();
	dfs(rt);
 
	int zx = -1;
	for(int i = 0; i < path.size(); ++i) {
		int to = path[i];
		mx[to] = max(mx[to], sz[rt] - sz[to]);
		if(zx == -1 || mx[to] < mx[zx]) zx = to;
	}
{
	for(int i = 0; i < path.size(); ++i)

		for(int j = 0; j < g[path[i]].size(); ++j) {
			cct++;
			check(cct);
			if(path[i] == zx) {
				dis[g[path[i]][j]] = p(0, g[path[i]][j] - path[i]);
				q.push(g[path[i]][j]);
			} else {
				dis[g[path[i]][j]] = p(1e9, -1);
			}
		}
	for(int i = 0; i < path.size(); ++i) {
		sz[path[i]] = 0;
	}
}
 {
	while(!q.empty()) {
		int h = q.front(); q.pop();
		cct++;
		check(cct);
		for(int i = 0; i < side[h].size(); ++i) {
			int to = side[h][i];
			if(dis[to].fi > dis[h].fi + 1) {
				dis[to] = p(dis[h].fi + 1, dis[h].se);
				q.push(to);
			}
		}
	}
}
	
	for(int i = 0; i <= cnt[zx]; ++i) {
		qz[i] = hz[i] = 1e9;
	}
	Ques.clear(), add.clear();
 
	
 
	for(int i = 0; i < path.size(); ++i) {
		int xh = path[i];
		for(int j = 0; j < g[xh].size(); ++j) {
			int pos = g[xh][j];
			if(appear[pos] != 1e9) {
				add.push_back(p(appear[pos], pos));
			}
			for(int k = 0; k < gg[pos].size(); ++k) {
				Ques.push_back(p(gg[pos][k], pos));
			}
		}
	}
	sort(Ques.begin(), Ques.end()), sort(add.begin(), add.end());
 
	for(int i = 0, tmp = 0; i < Ques.size(); ++i) {
		for(; tmp < add.size() && add[tmp].fi < Ques[i].fi; ++tmp) {
			for(int j = dis[add[tmp].se].se + 1; j; j -= j & (-j))
			{
				cct++;
				check(cct);
				Min(qz[j], dis[add[tmp].se].fi + dis[add[tmp].se].se);
			}
			for(int j = dis[add[tmp].se].se + 1; j <= cnt[zx]; j += j & (-j))
			{
				Min(hz[j], dis[add[tmp].se].fi - dis[add[tmp].se].se);
				cct++;
				check(cct);
			}
		}
		for(int j = dis[Ques[i].se].se + 1; j; j -= j & (-j)) {
			cct++;
				check(cct);
			if(hz[j] != 1e9) {
				
				Min(ans[Ques[i].fi], dis[Ques[i].se].fi + hz[j] + dis[Ques[i].se].se);
			}
		}
		for(int j = dis[Ques[i].se].se + 1; j <= cnt[zx]; j += j & (-j)) {
			cct++;
				check(cct);
			if(qz[j] != 1e9) {
				
				Min(ans[Ques[i].fi], dis[Ques[i].se].fi + qz[j] - dis[Ques[i].se].se);
			}
		}
	}
 
	for(set<int> :: iterator sit = tree[zx].begin(); sit != tree[zx].end(); ++sit) {
		tree[*sit].erase(zx);
	}
 
	for(set<int> :: iterator sit = tree[zx].begin(); sit != tree[zx].end(); ++sit) {
		solve(*sit);
	}
}
 
int main() {
 
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		scanf("%d%d", &zb[i].fi, &zb[i].se);
	}
	sort(zb + 1, zb + 1 + n);
	for(int i = 1; i <= n; ++i) {
		id[zb[i]] = i;
	}
	for(int i = 1; i <= n; ++i) {
		if(i > 1 && zb[i].fi == zb[i - 1].fi && zb[i].se == zb[i -1].se + 1) {
			ys[i] = ys[i - 1];
			side[i].push_back(i - 1), side[i - 1].push_back(i);
		} else ys[i] = i;
		if(id.find(p(zb[i].fi - 1, zb[i].se)) != id.end()) {
			int j = (*id.find(p(zb[i].fi - 1, zb[i].se))).se;
			side[i].push_back(j), side[j].push_back(i);
			tree[ys[i]].insert(ys[j]), tree[ys[j]].insert(ys[i]);
			// printf("edge%d %d\n", ys[i], ys[j]);
		}
	}
	for(int i = 1; i <= n; ++i) {
		appear[i] = 1e9;
		// printf("qwq%d %d %d %d\n", i, zb[i].fi, zb[i].se, ys[i]);
		cnt[ys[i]]++;
		g[ys[i]].push_back(i);
	}
	int m;
	scanf("%d", &m);	
	for(int i = 1, x, y, z; i <= m; ++i) {
		scanf("%d%d%d", &x, &y, &z);
		ans[i] = 1e9;
		int pos = id[p(y, z)];
		if(x == 1) {
			appear[pos] = min(appear[pos], i);
		} else {
			flg[i] = 1;
			gg[pos].push_back(i);
		}
	}
	solve(1);
	for(int i = 1; i <= m; ++i) {
		if(flg[i]) printf("%d\n", ans[i] == 1e9 ? -1 : ans[i]);
	}
	return 0;
}
