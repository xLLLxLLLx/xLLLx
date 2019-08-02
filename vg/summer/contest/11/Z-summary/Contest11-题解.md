### Contest11

--------------------

**Codeforces936 Round#467(Div1)**

| #         | A    | B    | C    | D    | E    |
| --------- | ---- | ---- | ---- | ---- | ---- |
| Contest11 | S    | S    | A    | A    | A    |

[官方题解来袭](https://codeforces.com/blog/entry/58056)

[传送门](https://codeforces.com/contest/936)

#### C

构造题

> 逐个字符构造，也是从后往前。
>
> 比如说现在串是AzB，A的前缀已经是t的一个后缀，z是想加在A前面的字符，B是剩下的。然后这样：AzB->B'zA'->AB'z->zAB'。

#### D

> 我们发现这个每$k$秒才会有一次发射 可以看作是积累步数

那么我们就可以发现 这样子求一行的是很容易的

那么有两行怎么办呢？

有一个贪心策略 就是如果你要转到另一行的话 那么肯定是在绕过当前行某个障碍之后立即到另外一行去的

这样不会变劣

![图片](https://images2018.cnblogs.com/blog/1067221/201803/1067221-20180307102048197-669731968.png)



#### E

ban图小分队！

![](https://cdn.luogu.org/upload/pic/60620.png)

![](https://cdn.luogu.org/upload/pic/60621.png)



好了。。这两张图已经说明了这道题最关键的东西啦～

> 首先将这个网格图弄成一个树形图 然后你发现最后的路径长度实际上就是$dep[s]+dep[T]+abs(A-B)$
>
> 所以你可以采取点分治+树状数组即可～



----------------------

Code

##### A

```c++
#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main() {
	ll k, d, t;
	cin >> k >> d >> t;
	ll pos = k / d, yu = k % d;
	if(!yu) {
		return printf("%lld\n", t), 0;
	}
	t *= 2ll;
	ll tmp = (pos * d + yu) * 2 + (d - yu);
	ll gg = t / tmp * (pos + 1) * d, sx = t % tmp;
	double ans = gg;
	if(sx <= (pos * d + yu) * 2) {
		ans += double(sx) / 2.0;
	} else {
		ans += sx - (d * pos + yu);
	}
	printf("%.12f\n", ans);
	return 0;
}
```

##### B

```c++
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
struct data {
	int nt, to;
} a[N];
vector<int> g[N];
struct node {
	int x, id;
};
queue<node> q;
int head[N], dfn[N], vis[N], low[N], st[N], top = 0, res = 0, cnt = 0, maxn = 0;
int fr[N][2], f[N][2], d[N];

void add(int x, int y) {
	a[++cnt].to = y;
	a[cnt].nt = head[x];
	head[x] = cnt;
}

void print(int x, int id) {
	printf("%d ", x);
	if(fr[x][id]) {
		print(fr[x][id], id ^ 1);
	}
}

void dfs(int x) {
	vis[x] = 1, st[++top] = x;
	dfn[x] = low[x] = ++res;
	for(int i = head[x]; i; i = a[i].nt) {
		int to = a[i].to;
		if(!dfn[to]) {
			dfs(to);
			low[x] = min(low[x], low[to]);
		} else if(vis[to]) {
			low[x] = min(low[x], dfn[to]);
		}
	}
	if(dfn[x] == low[x]) {
		int pos = 0;
		while(st[top] != x) {
			pos++;
			vis[st[top--]] = 0;
		}
		pos++, vis[st[top--]] = 0;
		maxn = max(maxn, pos);
	}
}

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &d[i]);
		for(int j = 1, x; j <= d[i]; ++j) {
			scanf("%d", &x);
			add(i, x);
			g[x].push_back(i);
		}
	}
	int s;
	scanf("%d", &s);
	dfs(s);
	for(int i = 1; i <= n; ++i) {
		if(!d[i]) {
			f[i][0] = 1;
			q.push((node){i, 0});
		}
	}
	while(!q.empty()) {
		node h = q.front(); q.pop();
		int len = g[h.x].size();
		for(int i = 0; i < len; ++i) {
			int to = g[h.x][i];
			if(!f[to][h.id ^ 1]) {
				f[to][h.id ^ 1] = 1;
				fr[to][h.id ^ 1] = h.x;
				q.push((node){to, h.id ^ 1});
			}
		}
	}
	// printf("%d\n", maxn);
	if(f[s][1]) {
		printf("Win\n");
		print(s, 1);
	} else if(maxn > 1) {
		printf("Draw\n");
	} else {
		printf("Lose\n");
	}
	return 0;
}
```

##### C

```c++
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
```

##### D

```c++
#include <bits/stdc++.h>
using namespace std;
const int N = 2e6 + 10;
struct node {
  int x, y;
};
vector<int> g;
vector<node> fir;
int n, m1, m2, t, tot;
int all[N], f[N][2], z[N][2], ys[N][2], rev[N][2];

int get(int x) {
  return lower_bound(all + 1, all + 1 + tot, x) - all;
}

bool cmp(node A, node B) {
  return A.x < B.x;
}

void print(int x) {
  printf("Yes\n");
  int tmp = 2e9;
  for(int i = tot; i; --i) {
    if(rev[i][x]) {
      x ^= 1;
      g.push_back(all[i]);
    }
    int d = all[i] - all[i - 1];
    if(f[i - 1][x] + d > f[i][x]) {
      int pos = min(tmp - t, all[i] - 1);
      tmp = pos;
      fir.push_back((node){pos, x + 1});
    }
  }
  /*output*/
  if(x) g.push_back(0);
  sort(g.begin(), g.end());
  sort(g.begin(), g.end());
  printf("%d\n", (int)g.size());
  for(int i = 0; i < g.size(); ++i) {
    printf("%d ", g[i]);
  }
  puts("");
  sort(fir.begin(), fir.end(), cmp);
  printf("%d\n", (int)fir.size());
  for(int i = 0; i < fir.size(); ++i) {
    printf("%d %d\n", fir[i].x, fir[i].y);
  }
}

int main() {
  scanf("%d%d%d%d", &n, &m1, &m2, &t);
  int cnt = 0;
  for(int i = 1; i <= m1; ++i) {
    scanf("%d", &z[i][0]);
    all[++cnt] = z[i][0], all[++cnt] = z[i][0] + 1;
  }
  for(int i = 1; i <= m2; ++i) {
    scanf("%d", &z[i][1]);
    all[++cnt] = z[i][1], all[++cnt] = z[i][1] + 1;
  }
  sort(all + 1, all + 1 + cnt);
  tot = unique(all + 1, all + 1 + cnt) - all - 1;
  for(int i = 1; i <= m1; ++i) {
    z[i][0] = get(z[i][0]);
    ys[z[i][0]][0] = 1;
  }
  for(int i = 1; i <= m2; ++i) {
    z[i][1] = get(z[i][1]);
    ys[z[i][1]][1] = 1;
  }
  memset(f, -1, sizeof f);
  f[0][0] = f[0][1] = 0;
  for(int i = 1; i <= tot; ++i) {
    int d = all[i] - all[i - 1];
    for(int j = 0; j < 2; ++j) {
      if(f[i - 1][j] == -1) {
        continue;
      }
      if(ys[i][j]) {
        if(f[i - 1][j] + d - 1 >= t && f[i - 1][j] + d - t > f[i][j]) {
          f[i][j] = f[i - 1][j] + d - t;
          rev[i][j] = 0;
        }
      } else {
        if(f[i - 1][j] + d > f[i][j]) {
          f[i][j] = f[i - 1][j] + d;
          rev[i][j] = 0;
        }
      }
    }
    if(!ys[i][1] && ~f[i][0] && min(f[i][0], t) > f[i][1]) {
      f[i][1] = min(f[i][0], t);
      rev[i][1] = 1;
    }
    if(!ys[i][0] && ~f[i][1] && min(f[i][1], t) > f[i][0]) {
      f[i][0] = min(f[i][1], t);
      rev[i][0] = 1;
    }
  }
  // for(int i = 1; i <= tot; ++i) {
  //   for(int j = 0; j < 2; ++j) {
  //     printf("f[%d][%d] = %d\n", i, j, f[i][j]);
  //   }
  // }
  if(~f[tot][0]) print(0);
  else if(~f[tot][1]) print(1);
  else printf("No\n");
  return 0;
}
```

##### E

```c++
#include <bits/stdc++.h>
#define p pair<int, int>
#define fi first
#define se second
using namespace std;
const int N = 3e5 + 10; 
queue<int> q;
p zb[N], dis[N];
map<p, int> id;
set<int> tree[N];
vector<int> side[N], g[N], gg[N], path;
vector<p> put, Ques, add;
int appear[N], flg[N], qz[N], hz[N], cnt[N], ys[N], mx[N], ans[N], sz[N];
int tot = 0;

void dfs(int x) {
	// printf("x = %d\n", x);
	path.push_back(x);
	sz[x] = 1;
	for(set<int> :: iterator sit = tree[x].begin(); sit != tree[x].end(); ++sit) {
		if(!sz[(*sit)]) {
			dfs(*sit);
			sz[x] += sz[*sit];
		}
	}
}

int lower(int x) {
	return x & (-x);
}

void Min(int &x, int y) {
	x = min(x, y);
}

void solve(int rt) {
	path.clear();
	dfs(rt);
	int zx = -1;
	for(int i = 0; i < path.size(); ++i) {
		int to = path[i];
		mx[to] = min(sz[to], sz[rt] - sz[to]);
		if(zx == -1 || mx[to] > mx[zx]) zx = to;
	}
	for(int i = 0; i < path.size(); ++i)
		for(int j = 0; j < g[path[i]].size(); ++j) {
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
	while(!q.empty()) {
		int h = q.front(); q.pop();
		for(int i = 0; i < side[h].size(); ++i) {
			int to = side[h][i];
			if(dis[to].fi > dis[h].fi + 1) {
				dis[to] = p(dis[h].fi + 1, dis[h].se);
				q.push(to);
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
			for(int j = dis[add[tmp].se].se + 1; j; j -= lower(j))
				Min(qz[j], dis[add[tmp].se].fi + dis[add[tmp].se].se);
			for(int j = dis[add[tmp].se].se + 1; j <= cnt[zx]; j += lower(j))
				Min(hz[j], dis[add[tmp].se].fi - dis[add[tmp].se].se);
		}
		for(int j = dis[Ques[i].se].se + 1; j; j -= lower(j)) {
			if(hz[j] != 1e9) {
				Min(ans[Ques[i].fi], dis[Ques[i].se].fi + hz[j] + dis[Ques[i].se].se);
			}
		}
		for(int j = dis[Ques[i].se].se + 1; j <= cnt[zx]; j += lower(j)) {
			if(qz[j] != 1e9) {
				Min(ans[Ques[i].fi], dis[Ques[i].se].fi + qz[j] - dis[Ques[i].se].se);
			}
		}
	}
	for(set<int> :: iterator sit = tree[zx].begin(); sit != tree[zx].end(); ++sit) {
		tree[*sit].erase(tree[*sit].find(zx));
	}
	for(set<int> :: iterator sit = tree[zx].begin(); sit != tree[zx].end(); ++sit) {
		solve(*sit);
	}
}

int main() {
	int n;
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
```

