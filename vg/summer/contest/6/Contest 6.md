



### Contest 6

[Codeforces293-Round#174Div1](https://codeforces.com/contest/283)

[官方题解](https://codeforces.com/blog/entry/7036)

> - Y::solved in the contest
> - A::solved after the contest
> - S::solving ::sob:
> - X::tan90

------我是vp分割线------

我也不知道该说啥了。。被自己蠢哭。。

A题明明是个大水题！~~我差点差点差点 就写了线段树。。。（区间修改的那种~~

B题也没有任何思维含量(~~虽然我写了很久~~

完全就是暴力暴力暴力。。注意一下细节就可以了。。~~B题告诉我。。——人要有信仰。。~~

C题咕咕咕。。只会把所有状态都放到dp里面去qwq

D题smg不会再见👋

E题咋又是计数！不会再见👋（事实上这个E题是我做过的Div1最后一道题里面最可做的了qwq

总而言之 感觉这场比赛确实不难。。。

~~最让我骄傲的是 至少我题目还是看得懂的！~~

-----还是写题(~~瞎~~)解(~~讲~~)报告比较好玩------

#### A

大水题！

略～

#### B

泥把这道题转换成<font color="blue">图模型</font>就可以啦！

注意细节就没有问题～

#### C

~~C题是什么sb题。。水的一皮~~

考虑复杂度 遇到dp只会把所有状态都放到dp状态上的你发现 tm只能开个1维的样子

想来想去 你发现有一维是绝对要的

然后智障的你在思考 你要满足这个限制啊

那么先满足最基本的东西嘛。。

就是如果最小的那个选了$x$个 那么与之相联系的硬币你都选$x$个

然后你就发现 这tm是个什么思博题。。

什么思博题！怎么可以这么思博！

打个比方 $num_x < num_y <num_z$

那你把$w_x = a_x + a_y + a_z,w_y = a_y +a_z,w_z=a_z$

然后你再跑个什么多重背包！tm就完事了。

（当然你先要满足最基本的条件。。。

#### D

一道肥肠流弊的题。。。

还是被我的数学菜到了。。

<font color="blue">**首先我们发现这个$n$只有$5000$! 然后我们就可以考虑$n^2$做法啦～**</font>

对于$y$个连续的数 和为$x$ 我们可以推出这么一个式子

$\dfrac{(2*a+y-1)*y}{2}=x$

从而 $2*a-1=\dfrac{2*x-y^2}{y}$

那么我们是不是得出$\dfrac{2*x-y^2}{y}$需要是个奇数

那么我们将数划分成$x=2^p*q$

那么$x,y$需要满足的条件

- $q_x$%$q_y$$=0$

- $p_x+1=p_y$||$p_y=0$

  

我们设$f[i]$表示前$i$个最少需要修改几个

#### E

<font color="blue">**遇难则反**</font>

<font color="blue">**一个三元组$(a,b,c)$不满足条件的情况就是其中一个数的能力大于另外两个数**</font>

我们知道一共有$C_n^3$个三元组

那么一个数$a$打赢另一个数$b$ 情况也只有两种

- 本身$a$就比$b$大 而且反转了偶数次
- 本身$a$就比$b$小 而且反转了奇数次

这种区间反转多少次我们可以放到线段树上去求

现将$a$按从小到大排序 

枚举到一个$i$ 我们将所有以$i$为左端点的区间放到线段树里去

计算完$i$的贡献时 我们就将所有以$i$为右端点的线段从线段树里去除影响

然后你发现你就写完了一道Div1！的最后一题！

撒花花:cherry_blossom:

------Code!------

##### A

```c++
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 2e5 + 10;
ll add[N], a[N];

int main() {
	ll sum = 0;
	int now = 1, n;
	scanf("%d", &n);
	for(int i = 1, tp; i <= n; ++i) {
		scanf("%d", &tp);
		if(tp == 1) {
			int x, y;
			scanf("%d%d", &x, &y);
			add[x] += y;
			sum += 1ll * x * y;
		} else if(tp == 2) {
			int x;
			scanf("%d", &x);
			sum += x, a[++now] = x;
		} else {
			add[now - 1] += add[now];
			sum -= add[now] + a[now];
			add[now] = a[now] = 0;
			now--;
		}
		printf("%.10f\n", double(sum) / double(now));
	}
	return 0;
}
```

##### B

```c++
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e6 + 10;
ll dis[N], a[N];
int vis[N], ed[N], vv[10], res = 0, n;

int zh(int y, int x) {
	return x * n + y;
}

void go(int x, int id) {
	// printf("%d %d\n", x, id);
	int num = zh(x, id);
	if(x == 1) {
		ed[num] = id + 1;
		return ;
	}
	vis[num] = res;
	if(!id) {
		int pos = x + a[x], nid = id ^ 1;
		int tmp = zh(pos, nid);
		if(pos > n) {
			dis[num] = a[x];
			return ;
		} else if(vis[tmp] == vis[num]) {
			dis[num] = -1;
			return ;
		} else {
			if(!vis[tmp]) {
				go(pos, nid);
			}
			if(dis[tmp] == -1) dis[num] = -1;
			else dis[num] = dis[tmp] + a[x];
			ed[num] = ed[tmp];
		}
	} else {
		int pos = x - a[x], nid = id ^ 1;
		int tmp = zh(pos, nid);
		if(pos <= 0) {
			dis[num] = a[x];
			return ;
		} else if(vis[num] == vis[tmp]) {
			dis[num] = -1;
			return ;
		} else {
			if(!vis[tmp]) {
				go(pos, nid);
			}
			if(dis[tmp] == -1) dis[num] = -1;
			else dis[num] = dis[tmp] + a[x];
			ed[num] = ed[tmp];
		}
	}
}

int main() {
	scanf("%d", &n);
	for(int i = 2; i <= n; ++i) {
		cin >> a[i];
	}
	for(int i = 2; i <= n; ++i) 
	 for(int j = 0; j < 2; ++j) {
		if(!vis[zh(i, j)]) {
			++res;
			go(i, j);
		}
	}
	for(int i = 1; i < n; ++i) {
		memset(vv, 0, sizeof vv);
		int tt = zh(i + 1, 1);
		ll pos = dis[tt];
		if(ed[tt] == 1) {
			printf("-1\n");
		} else if(ed[tt] == 2){
			cout << pos + i + i << endl;
		} else {
			if(pos == -1) printf("-1\n");
			else cout << pos + i <<endl;
		}
	}
	return 0;
}
```

##### C

```c++
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e5 + 10, mod = 1e9 + 7;
int a[N], mx[N], my[N], vis[N], w[N];
ll f[N];

int main() {
	int n, q, t;
	scanf("%d%d%d", &n, &q, &t);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
	}
	for(int i = 1, x, y; i <= q; ++i) {
		scanf("%d%d", &x, &y);
		mx[x] = y, my[y] = x;
	}
	for(int i = 1; i <= n; ++i) {
		if(!my[i]) {
			// printf("qwq%d\n", i);
			int tmp = i, pos = a[tmp];
			w[tmp] = pos;
			while(mx[tmp]) {
				t -= pos;
				if(t < 0) return printf("0\n"), 0;
				tmp = mx[tmp];
				pos += a[tmp];
				w[tmp] = pos;
			}
		}
	}
	f[0] = 1;
	for(int i = 1; i <= n; ++i) {
		if(!w[i]) return printf("0\n"), 0;
		for(int j = w[i]; j <= t; ++j) {
			f[j] = (f[j] + f[j - w[i]]) % mod;
		}
	}
	// printf("%d\n", t);
	if(t >= 0) printf("%lld\n", f[t]);
	else {
		printf("0\n");
	}
	return 0;
}
```

##### D

```c++
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 5050;
int f[N];
ll q[N], p[N];

bool check(int x, int y) {
	if(q[x] % q[y]) return false;
	return p[y] - p[x] == y - x || p[y] < y - x;
}

int main() {
	int n;
	scanf("%d", &n);
	for(int i = 0; i < n; ++i) {
		ll x;
		cin >> x;
		p[i] = 0;
		while(x % 2 == 0) p[i]++, x /= 2;
		q[i] = x;
	}
	memset(f, 0x3f, sizeof f);
	f[0] = 0, q[n] = 1;
	for(int i = 1; i <= n; ++i) {
		f[i] = i;
		for(int j = 0; j < i; ++j) {
			if(check(j, i)) {
				f[i] = min(f[i], f[j] + i - j - 1);
			}
		}
	}
	printf("%d\n", f[n]);
	return 0;
}
```

##### E

```c++
#include<bits/stdc++.h>
#define ls x << 1
#define rs x << 1 | 1
#define ll long long
using namespace std;
const int N = 1e5 + 10;
struct data {
	int l, r;
} xd[N];
struct node {
	int js, os;
} tr[N << 2];
vector<int> b[N], e[N];
int a[N], all[N << 2];
int rev[N << 2], n, k;

int getl(int x) {
	int l = 1, r = n, ans = 1;
	while(l <= r) {
		int mid = (l + r) >> 1;
		if(all[mid] >= x) r = mid - 1, ans = mid;
		else l = mid + 1;
	}
	return ans;
}

int getr(int x) {
	int l = 1, r = n, ans = n;
	while(l <= r) {
		int mid = (l + r) >> 1;
		if(all[mid] <= x) l = mid + 1, ans = mid;
		else r = mid - 1;
	}
	return ans;
}

node merge(node A, node B) {
	node res;
	res.js = A.js + B.js;
	res.os = A.os + B.os;
	return res;
}

void build(int x, int l, int r) {
	if(l == r) {
		tr[x].os = 1;
		tr[x].js = 0;
		return ;
	}
	int mid = (l + r) >> 1;
	build(ls, l, mid), build(rs, mid + 1, r);
	tr[x] = merge(tr[ls], tr[rs]);
}

void down(int x) {
	if(rev[x]) {
		rev[x] = 0;
		rev[ls] ^= 1;
		rev[rs] ^= 1;
		swap(tr[ls].os, tr[ls].js);
		swap(tr[rs].os, tr[rs].js);
	}
}

void put(int x, int l, int r, int L, int R) {
	// printf("x=%d l=%d r=%d\n", x,l,r);
	if(L <= l && r <= R) {
		rev[x] ^= 1;
		swap(tr[x].os, tr[x].js);
		// printf("qwqx=%d l=%d r=%d os=%d js=%d\n",x,l,r,tr[x].js,tr[x].os);
		return ;
	}
	down(x);
	int mid = (l + r) >> 1;
	if(L <= mid) put(ls, l, mid, L, R);
	if(R > mid) put(rs, mid + 1, r, L, R);
	tr[x] = merge(tr[ls], tr[rs]);
	// printf("x=%d l=%d r=%d os=%d js=%d\n", x, l, r, tr[x].os,tr[x].js);
}

node get(int x, int l, int r, int L, int R) {
	if(L > R) {
		return (node){0, 0};
	}
	if(L <= l && r <= R) {
		return tr[x];
	}
	down(x);
	int mid = (l + r) >> 1;
	node ans1, ans2;
	if(L <= mid) ans1 = get(ls, l, mid, L, R);
	else ans1.js = ans1.os = 0;
	if(R > mid) ans2 = get(rs, mid + 1, r, L, R);
	else ans2.js = ans2.os = 0;
	tr[x] = merge(tr[ls], tr[rs]);
	return merge(ans1, ans2);
}

int main() {
	scanf("%d%d", &n, &k);
	int res = 0;
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
		all[i] = a[i];
	}
	sort(a + 1, a + 1 + n), sort(all + 1, all + 1 + n);
	for(int i = 1; i <= n; ++i) {
		a[i] = lower_bound(all + 1, all + 1 + n, a[i]) - all;
	}
	for(int i = 1; i <= k; ++i) {
		scanf("%d%d", &xd[i].l, &xd[i].r);
		xd[i].l = getl(xd[i].l);
		xd[i].r = getr(xd[i].r);
		b[xd[i].l].push_back(i), e[xd[i].r].push_back(i);
	}
	ll ans = 1ll * n * (n - 1) * (n - 2) / 6;
	build(1, 1, n);
	for(int i = 1, len; i <= n; ++i) {
		// printf("qwq%d\n", i);
		len = b[i].size();
		for(int j = 0; j < len; ++j) {
			// printf("%d %d\n", xd[b[i][j]].l, xd[b[i][j]].r);
			put(1, 1, n, xd[b[i][j]].l, xd[b[i][j]].r);
		}
		ll tmp = 0;
		tmp += get(1, 1, n, 1, i - 1).os + get(1, 1, n, i + 1, n).js;
		// printf("%lld\n", tmp);
		ans -= tmp * (tmp - 1) / 2;
		len = e[i].size();
		for(int j = 0; j < len; ++j) {
			put(1, 1, n, xd[e[i][j]].l, xd[e[i][j]].r);
		}
	}
	printf("%lld\n", ans);
	return 0;
}
```

事实上我也不知道为什么我的代码是别人的两倍长qwq