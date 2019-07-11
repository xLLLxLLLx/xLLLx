[TOC]

### Contest 5

[Codeforces949-Round#469Div1](https://codeforces.com/contest/949)

[官方题解](https://codeforces.com/blog/entry/58291)

--------vp经过分割线--------

开A题就有一种熟悉的感觉迎面扑来....QwQ

看到B题的图我就有一种强烈的感觉。。这A,B我怕不是都做过。。

然后想了想。。发现自己都不会做（~~不愧是我~~

瞄了几眼后面几题。。。smg...为什么题面这么长（~~这让英语菜鸡怎么活~~

大力搞B啦～。。。。

写了个暴力就过了（~~明明很简单啊。。为什么我可以写这么久qwq~~

为什么啊。。。。。

> - `A`::sloved after the contest
> - `Y`::sloved in the contest
> - `S`::sloving  :sob:

| #        | A    | B    | C    | D    | E    | F    |
| -------- | ---- | ---- | ---- | ---- | ---- | ---- |
| Contest5 | A    | Y    | A    | A    | A    | S    |

--------题(~~瞎~~)解(~~讲~~)题解---------

#### A

~~为什么啊。。这么简单的题目我哭了。。~~

因为肯定是010101这样子的嘛。。

一种是你暴力用**set**搞一搞 贪心肯定是选在当前位置(假设为1)的后面且离它最近的0嘛。。

还有一种方法呢～我觉得还是肥肠巧妙的～qwq

```c++
		if(lx[i] == '0') {
			g[++now].push_back(i);
		} else {
			if(!now) fail();
			g[now--].push_back(i);
		}
```

$O(n)$

#### B

这道题真的很简单啊。。qwq

直接暴力模拟一下就可以了

一个问题可以分成几个子问题嘛。。直接分治就可以了。。

$O(qlogn)$

#### C

关键在于**转换为图**模型

如果$x,y$是一对 那么如果$x$往后移1h等于$y$的话 那么我们就从$x$向$y$连一条有向边(代表选择$x$必定要选择$y$

经过这些操作之后我们可以得到一张有向图

通过tarjian缩点成一张DAG（将强联通分量缩成一个点 【因为强联通分量中的一个点选择了其他点肯定必定要选的哇

那么我们的答案肯定是在出度为0的点中选啦

$O(n)$搞定

#### D

好神仙啊这个贪心。

Q：如何yy这个贪心？

A：~~我咋知道。。~~ 我们肯定会尽量让每个寝室最多只有$b$个人（如果有多的为什么不到别的寝室去救济一下呢qwq

然后题目保证总人数就是$n * b$ 所以下面这个贪心就是对的了。。

对于一个寝室$i$ 如果有人能够在寝室管理员之前到达$i$且使得它的人数大于等于$b$,那就让他们去，否则答案++

分左右两边计算 得到的答案取max即为答案

- 我们不必担心中间的人跑到左边会影响右边的答案使之变差 因为 中间的人跑到左边的前提是左边人数不够 又因为总人数是$n * b$所以就是代表着右边的人数有多 所以答案是不会变劣的

所以$O(n)$扫一遍就可以了qwq

#### E

这个E 也好神仙。。qwq

首先我们必须要知道几个性质（正经脸

- 相同的需要构造的数我们只需要保留一个就可以了（~~显然~~虽然是显然的 但这个性质保证了复杂度qwq
- 选$2^k,2^k$肯定没有$2^k,2^{k+1}$优秀
- 选$-2^k,-2^k$没有$2^k,-2^{k+1}$优秀
- 选$2^k,-2^k$没有$2^k,-2^{k+1}$优秀

所以我们知道了 每一个2的次方我们最多都只会选一个

那么对于二进制下第$k$位

- 所有数的第$k$位都为0 直接到下一位去
- 其中有数的第$k$位不为0 这个时候我们有两种选择$2^k$或者是$-2^k$ 这个我们爆搜就可以解决啦～

这样的复杂度似乎有点高qwq

但是我们可以注意到的是 每往下一层 不重复的数字都在至少减半！

所以复杂度即为$O(nlogn)$



#### F

看不懂 咕咕咕了。。



----------Code分割线---------

##### A

```c++
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
```



##### B

```c++
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll n;

ll get(ll x, ll len, int gg) {
	if((x & 1) == gg) return x / 2 + gg;
	else {
		ll pos = x / 2 + (gg ^ 1);
		return get(pos, (len + (gg ^ 1))/ 2, gg ^ (len & 1)) + (len + gg) / 2;
	}
}

int main() {
	int q;
	scanf("%lld%d", &n, &q);
	for(int o = 1; o <= q; ++o) {
		ll x;
		scanf("%lld", &x);
		printf("%lld\n", get(x, n, 1));
	}
	return 0;
}
```



##### C

```c++
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
struct data {
	int nt, to;
} a[N << 1];
vector <int> g[N];
int w[N];
int tp = 0, c = 0, st[N], d[N];
int dfn[N], low[N], vis[N], col[N];
int head[N], res = 0, cnt = 0;

void add(int x, int y) {
	a[++cnt].to = y;
	a[cnt].nt = head[x];
	head[x] = cnt;
}

void dfs(int x) {
	vis[x] = 1, st[++tp] = x;
	low[x] = dfn[x] = ++res;
	for(int i = head[x]; i; i = a[i].nt) {
		int to = a[i].to;
		if(vis[to]) {
			low[x] = min(low[x], dfn[to]);
		} else if(!dfn[to]) {
			dfs(to);
			low[x] = min(low[x], low[to]);
		}
	}
	if(dfn[x] == low[x]) {
		vis[x] = 0, col[x] = ++c;
		for(;st[tp] != x; tp--) {
			int pos = st[tp];
			vis[pos] = 0;
			col[pos] = c;
			g[c].push_back(pos);
		}
		g[c].push_back(st[tp--]);
	}
}


int main() {
	int n, m, h;
	scanf("%d%d%d", &n, &m, &h);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &w[i]);
	}
	for(int i = 1, x, y; i <= m; ++i) {
		scanf("%d%d", &x, &y);
		if((w[x] + 1) % h == w[y]) add(x, y);
		if((w[y] + 1) % h == w[x]) add(y, x);
	}
	for(int i = 1; i <= n; ++i) {
		if(!dfn[i]) {
			dfs(i);
		}
	}
	for(int u = 1; u <= n; ++u) {
		// printf("%d\n", col[u]);
		for(int i = head[u]; i; i = a[i].nt) {
			int to = a[i].to;
			if(col[u] != col[to]) {
				d[col[u]]++;
			}
		}
	}
	int ans = n + 1, be = 0;
	for(int i = 1; i <= c; ++i) {
		if(!d[i]) {
			int len = g[i].size();
			if(ans > len) {
				ans = len, be = i;
			}
		}
	}
	printf("%d\n", ans);
	for(int i = 0; i < ans; ++i) {
		printf("%d ", g[be][i]);
	}
	return 0;
}
```

##### D

```c++
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e5 + 10;
int a[N];

int main() {
	int n, d, b;
	scanf("%d%d%d", &n, &d, &b);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
	}
	ll sum = 0;
	int ans1 = 0, ans2 = 0;
	for(int i = 1, j = 1; i <= (n + 1) / 2; ++i) {
		for(; j <= min(i * (d + 1), n); ++j) sum += a[j];
		if(sum >= b) sum -= b;
		else ans1++;
	}
	reverse(a + 1, a + 1 + n);
	sum = 0;
	for(int i = 1, j = 1; i <= n / 2; ++i) {
		for(; j <= min(i * (d + 1), n); ++j) sum += a[j];
		if(sum >= b) sum -= b;
		else ans2++;
	}
	printf("%d\n", max(ans1, ans2));
	return 0;
}
```

##### E

```c++
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10, LOG = 25;
int a[LOG][N], d[LOG], c[LOG], ans = 100, now = 0;

void work(int t, int n) {
	if(t >= 20) {
		int flg = 1;
		for(int i = 1; i <= n; ++i) {
			if(a[t][i]) flg = 0;
		}
		if(flg && now < ans) {
			ans = now;
			for(int i = 1; i <= now; ++i) {
				d[i] = c[i];
			}
		}
		return ;
	}
	int flg = 1;
	for(int i = 1; i <= n; ++i)
		if(a[t][i] & 1) {
			flg = 0;
			break;
		}
	if(flg) {
		for(int i = 1; i <= n; ++i) {
			a[t + 1][i] = a[t][i] / 2;
		}
		sort(a[t + 1] + 1, a[t + 1] + 1 + n);
		int m = unique(a[t + 1] + 1, a[t + 1] + 1 + n) - a[t + 1] - 1;
		work(t + 1, m);
	} else {
		for(int i = -1; i <= 1; i += 2){
			for(int j = 1; j <= n; ++j) 
				if(a[t][j] & 1)
					a[t + 1][j] = (a[t][j] + i) / 2;
				else a[t + 1][j] = a[t][j] / 2;
			sort(a[t + 1] + 1, a[t + 1] + 1 + n);
			int m = unique(a[t + 1] + 1, a[t + 1] + 1 + n) - a[t + 1] - 1;
			c[++now] = -i * (1 << t);
			work(t + 1, m);
			--now;
		}
	}
}

int main() {
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &a[0][i]);
	}
	sort(a[0] + 1, a[0] + 1 + n);
	int m = unique(a[0] + 1, a[0] + 1 + n) - a[0] - 1;
	work(0, m);
	printf("%d\n", ans);
	for(int i = 1; i <= ans; ++i) {
		printf("%d ", d[i]);
	}
	return 0;
}

```

