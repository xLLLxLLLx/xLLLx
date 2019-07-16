### Contest10

[Codeforces930-Round#468Div1](codeforces.com/contest/930)

[官方题解](https://codeforces.com/blog/entry/58177)

-------

A，B，C都好水啊～

B题题意一直没有理解对。。导致我对着样例一脸mengbier。。。

--------------

#### D

> 首先你要发现黑点和白点的横纵坐标的奇偶性必须要相同 才可以挡住白点
>
> 白点的四个方向上都要有黑点才能挡住
>
> ![](https://codeforces.com/predownloaded/b6/7e/b67ea479544dd0eee6c25579333e2e9722f56201.png)

那我们把黑点按照横纵坐标和的奇偶性分成两类 分别计算

发现这个斜着的区域肥肠难求 那么我们将它转个45度长度再扩大个$\sqrt2$倍

![](https://codeforces.com/predownloaded/eb/b8/ebb865f1cf1b82a9309fc393c12729aed6f57e14.png)

那就肥肠好求了(此时$(x,y)->(x+y,x-y)$

#### E

> 可以想到 其实不用一个位置一个位置去考虑过去 而是由题目所给的端点为关键点
>
> 关键点又把整个区间划分成了一个个小区间 而这一个个小区间是可以一起计算的
>
> 又考虑到 这一个个小区间如果都有`1`和有`0` 那么肯定是满足条件的
>
> 我们漏算的其实是这一个个小区间可以全部是1或者是0的情况
>
> 于是就有了下面的dp

什么[神仙题解](https://www.cnblogs.com/skylee03/p/9078791.html)！

是个肥肠厉害的dp!

大侠们我去ban题解了！

![](http://chuantu.xyz/t6/702/1563181655x2073530529.png)

解释一下这个转移方程好了。。
$$
f[i][0]=f[i+1][0]+(f[i+1][1]-f[min[1][i+1]][1])+f[i+1][2]*(2^{tmp[i+1]-tmp[1]}-2)
$$
$f[i][0]$的意义是啥 后缀和对吧 那么我们吧$+f[i+1][0]$这一项先不管了 

$+f[i+1][2]*(2^{tmp[i+1]-tmp[i]}-2)$ 这一项是啥？是不是$(tmp[i],tmp[i+1]]$这个小区间随便取（去掉全是0和全是1的情况）

最后我们看看这~~毒瘤~~的一项 $f[i+1][1]-f[min[1][i+1]][1]$ 

事实上先不算上面毒瘤的一项 我们计算到$f[i][0]$里面的并没有$(tmp[i],tmp[i+1]]$这个小区间里面全是0的情况

所以就加上$1*(f[i+1][1]-f[min[1][i+1]][1])$这一项啦～（`1`代表$(tmp[i],tmp[i+1]]$这个小区间里面全是0

其他两个转移方程道理就是一样的啦～
$$
f[i][1]=f[i+1][1]+(f[i+1][0]-f[min[1][i+1]][0])+f[i+1][2]*(2^{tmp[i+1]-tmp[1]}-2)
$$

$$
f[i][2]=(f[i+1][0]-f[min[0][i+1]][0])+(f[i+1][1]-f[min[1][i+1]][1])+f[i+1][2]*(2^{tmp[i+1]-tmp[1]}-2)
$$



-----

Code

##### A

```c++
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
struct data {
	int nt, to;
} a[N];
int dep[N], col[N], head[N], cnt = 0;

void add(int x, int y) {
	a[++cnt].to = y;
	a[cnt].nt = head[x];
	head[x] = cnt;
}

void dfs(int x, int fa) {
	dep[x] = dep[fa] + 1;
	for(int i = head[x]; i; i = a[i].nt) {
		dfs(a[i].to, x);
	}
}

int main() {
	int n;
	scanf("%d", &n);
	for(int i = 2, p; i <= n; ++i) {
		scanf("%d", &p);
		add(p, i);
	}
	dfs(1, 0);
	int ans = 0;
	for(int i = 1; i <= n; ++i) {
		col[dep[i]]++;
	}
	for(int i = 1; i <= n; ++i) {
		ans += (col[i] & 1);
	}
	printf("%d\n", ans);
	return 0;
}
```

#### B

```c++
#include <bits/stdc++.h>
using namespace std;
const int N = 5010;
vector<int> g[N];
int a[N][26], v[N];
double c[N];
char lx[N];
//renshazidaidachangshu
int main() {
	scanf("%s", lx + 1);
	int n = strlen(lx + 1);
	for(int i = 1; i <= n; ++i) {
		v[i] = lx[i] - 'a' + 1;
		g[v[i]].push_back(i);
	}
	double ans = 0;
	for(int i = 1; i <= 26; ++i) {
		int len = g[i].size();
		if(!len) continue;
		for(int j = 0; j < len; ++j) {
			int fi = g[i][j];
			for(int k = fi; k <= n; ++k) {
				a[k - fi + 1][v[k]]++;
				// printf("%c", char(v[k] + 'a' - 1));
			}
			for(int k = 1; k < fi; ++k) {
				a[n - fi + 1 + k][v[k]]++;
				// printf("%c", char(v[k] + 'a' - 1));
			}
			// puts("");
		}
		int tmp = 0;
		for(int j = 1; j <= n; ++j) {
			int pos = 0;
			for(int k = 1; k <= 26; ++k) {
				pos += (a[j][k] == 1);
				a[j][k] = 0;
			}
			tmp = max(tmp, pos);
		}
		ans += (double)tmp / (double) n;
	}
	printf("%.12f\n", ans);
	return 0;
}
```

##### C

```c++
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int a[N], tr[N], dp[N], f[N];

int lower(int x) {
	return x & (-x);
}

void upd(int x, int y) {
	for(; x < N; x += lower(x)) tr[x] = max(tr[x], y);
}

int get(int x) {
	int ans = 0;
	for(; x; x -= lower(x)) ans = max(ans, tr[x]);
	return ans;
}

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	for(int i = 1, x, y; i <= n; ++i) {
		scanf("%d%d", &x, &y);
		a[x]++, a[y + 1]--;
	}
	for(int i = 1; i <= m; ++i) a[i] += a[i - 1];
	for(int i = 1; i <= m; ++i) a[i]++;
	dp[0] = 0;
	for(int i = 1; i <= m; ++i) {
		dp[i] = get(a[i]) + 1;
		upd(a[i], dp[i]);
	}
	int ans = 0;
	memset(tr, 0, sizeof tr);
	reverse(a + 1, a + 1 + m);
	f[0] = 0;
	for(int i = 1; i <= m; ++i) {
		f[i] = get(a[i]) + 1;
		upd(a[i], f[i]);
	}
	for(int i = 1; i <= m; ++i) {
		ans = max(ans, f[i] + dp[m - i + 1] - 1);
	}
	printf("%d\n", ans);
	return 0;
}
```

##### D

```c++
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 4e5 + 10, M = 1e5 + 10;
struct data {
	int x, y;
} a[M][2];
int num[2];
int bmax[N], bmin[N], amax[N], amin[N];

int add = 2e5;
ll ans = 0;

void Min(int &x, int y) {
	x = min(x, y);
}

void Max(int &x, int y) {
	x = max(x, y);
}

void work(int now) {
	memset(bmin, 0x3f, sizeof bmin);
	memset(amin, 0x3f, sizeof amin);
	memset(bmax, 0, sizeof bmax);
	memset(amax, 0, sizeof amax);
	for(int i = 1; i <= num[now]; ++i) {
		Min(bmin[a[i][now].x], a[i][now].y);
		Min(amin[a[i][now].x], a[i][now].y);
		Max(bmax[a[i][now].x], a[i][now].y);
		Max(amax[a[i][now].x], a[i][now].y);
	}
	for(int i = 1; i < N; ++i) {
		Min(bmin[i], bmin[i - 1]);
		Max(bmax[i], bmax[i - 1]);
	}
	for(int i = N - 2; i >= 0; --i) {
		Min(amin[i], amin[i + 1]);
		Max(amax[i], amax[i + 1]);
	}
	for(int i = 1; i < N; i += 2) {
		int pos = min(bmax[i], amax[i]);
		int tmp = max(bmin[i], amin[i]);
		if(pos > tmp) ans += 1ll * (pos - tmp) / 2;
	}
}

int main() {
	int n;
	scanf("%d", &n);
	for(int i = 1, x, y; i <= n; ++i) {
		scanf("%d%d", &x, &y);
		int pos = (x + y + add) & 1;
		a[++num[pos]][pos].x = x + y + add + pos;
		a[num[pos]][pos].y = x - y + add + pos; 
	}
	for(int i = 0; i < 2; ++i) {
		work(i);
		// printf("%lld\n", ans);
	}
	printf("%lld\n", ans);
	return 0;
}
```

##### E

```c++
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e5 + 10, mod = 1e9 + 7;
struct data {
	int l, r;
} a[N], b[N];
ll f[N << 2][3];
int all[N << 2], nx[N << 2][2];
int k, n, m, tot, cnt = 0;

ll add(ll x, ll y) {
	return (x + y + mod) % mod;
}

ll mul(ll x, ll y) {
	return (x * y) % mod;
}

void Mul(ll &x, ll y) {
	x = (x * y) % mod;
}

ll q_pow(ll x, int y) {
	ll ans = 1;
	for(; y; y >>= 1) {
		if(y & 1) Mul(ans, x);
		Mul(x, x);
	}
	return ans;
}

void Min(int &x, int y) {
	x = min(x, y);
}

int get(int x) {
	return lower_bound(all + 1, all + 1 + tot, x) - all;
}

int main() {
	scanf("%d%d%d", &k, &n, &m);
	all[++cnt] = 0;
	for(int i = 1; i <= n; ++i) {
		scanf("%d%d", &a[i].l, &a[i].r);
		a[i].l--;
		all[++cnt] = a[i].l, all[++cnt] = a[i].r;
	}
	for(int i = 1; i <= m; ++i) {
		scanf("%d%d", &b[i].l, &b[i].r);
		b[i].l--;
		all[++cnt] = b[i].l, all[++cnt] = b[i].r;
	}
	all[++cnt] = k;
	sort(all + 1, all + 1 + cnt);
	tot = unique(all + 1, all + 1 + cnt) - all - 1;
	for(int i = 1; i <= tot; ++i) {
		nx[i][0] = nx[i][1] = tot + 1;
	}
	for(int i = 1; i <= n; ++i) {
		a[i].l = get(a[i].l), a[i].r = get(a[i].r);
		Min(nx[a[i].l][0], a[i].r);
	}
	for(int i = 1; i <= m; ++i) {
		b[i].l = get(b[i].l), b[i].r = get(b[i].r);
		Min(nx[b[i].l][1], b[i].r);
	}
	for(int i = tot - 1; i >= 1; --i) {
		Min(nx[i][0], nx[i + 1][0]);
		Min(nx[i][1], nx[i + 1][1]);
	}
	f[tot][0] = f[tot][1] = f[tot][2] = 1;
	for(int i = tot - 1; i >= 1; --i) {
		ll g0 = add(f[i + 1][0], -f[nx[i][0]][0]);
		ll g1 = add(f[i + 1][1], -f[nx[i][1]][1]);
		ll g2 = mul(f[i + 1][2], add(q_pow(2, all[i + 1] - all[i]), -2));
		f[i][0] = add(f[i + 1][0], add(g1, g2));
		f[i][1] = add(f[i + 1][1], add(g0, g2));
		f[i][2] = add(g0, add(g1, g2));
	}
	printf("%lld\n", f[1][2]);
	return 0;
}
```

