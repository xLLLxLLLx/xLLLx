### Contest14

[Codeforces827Round#423](https://codeforces.com/contest/827)

[官方题解传送门](https://codeforces.com/blog/entry/53268)

#### A
> 暴力赋值显然不行.所以赋值过后的地方不用赋值
> 发现问题可以转换为区间覆盖问题
> 那么贪心地将左端点较小的放在前面就行了

#### B
> 可以显然地发现直径最小事实上是在求层数最小
> 由于叶子节点必定有$k$个 那么每层尽量放$k$个是最优方案

#### C
>首先暴力匹配肯定是会超时的呀!
>然后想到了用前缀和优化 又发现对于模式串$s$的一个字符$s[1]$
>它所对应的位置是$l+len,l+2*len,l+3*len...$
>又长度很小可以直接树状数组维护前缀和即可

#### D
神仙D题
> 既然题目要我们搞关于最小生成树的东西 那么我们就先搞出一颗最小生成树 那么原本这张图上的边就被分为了树边和非树边两类
>
> - 对于非树边 如果这条边连上去 就会形成一个环 而这条边想要跻身于最小生成树中 那么 肯定是要挤掉一条这个环里面的边(显然是边权最大的那一条) 所以这条边的权值至少要比在这个环中权值最大的边权小1才行
> - 再考虑树边 同理我们可得 要比所有能和这条边成环的非树边的最小值小1

实质上 树边和非树边可以一起搞的嘛。。
而且你会发现这些个限制实际上实在链上搞的嘛！
~~你发现你的树链剖分派上了用场~~
但其实可以不用
我们发现我们是在链上取min 那么如果一条链已经被一个比较小的值取过min了 那么比这个值大的再去取min是没有什么用的
那么我们将这些操作按照权值排序
取完min就可以用并查集合并啦！

#### E
[挂个链接就不证了](https://www.cnblogs.com/wuyiqi/archive/2012/01/06/2314078.html)
> 根据kmp的性质 如果一个字符串有一个长度为$k$的循环节 
> 那么必然有长度为$n-k$的公共前后缀

为了方便得进行check
我们令$A[i]=[s[i]=='V'],B[i]=[s[i]=='K']$
那么可行条件为
$$\sum_{i = 0}{n-k-1}A[i]*B[i+k]=0\ \&\&  \sum_{i=0}{n-k-1}B[i]*A[i+k]=0$$
那么我们将$A$翻转一下 发现这个下标和是个定值啊～
那么我们就可以直接上FFT了

#### F
神仙题...
> 注意到，一条边(u,v)的贡献是一个时间段，且如果到达u的时间是t，那么他会使$v[t+1][v],v[t+3][v]..v[t+1+2k][v]，v[t+2][u],v[t+4][u]$..变成true， 
> 改成true的这些时间点对于一个点来说奇偶性是相同的，又是时间连续的一段

我们不妨把每个点拆成两个点，表示时刻为奇数和偶数。 
边也按照奇偶拆开，再拆成两条有向边。 
然后用小根堆以加入时间为关键字维护每条边。设Late[u][p]表示当前奇偶性为p的点u，最晚可以逗留到什么时候。
加入一条边时，如果它的起点Late大于等于它的出现时间，那么这条边是可达的，然后去更新终点的答案。否则把它存在起点，等待这个点下一次被访问时再拿出来。 

------------------

##### A

```c++
#include <bits/stdc++.h>
using namespace std;
const int N = 3e6 + 10;
struct data {
	int l, r, id;
} a[N];
int d[N];
string lx[N];

bool cmp(data A, data B) {
	return A.l == B.l ? A.r > B.r : A.l < B.l;
}

int main() {
	int n, maxn = 0;
	scanf("%d", &n);
	int cnt = 0;
	for(int o = 1, num; o <= n; ++o) {
		cin >> lx[o];
		scanf("%d", &num);
		int len = lx[o].size();
		for(int t = 1, be; t <= num; ++t) {
			scanf("%d", &be);
			maxn = max(maxn, be + len - 1);
			a[++cnt].l = be, a[cnt].r = be + len - 1, a[cnt].id = o;
		}
	}
	sort(a + 1, a + 1 + cnt, cmp);
	int last = 0;
	for(int i = 1; i <= cnt; ++i) {
		for(int j = max(last, a[i].l); j <= a[i].r; ++j) {
			d[j] = lx[a[i].id][j - a[i].l] - 'a' + 1;
		}
		last = max(last, a[i].r + 1);
	}
	for(int i = 1; i <= maxn; ++i) {
		if(!d[i]) d[i] = 1;
		printf("%c", char(d[i] + 'a' - 1));
	}
	puts("");
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
int cnt = 0, ans = 0;
int head[N], dp[N], d[N], vis[N];
queue<int> q;

void add(int x, int y) {
	d[x]++, d[y]++;
	a[++cnt].to = y;
	a[cnt].nt = head[x];
	head[x] = cnt;
}

void dfs(int u) {
	vis[u] = 1;
	for(int i = head[u]; i; i = a[i].nt) {
		int to = a[i].to;
		dfs(to);
		ans = max(ans, dp[u] + dp[to] + 1);
		dp[u] = max(dp[u], dp[to] + 1);
	}
}

int main() {
	int n, k;
	scanf("%d%d", &n, &k);
	int L = 0;
	for(int i = 1; i <= n; ++i) {
		if(k + (n - k) * i > 2 * (n - 1)) break;
		L = i;
	}
	int pos = 2 * (n - 1) - (k + (n - k) * L), tmp = n - k - pos;
	// printf("%d %d %d\n", L, pos, tmp);
	for(int i = 1; i <= n; ++i) {
		if(i <= k) {
			q.push(i);
			continue;
		}
		if(i == n) L++;
		if(tmp) {
			for(int j = 1; j < L; ++j) {
				int h = q.front(); q.pop();
				add(i, h);
			}
			tmp--;
		} else {
			for(int j = 1; j <= L; ++j) {
				int h = q.front(); q.pop();
				add(i, h);
			}
		}
		q.push(i);
	}	
	dfs(n);
	// printf("%d\n", ans);
	// for(int u = 1; u <= n; ++u) {
	// 	for(int i = head[u]; i; i = a[i].nt) {
	// 		printf("%d %d\n", u, a[i].to);
	// 	}
	// }
	int count = 0, zz = 0, flg = 0;
	for(int i = 1; i <= n; ++i) {
		count += (d[i] == 1);
		zz += (d[i] >= 2);
		if(!vis[i]) {
			flg = 1;
		}
	}
	if(count != k || zz != n - k || flg) printf("WAI!\n");
	else printf("Yes\n");
	return 0;
}
```

##### C

```c++
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
char lx[N];
int v[N], tr[4][11][11][N];

int lower(int x) {
	return x & (-x);
}

void add(int *a, int x, int k) {
	for(int i = x; i < N; i += lower(i)) {
		a[i] += k;
	}
}

int get(int *a, int x) {
	int ans = 0;
	for(int i = x; i; i -= lower(i)) {
		ans += a[i];
	}
	return ans;
}

int zh(char ch) {
	if(ch == 'A') return 0;
	if(ch == 'T') return 1;
	if(ch == 'G') return 2;
	if(ch == 'C') return 3;
}

int main() {
	scanf("%s", lx + 1);
	int n = strlen(lx + 1);
	for(int i = 1; i <= 10; ++i) {
		for(int j = 1; j <= n; ++j) {
			v[j] = zh(lx[j]);
			add(tr[v[j]][i][j % i], j, 1);
		}
	}
	int m;
	scanf("%d", &m);
	for(int o = 1, tp; o <= m; ++o) {
		scanf("%d", &tp);
		if(tp == 2) {
			int l, r, ans = 0;
			scanf("%d%d%s", &l, &r, lx + 1);
			int len = strlen(lx + 1);
			for(int i = 1; i <= min(r - l + 1, len); ++i) {
				int gg = zh(lx[i]), tmp = (l + i - 1) % len;
				int pos = get(tr[gg][len][tmp], r) - get(tr[gg][len][tmp], l - 1);
				ans += pos;
			}
			printf("%d\n", ans);
		} else {
			int x;
			scanf("%d%s", &x, lx + 1);
			int y = zh(lx[1]);
			for(int i = 1; i <= 10; ++i) {
				add(tr[v[x]][i][x % i], x, -1);
				add(tr[y][i][x % i], x, 1);
			}
			v[x] = y;
		}
	}
	return 0;
}
```

##### D

```c++
#include <bits/stdc++.h>
const int N = 2e5 + 10, LOG = 19;
using namespace std;
struct data {
	int to, nt, id, w;
} ed[N], a[N << 1];
int n, m, cnt = 0;
int v[N][LOG + 1], ans[N];
int dep[N], ys[N], g[N][LOG + 1], head[N];
int f[N], used[N];

bool cmp(data A, data B) {
	return A.w < B.w;
}

void add(int x, int y, int id, int w) {
	a[++cnt].to = y;
	a[cnt].id = id;
	a[cnt].w = w;
	a[cnt].nt = head[x];
	head[x] = cnt;
}

int find(int k) {
	return k == f[k] ? f[k] : f[k] = find(f[k]);
}

void kruskal() {
	sort(ed + 1, ed + 1 + m, cmp);
	for(int i = 1; i <= n; ++i) f[i] = i;
	int now = 0;
	for(int i = 1; i <= m; ++i) {
		int fx = find(ed[i].to), fy = find(ed[i].nt);
		if(fx != fy) {
			now++;
			used[i] = 1;
			f[fx] = fy;
			// printf("%d %d %d\n", ed[i].to, ed[i].nt, ed[i].w);
			add(ed[i].to, ed[i].nt, ed[i].id, ed[i].w);
			add(ed[i].nt, ed[i].to, ed[i].id, ed[i].w);
		}
		if(now == n - 1) return ;
	}
}

void dfs(int u, int fa) {
	dep[u] = dep[fa] + 1;
	g[u][0] = fa;
	for(int i = head[u]; i; i = a[i].nt) {
		int to = a[i].to;
		if(to == fa) {
			continue;
		}
		dfs(to, u);
		v[to][0] = a[i].w;
		ys[to] = a[i].id;
	}
}

void yyqx() {
	for(int j = 1; j <= LOG; ++j)
		for(int i = 1; i <= n; ++i) {
			g[i][j] = g[g[i][j - 1]][j - 1];
			v[i][j] = max(v[i][j - 1], v[g[i][j - 1]][j - 1]);
		}
}

int GetLCA(int A, int B, int &val) {
	val = 0;
	if(dep[A] > dep[B]) swap(A, B);
	for(int i = LOG; i >= 0; --i)
		if(dep[g[B][i]] >= dep[A]) {
			val = max(val, v[B][i]);
			B = g[B][i];
		}
	if(A == B) return A;
	for(int i = LOG; i >= 0; --i) 
		if(g[A][i] != g[B][i]) {
			val = max(val, max(v[A][i], v[B][i]));
			A = g[A][i], B = g[B][i];
		}
	val = max(val, max(v[A][0], v[B][0]));
	return g[A][0];
} 

void change(int x, int y, int val) {
	// printf("val=%d\n", val);
	x = find(x);
	while(dep[x] > dep[y]) {
		ans[ys[x]] = min(ans[ys[x]], val);
		int y = find(g[x][0]);
		f[x] = y;
		x = find(x);
	}
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; ++i) {
		scanf("%d%d%d", &ed[i].to, &ed[i].nt, &ed[i].w);
		ed[i].id = i;
	}
	kruskal();
	dfs(1, 0), yyqx();
	// for(int i = 1; i <= n; ++i) 
	//  for(int j = 0; j <= LOG; ++j) {
	// 	printf("v[%d][%d] = %d\n", i, j, v[i][j]);
	// }
	for(int i = 1; i <= m; ++i) f[i] = i;
	for(int i = 1; i <= m; ++i) ans[i] = 1e9;
	for(int i = 1; i <= m; ++i) {
		if(used[i]) continue;
		int u = ed[i].nt, v = ed[i].to;
		int lca = GetLCA(u, v, ans[ed[i].id]);
		// printf("qwq%d %d %d %d\n", u, v, lca, ans[ed[i].id]);
		ans[ed[i].id]--;
		change(u, lca, ed[i].w - 1), change(v, lca, ed[i].w - 1);
	}
	for(int i = 1; i <= m; ++i) {
		if(ans[i] == 1e9) ans[i] = -1;
		printf("%d ", ans[i]);
	}
	return 0;
}

/*
10 21
5 6 88
6 3 74
1 5 7
1 6 27
8 1 50
4 1 24
10 6 37
9 7 39
5 7 63
2 7 98
3 4 28
9 2 5
2 4 96
9 6 67
9 10 47
10 4 64
2 5 70
6 8 89
3 5 54
6 7 18
1 7 26

25 27 53 25 88 53 46 46 25 38 53 69 38 38 38 36 38 49 27 26 26 
*/
```

##### E

```c++
#include <bits/stdc++.h>
using namespace std;
const int N = 2e6 + 10;
const double PI = acos(-1.0);
struct C {
	double r, i;
	C() { r = 0, i = 0; }
	C(double _r, double _i) { r = _r, i = _i; }
	C operator + (C x) { return C(r + x.r, i + x.i); }
	C operator - (C x) { return C(r - x.r, i - x.i); }
	C operator * (C x) { return C(r * x.r - i * x.i, i * x.r + r * x.i); }
} A[N], B[N], w[N];
char lx[N];
int rev[N], b[N], d[N];
 
void fft(C a[], int n) {
	for(int i = 0; i < n; ++i) 
		if(rev[i] > i)
			swap(a[i], a[rev[i]]);
	for(int t = n >> 1, d = 1; d < n; t >>= 1, d <<= 1)
		for(int i = 0; i < n; i += (d << 1))
			for(int j = 0; j < d; ++j) {
				C tmp = w[t * j] * a[i + j + d];
				a[i + j + d] = a[i + j] - tmp;
				a[i + j] = a[i + j] + tmp;
			}
}
 
void work(int len) {
	int L = 0, n = 1;
	for(; n < 2 * len; n <<= 1, L++);
	for(int i = 0; i < n; ++i) {
		b[i] = 0;
		A[i] = B[i] = C(0, 0);
		w[i] = C(cos(2.0 * i * PI / n), sin(2.0 * i * PI / n));
		rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (L - 1));
	}
	for(int i = 1; i <= len; ++i) {
		if(lx[i] == 'V') A[len - i].r = 1;
		if(lx[i] == 'K') B[i - 1].r = 1;
	}
	fft(A, n), fft(B, n);
	for(int i = 0; i < n; ++i) {
		A[i] = A[i] * B[i];
		w[i].i = -w[i].i;
	}
	fft(A, n);
	for(int i = 0; i < n; ++i) {
		int pos = int((A[i].r + 0.5) / n);
		// printf("%d\n", pos);
		if(pos) b[abs(i - len + 1)] = 1;
	}
	int ans = 0;
	for(int i = 1; i <= len; ++i) {
		if(!b[i]) {
			for(int j = i; j <= len; j += i) {
				if(b[j]) {
					b[i] = 1;
					break;
				}
			}
		}
	}
	d[0] = 0;
	for(int i = 1; i <= len; ++i)
		if(!b[i])
			d[++d[0]] = i;
	printf("%d\n", d[0]);
	for(int i = 1; i <= d[0]; ++i) {
		printf("%d ", d[i]);
	}
	puts("");
}
 
int main() {
	int T;
	scanf("%d", &T);
	for(int o = 1, len; o <= T; ++o) {
		scanf("%d%s", &len, lx + 1);
		work(len);
	}
	return 0;
}
```

##### F

```c++
#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 10;
struct node {
	int u, v, l, r;
	bool operator < (const node & C) const {
		return l > C.l;
	}
};
struct data {
	int nt, to, r;
} a[N * 10];
int head[N][2], L[N][2], cnt = 0;
priority_queue<node> q;

void add(int x, int y, int r, int opt) {
	a[++cnt].to = y, a[cnt].r = r;
	a[cnt].nt = head[x][opt], head[x][opt] = cnt;
}

void insert(int u, int v, int l, int r) {
	q.push((node){u, v, l, r});
}

void go(int u, int l, int r, int opt) {
	L[u][opt] = max(L[u][opt], r);
	for(int i = head[u][opt]; i; i = a[i].nt) {
		insert(u, a[i].to, l, a[i].r);
	}
	head[u][opt] = 0;
}

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	if(n == 1) {
		return printf("0\n"), 0;
	}
	for(int i = 1; i <= m; ++i) {
		int u, v, l, r;
		scanf("%d%d%d%d", &u, &v, &l, &r);
		r--;
		int pos = r - l;
		insert(u, v, l, r - (pos & 1));
		insert(v, u, l, r - (pos & 1));
		insert(u, v, l + 1, r - (!(pos & 1)));
		insert(v, u, l + 1, r - (!(pos & 1)));
	}
	memset(L,255,sizeof(L));
  L[1][0]=0;
	while(!q.empty()) {
		node h = q.top(); q.pop();
		if(h.l > h.r) {
			continue;
		}
		int opt = h.l & 1;
		if(L[h.u][opt] >= h.l) {
			if(h.v == n) {
				printf("%d\n", h.l + 1);
				return 0;
			} 
			go(h.v, h.l + 1, h.r + 1, opt ^ 1);
		} else {
			add(h.u, h.v, h.r, opt);
		}
	}
	puts("-1");
	return 0;
}
```

