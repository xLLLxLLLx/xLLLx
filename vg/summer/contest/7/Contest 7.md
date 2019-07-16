### Contest 7

[Codeforces1109-Round#539Div1](https://codeforces.com/contest/1109)

[官方题解](https://codeforces.com/blog/entry/65295)



---------------

总之我也不知道为什么zzd大神说这场很好涨分qwq

大概是有一道肥肠套路的E？？（~~好涨分也不妨碍我gg~~

A题简直就是~~超级大水题。。怎么div2C变成这个样子qwq~~

B题也是道结论题的样子呢。。可我竟然有一种更优的方案没想到。。(~~智商直线下滑~~

C题就是道无良数据结构题。。反正就是~~那种道理我都懂啥也不会写的感觉~~

D题tm又是道结论题。。不过这个结论好神啊！而且应用也很神仙啊。。（感觉就像是我知道有这么一个结论也还是不会做的感觉。。

E题。。线段树暴写题。。主要还是处理模数不是质数的时候。。用到了点CRT合并

F题。。tm又是数据结构！LCT+线段树！加上我的神奇码风 200+行。。

~~我能说什么。。这场简直就是毒瘤好吗。。。~~

------

终于到了愉快的写题解环节（并不

#### A

太水了我们直接跳过

#### B

好一道牛逼的题目。。。

注意到一点 最极限的情况下 我们可以把所有的字母都拆出来！

然后无解的情况很显然了

然后在有解的情况下 我们最多也只用切2刀就一定可以了 而且至少也要切1刀

然后对于长度为偶数的字符串 如果中间切开 两边如果不是回文串的话 那么就是1刀啦～

#### C

> 按题意模拟一下嘛。。

线段树平衡树挑一个写写（反正两个都不会好写到哪里去。。

线段树可能好写一点？（不过我感觉线段树的预处理比较麻烦

#### D

> 结论题。。。

丢几个链接🔗

[Cold_Chair](https://blog.csdn.net/Cold_Chair/article/details/87558803)  	[ymzqwq](https://blog.csdn.net/ymzqwq/article/details/87633376)		[论文](https://www.sciencedirect.com/science/article/pii/0097316590900644?via%3Dihub)

首先呢 作为智商不是负数的泥 发现

你可以枚举$a,b$之间有多少条边啊 我们设为$x$

有$x$条边就说明我们要选$x-1$个点 $A_{n-2}^{x-1}$

又边的和为$m$ 则由挡板法 可得$C_{m-1}^{x-1}$

其他边随意$m^{n-1-x}$
$$
ans=树的个数*A_{n-2}^{x-1}*C_{m-1}^{x-1}*m^{n-1-x}
$$
**拓展Cayley公式**

设$F(n,m)$表示$n$个点组成$m$个有标号的森林的个数，$1-m$属于不同的树
$$
F(n,m)=m*n^{n-1-m}
$$
**prüfer序列**

[Martrix67!!!!写得超级好！！](http://www.matrix67.com/blog/archives/682)

#### E

> 事实上。。你可以把这个<font color="blue">**模数给质因数分解一下**</font>。。
> $$
> p = p_1^{k_1}p_2^{k_2}p_3^{k_3}…*p_t^{k_t}
> $$
> 把所有要操作的数$w$ 都变成
> $$
> w=v*p_1^{l_1}*p2^{l_2}...*p_t^{l_t}
> $$
> 其中$v$和$p$互质 那么$v$就拥有模$p$意义下的逆元啦！



看到题目泥会发现 1，3两个操作。。你随便写颗线段树就可以了

如果模数是个质数的话 1，2，3都可以随便写颗线段树了。。。

但是 这个模数不是个质数。。。那就并不是每一个数都有在膜p意义下的逆元了。。

事实上。。你可以把这个<font color="blue">**模数给质因数分解一下**</font>。。
$$
p = p_1^{k_1}p_2^{k_2}p_3^{k_3}…*p_t^{k_t}
$$
把所有要操作的数$w$ 都变成
$$
w=v*p_1^{l_1}*p2^{l_2}...*p_k^{l_k}
$$
其中$v$和$p$互质 那么$v$就拥有模$p$意义下的逆元啦！

线段树直接维护这些东西就行了



#### F

> 判断是否是树的时候 我们可以先判断是否是森林 然后再判断点数-边数是否等于1

我们可以发现对于一个$l$ 存在一个最大的$r$使得$(l,r)$是一个森林，$r->r+1$时就会有环出现

且$l ->l +1$时 $r$不会变小 类似于two-pointer处理一下就行啦

怎么样可以快速判环？交给lct！

如何求得区间点数-边数的最小值 和最小值有几个？ 交给线段树！



------------

代码区（~~总之我觉得自己的代码写的肥肠好看而且浅显易懂~~

##### A

```c++
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 3e5 + 10, M = 2e6 + 10;
int a[M][2];

int main() {
	int n, now = 0;
	scanf("%d", &n);
	ll ans = 0;
	a[0][0]++;
	for(int i = 1, x; i <= n; ++i) {
		scanf("%d", &x);
		now ^= x;
		int pos = i & 1;
		ans += a[now][pos];
		a[now][pos]++;
		// printf("%d %d\n", i, now);
	}
	printf("%lld\n", ans);
	return 0;
}
```

##### B

```c++
#include <bits/stdc++.h>
using namespace std;
const int N = 5010;
char lx[N];

void fail() {
	printf("Impossible\n");
	exit(0);
}

bool check(int l, int r) {
	for(int i = l; i <= r; ++i) {
		if(lx[i] != lx[r - i + l]) return false;
	}
	return true;
}

bool go(int x) {
	if(x & 1) return true;
	int mid = x / 2;
	if(check(1, mid)) {
		return go(mid);
	} else return false;
}

int main() {
	scanf("%s", lx + 1);
	int len = strlen(lx + 1);
	if(len == 1) fail();
	int flg = 1, pos = lx[1] - 'a' + 1;
	if(len & 1) {
		for(int i = 1; i <= len; ++i) {
			if(i == len / 2 + 1) continue;
			if(lx[i] - 'a' + 1 != pos) flg = 0;
		}
	} else {
		for(int i = 1; i <= len; ++i) {
			if(lx[i] - 'a' + 1 != pos) flg = 0;
		}
	}
	if(flg) fail();
	else {
		if(len & 1) {
			printf("2\n");
		} else {
			if(go(len)) printf("2\n");
				else printf("1\n");
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
const int N = 1e6 + 10, inf = 1e9;
struct data {
	ll tr, tl, sr, s, t, res, minn;
	int rd, ch[2];
	void print() {
		printf("tr=%d tl=%d sr=%d s=%d t=%d res=%d minn=%d ls=%d rs=%d\n", rd,tr,tl,sr,s,t,res,minn,ch[0],ch[1]); 
	}
} t[N];

void up(int x) {
	if(t[x].ch[0]) {
		t[x].tl = t[t[x].ch[0]].tl;
	} else t[x].tl = t[x].t;
	if(t[x].ch[1]) {
		t[x].tr = t[t[x].ch[1]].tr;
		t[x].sr = t[t[x].ch[1]].sr;
	} else {
		t[x].tr = t[x].t;
		t[x].sr = t[x].s;
	}
	t[x].res = 0, t[x].minn = 0;
	if(t[x].ch[0]) {
		t[x].minn = max(t[x].minn, t[t[x].ch[0]].minn);
		t[x].res += t[t[x].ch[0]].res;
		t[x].res += t[t[x].ch[0]].sr * (t[x].t - t[t[x].ch[0]].tr);
		t[x].minn = max(t[x].minn, -t[x].res);
	}
	if(t[x].ch[1]) {
		t[x].res += t[x].s * (t[t[x].ch[1]].tl - t[x].t);
		t[x].minn = max(t[x].minn, -t[x].res);
		t[x].minn = max(t[x].minn, -t[x].res + t[t[x].ch[1]].minn);
		t[x].res += t[t[x].ch[1]].res;
	}
}

void split(int now, int &x, int &y, ll k) {
	if(!now) {
		x = y = 0;
		return ;
	}
	if(t[now].t <= k) {
		x = now, split(t[now].ch[1], t[now].ch[1], y, k);
	} else {
		y = now, split(t[now].ch[0], x, t[now].ch[0], k);
	}
	up(now);
}

int merge(int x, int y) {
	if(!x || !y) return x ^ y;
	if(t[x].rd < t[y].rd) {
		t[x].ch[1] = merge(t[x].ch[1], y);
		up(x);
		return x;
	} else {
		t[y].ch[0] = merge(x, t[y].ch[0]);
		up(y);
		return y;
	}
}

double ask(int x, ll w) {
	if(t[x].ch[0]) {
		if(w <= t[t[x].ch[0]].minn) {
			return ask(t[x].ch[0], w);
		}
		w += t[t[x].ch[0]].res;
		if(w + t[t[x].ch[0]].sr * (t[x].t - t[t[x].ch[0]].tr) <= 0) {
			return t[t[x].ch[0]].tr - (double)w / t[t[x].ch[0]].sr;
		}
		w += t[t[x].ch[0]].sr * (t[x].t - t[t[x].ch[0]].tr);
	}
	if(t[x].ch[1]) {
		if(w + t[x].s * (t[t[x].ch[1]].tl - t[x].t) <= 0) {
			return t[x].t - (double)w / t[x].s;
		}
		w += t[x].s * (t[t[x].ch[1]].tl - t[x].t);
		return ask(t[x].ch[1], w);
	}
	return t[x].t - (double)w / t[x].s;
}

int main() {
	srand(time(NULL));
	int n, root = 0, cnt = 0, dx, dy, dz, dw;
	scanf("%d", &n);
	for(int i = 1, opt; i <= n; ++i) {
		scanf("%d", &opt);
		// printf("root=%d\n", root);
		if(opt == 1) {
			++cnt;
			scanf("%lld%lld", &t[cnt].t, &t[cnt].s);
			t[cnt].tl = t[cnt].tr = t[cnt].t;
			t[cnt].sr = t[cnt].s;
			t[cnt].rd = rand() % inf;
			t[cnt].ch[0] = t[cnt].ch[1] = 0;
			split(root, dx, dy, t[cnt].t);
			root = merge(merge(dx, cnt), dy);
		} else if(opt == 2) {
			int l;
			scanf("%lld", &l);
			split(root, dx, dy, l);
			split(dx, dz, dw, l - 1);
			root = merge(dz, dy);
		} else {
			ll l, r, w;
			scanf("%lld%lld%lld", &l, &r, &w);
			if(!w) {
				printf("%.8f\n", double(l));
				continue;
			}
			split(root, dx, dy, r);
			split(dx, dz, dw, l - 1);
			if(!dw) {
				printf("-1\n");
			} else if(w > t[dw].minn) {
				w += t[dw].res;
				if(w + (r - t[dw].tr) * t[dw].sr <= 0) {
					printf("%.8f\n", t[dw].tr - (double)w / t[dw].sr);
				} else printf("-1\n");
			} else printf("%.8f\n", ask(dw, w));
			root = merge(merge(dz, dw), dy);
		}
	}
	return 0;
}
```

##### D

```c++
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e6 + 10, mod = 1e9 + 7;
ll jc[N] = {1}, ny[N] = {1};

ll q_pow(ll x, int y) {
	ll ans = 1;
	for(; y; y >>= 1) {
		if(y & 1) {
			ans = ans * x % mod;
		}
		x = x * x % mod;
	}
	return ans;
}

ll C(int x, int y) {
	if(y > x) return 0ll;
	return jc[x] * ny[y] % mod * ny[x - y] % mod;
}

ll A(int x, int y) {
	return jc[x] * ny[x - y] % mod;
}

int main() {
	int n, m, a, b;
	cin >> n >> m >> a >> b;
	ll ans = 0;
	for(int i = 1; i < N; ++i) jc[i] = jc[i - 1] * i % mod, ny[i] = q_pow(jc[i], mod - 2);
	for(int i = 1; i <= n - 1; ++i) {
		ll pos = A(n - 2, i - 1) * q_pow(m, n - 1 - i) % mod * C(m - 1, i - 1) % mod;
		if(i != n - 1) pos = pos * (i + 1) % mod * q_pow(n, n - i - 2) % mod;
		ans = (ans + pos) % mod;
	}
	printf("%lld\n", ans);
	return 0;
}
```

##### E

```c++
#include <bits/stdc++.h>
#define ll long long
#define ls x << 1
#define rs x << 1 | 1
using namespace std;
const int N = 1e5 + 10;
ll tr[N << 2][20], tag[N << 2], sum[N << 2];
int yz[15], c[15], val[N];
int mod, phi;

ll mul(ll x, ll y) {
	return x * y % mod;
}

ll add(ll x, ll y) {
	return (x + y) % mod;
}

void Add(ll &x, ll y) {
	x = (x + y) % mod;
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

ll rev(ll x) {
	return q_pow(x, phi - 1);
}

void getphi(int x) {
	int len = sqrt(x);
	phi = x;
	for(int i = 2; i <= len; ++i) {
		if(x % i == 0) {
			yz[++yz[0]] = i;
			phi = phi / i * (i - 1);
			while(x % i == 0) x /= i;
		}
	}
	if(x > 1) yz[++yz[0]] = x, phi = phi / x * (x - 1);
}

void get(int x, int &y) {
	memset(c, 0, sizeof c);
	for(int i = 1; i <= yz[0]; ++i) {
		while(x % yz[i] == 0) {
			x /= yz[i], c[i]++;
		}
	}
	y = x % mod;
}

ll cal(int x) {
	ll ans = 1;
	for(int i = 1; i <= yz[0]; ++i) {
		Mul(ans, q_pow(yz[i], tr[x][i]));
	}
	return ans;
}

void up(int x) {
	sum[x] = add(sum[ls], sum[rs]);
}

void down(int x) {
	ll pos = cal(x);
	for(int i = 1; i <= yz[0]; ++i) {
		tr[ls][i] += tr[x][i];
		tr[rs][i] += tr[x][i];
		tr[x][i] = 0;
	}
	Mul(tag[ls], tag[x]), Mul(sum[ls], mul(tag[x], pos));
	Mul(tag[rs], tag[x]), Mul(sum[rs], mul(tag[x], pos));
	tag[x] = 1;
}

void build(int x, int l, int r) {
	tag[x] = 1;
	if(l == r) {
		sum[x] = val[l] % mod;
		for(int i = 1; i <= yz[0]; ++i) {
			while(val[l] % yz[i] == 0) {
				val[l] /= yz[i];
				tr[x][i]++;
			}
		}
		tag[x] = val[l] % mod;
		return ;
	}
	int mid = (l + r) >> 1;
	build(ls, l, mid), build(rs, mid + 1, r);
	up(x);
}

void modify(int x, int l, int r, int L, int R, ll real, ll v) {
	if(L <= l && r <= R) {
		for(int i = 1; i <= yz[0]; ++i) {
			tr[x][i] += c[i];
		}
		Mul(tag[x], v);
		Mul(sum[x], real);
		return ;
	}
	down(x);
	int mid = (l + r) >> 1;
	if(L <= mid) modify(ls, l, mid, L, R, real, v);
	if(R > mid) modify(rs, mid + 1, r, L, R, real, v);
	up(x);
}

void change(int x, int l, int r, int L, ll v) {
	if(l == r) {
		for(int i = 1; i <= yz[0]; ++i) {
			tr[x][i] -= c[i];
		}
		Mul(tag[x], rev(v));
		sum[x] = mul(cal(x), tag[x]);
		return ;
	}
	down(x);
	int mid = (l + r) >> 1;
	if(L <= mid) change(ls, l, mid, L, v);
	else change(rs, mid + 1, r, L, v);
	up(x);
}

ll ask(int x, int l, int r, int L, int R) {
	if(L <= l && r <= R) {
		return sum[x];
	}
	down(x);
	int mid = (l + r) >> 1;
	ll ans1 = 0, ans2 = 0;
	if(L <= mid) ans1 = ask(ls, l, mid, L, R);
	if(R > mid) ans2 = ask(rs, mid + 1, r, L, R);
	return add(ans1, ans2);
}

int main() {
	int n;
	scanf("%d%d", &n, &mod);
	getphi(mod);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &val[i]);
	}
	build(1, 1, n);
	int q;
	scanf("%d", &q);
	for(int i = 1; i <= q; ++i) {
		int opt;
		scanf("%d", &opt);
		if(opt == 1) {
			int l, r, real, v;
			scanf("%d%d%d", &l, &r, &real);
			get(real, v);
			modify(1, 1, n, l, r, real, v);
		} else if(opt == 2) {
			int p, real, v;
			scanf("%d%d", &p, &real);
			get(real, v);
			change(1, 1, n, p, v);
		} else {
			int l, r;
			scanf("%d%d", &l, &r);
			printf("%lld\n", ask(1, 1, n, l, r) % mod);
		}
	}
	return 0;
}
```

##### F

```c++
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1001, M = 2e5 + 1;

/* LCT */
struct LCT {
	int f[M], ch[M][2];
	bool rev[M];

	#define ls ch[x][0]
	#define rs ch[x][1]

	bool isroot(int x) {
		return (ch[f[x]][0] != x) && (ch[f[x]][1] != x);
	}

	void Rev(int x) {
		swap(ls, rs);
		rev[x] ^= 1;
	}

	void down(int x) {
		if(rev[x]) {
			Rev(ls), Rev(rs);
			rev[x] = 0;
		}
	}

	void pushdown(int x) {
		if(f[x]) pushdown(f[x]);
		down(x);
	}

	void rotate(int x) {
		int y = f[x], z = f[y], k = (ch[z][1] == y), d = (ch[y][1] == x);
		if(!isroot(y)) {
			ch[z][k] = x;
		}
		f[x] = z;
		ch[y][d] = ch[x][d ^ 1], f[ch[x][d ^ 1]] = y;
		ch[x][d ^ 1] = y, f[y] = x;
	}

	void splay(int x) {
		pushdown(x);
		while(!isroot(x)) {
			int y = f[x], z = f[y];
			if(!isroot(y)) 
				(ch[z][1] == y) ^ (ch[y][1] == x) ? rotate(x) : rotate(y);
			rotate(x);
		}
	}

	void access(int x) {
		for(int y = 0; x; y = x, x = f[x]) {
			splay(x);
			rs = y;
		}
	}

	void makeroot(int x) {
		access(x);
		splay(x);
		Rev(x);
	}

	int findroot(int x) {
		access(x);
		splay(x);
		for(; ls; down(x), x = ls) {
			splay(x);
		}
		return x;
	}

	void split(int x, int y) {
		makeroot(x);
		access(y);
		splay(y);
	}

	void link(int x, int y) {
		makeroot(x), f[x] = y;
	}

	void cut(int x, int y) {
		split(x, y), f[x] = ch[y][0] = 0;
	}
} T;

/* LCT */

/* segtree */

#define lson x << 1
#define rson x << 1 | 1
int sum[M << 2], tag[M << 2], v[M << 2];

int maxn, num;

void up(int x) {
	v[x] = min(v[lson], v[rson]), sum[x] = 0;
	if(v[lson] == v[x]) sum[x] += sum[lson];
	if(v[rson] == v[x]) sum[x] += sum[rson];
}

void down(int x) {	
	if(tag[x]) {
		tag[lson] += tag[x], v[lson] += tag[x];
		tag[rson] += tag[x], v[rson] += tag[x];
		tag[x] = 0;
	}
}

void check(int x) {
	if(v[x] < maxn) {
		maxn = v[x], num = sum[x];
	} else if(v[x] == maxn) {
		num += sum[x];
	}
}

void build(int x, int l, int r) {
	if(l == r) {
		sum[x] = r - l + 1;
		v[x] = 0;
		return ;
	}
	int mid = (l + r) >> 1;
	build(lson, l, mid), build(rson, mid + 1, r);
	up(x);
}

void change(int x, int l, int r, int L, int R, int w) {
	if(L <= l && r <= R) {
		tag[x] += w;
		v[x] += w;
		return ;
	}
	down(x);
	int mid = (l + r) >> 1;
	if(L <= mid) change(lson, l, mid, L, R, w);
	if(R > mid) change(rson, mid + 1, r, L, R, w);
	up(x);
}

void ask(int x, int l, int r, int L, int R) {
	if(L <= l && r <= R) {
		check(x);
		return ;
	}
	down(x);
	int mid = (l + r) >> 1;
	if(L <= mid) ask(lson, l, mid, L, R);
	if(R > mid) ask(rson, mid + 1, r, L, R);
	up(x);
}
/* segtree */

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
int a[N][N], idx[M], idy[M];

int n, m, nowl = 1, nowr = 1, p[10];

bool judge() {
	p[0] = 0;
	for(int i = 0; i < 4; ++i) {
		int x = idx[nowr + 1] + dx[i], y = idy[nowr + 1] + dy[i];
		if(!x || !y || x > n || y > m || a[x][y] < nowl || a[x][y] > nowr) {
			continue;
		}
		p[++p[0]] = T.findroot(a[x][y]);
	}
	sort(p + 1, p + 1 + p[0]);
	for(int i = 1; i < p[0]; ++i) if(p[i] == p[i + 1]) return false;
	return true;
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i) 
		for(int j = 1; j <= m; ++j) {
			scanf("%d", &a[i][j]);
			idx[a[i][j]] = i, idy[a[i][j]] = j;
		}
	build(1, 1, n * m), change(1, 1, n * m, 1, 1, 1);
	ll ans = 1;
	for(; nowr < n * m; ) {
		for(; nowl < nowr && !judge(); ++nowl) {
			for(int i = 0; i < 4; ++i) {
				int x = idx[nowl] + dx[i], y = idy[nowl] + dy[i];
				if(!x || !y || x > n || y > m || a[x][y] < nowl || a[x][y] > nowr) {
					continue;
				}
				T.cut(nowl, a[x][y]);
			}
		}
		++nowr, change(1, 1, n * m, nowl, nowr, 1);
		for(int i = 0; i < 4; ++i) {
			int x = idx[nowr] + dx[i], y = idy[nowr] + dy[i];
			if(!x || !y || x > n || y > m || a[x][y] < nowl || a[x][y] > nowr) {
					continue;
			}
			T.link(nowr, a[x][y]), change(1, 1, n * m, nowl, a[x][y], -1);
		}
		maxn = 1e9, num = 0;
		ask(1, 1, n * m, nowl, nowr);
		ans += (maxn == 1) * num;
	}
	printf("%I64d\n", ans);
	return 0;
}
```

