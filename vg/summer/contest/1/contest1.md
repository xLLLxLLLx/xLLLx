训练的第一场比赛。。最后打了2题感觉还是不错哈。。至少C题是真的做不出来啊qwq

当然是先看A题啦。。结果发现自己并不会的样子。。算了一下复杂度好像不太OK啊

算了弃疗看B了 模拟了几下 发现是到大水题诶！但还是打了很久的样子qwq

之后看C 只会m^2 弃疗

看D怎么看也看不懂。。（怎么连题目都看不懂了 想必补题之路肥肠艰辛了。。qwq

看E 怎么又是gcd 怎么我还是什么都不会

看F又没看懂

~~决定看看A~~ 仔细想了一下 发现复杂度好像还挺对的。。

就打了一下。。没想到就过了。。qwq

最后的时间看了看F 把模型转换了一下 就不会做了（菜。

------------

### [Codeforces986C. AND Graph](https://codeforces.com/problemset/problem/986/C)

~~哭哭这题简直就是神仙啊！~~

##### 题面描述

输入$n,m$（$1 \leq n \leq 22$

还有$m$个数($\leq 2^n$)

如果$a_i \& a_j = 0$ 那么$i,j$连边

问最后有多少个联通块

##### qwq

看到这种题只会$O(m^2)$啊药丸

感觉做法还是很神仙的qwq

我们考虑输入的$m$个数分别对应了$(x,1)$，其中$x$表示值

加入$2^n - 1$个点 $(x,2)$

- $(x,1)$可以指向$(x,2)$,$(tot - x, 2)$指向$(x,2)$
- $(x,2)$可以指向$(x |(1 << k),2)$ 其中$x$的第$k$位上为零

这样就把它们连在一起啦！

我们知道很显然的一个性质 就是如果$x \& y=0$的话

那么$x | (tot - y) = x$

那么其实这样构造也就是在满足这个性质

但是点的个数为$O(2^n)$级别的

所以就对了

~~md我交了8发我不难过。。~~

```c++
#include <bits/stdc++.h>
using namespace std;
const int N = 9e6 + 10;
queue<int> q;
int v[N], vis[N];
int n, m, tot;

void go(int x) {
	if(vis[x]) return ;
	// printf("%d\n", x);
	vis[x] = 1;
	if(x <= tot) {
		if(v[x]) go(x + tot + 1);
	} else {
		x = x - tot - 1;
		if(v[tot ^ x]) go(tot ^ x);
		for(int i = 0; i < n; ++i) {
			if((x >> i) & 1) {
				continue;
			}
			int pos = (x | (1 << i)) + tot + 1;
			go(pos);
		}
	}
}

int main() {
	scanf("%d%d", &n, &m);
	tot = (1 << n) - 1;
	for(int i = 1, x; i <= m; ++i) {
		scanf("%d", &x);
		v[x] = 1;
	}
	int ans = 0;
	for(int i = 0; i <= tot; ++i) {
		if(v[i] && !vis[i]) {
			go(i);
			ans++;
		}
	}
	printf("%d\n", ans);
	return 0;
}
```

------

### [Codeforces986F. Oppa Funcan Style Remastered](https://codeforces.com/contest/986/problem/F)

被Div1的题给d没了呀qwq

但是作为Div1最后一题感觉确实不是很难的样子。。

也许难想？

##### 题目描述

反正问题可以转换为

由若干个$k$的质因数能否组成和为$n$ ($k,n \leq 1e18$

一共有$q$$(1 \leq q \leq 10000)$次询问

其中不同的$k$最多50个

##### qwq

首先想到的肯定是质因数分解嘛

但是你会发现..这个要是分的话复杂度显然不对

对此 我们可以采用离线的做法 对相同的$k$就一起算了

假设 我们分解$k$可以分解为$p_1,p_2..p_m$

- $m == 0$ 显然不行

- $m==1$就看$n$ %$p_1$

- $m ==2$ 其实就相当于求解$a*p_1+b*p_2=n$ 其中$b$的最小合理解为$\dfrac{n}{p_2}$在膜$p_1$的意义下 

  那么我们就只需判断$b * p_2$是否大于$n$啦

- $m==3$时 最小的质因数$p_1$显然是小于$100000$的

  那么我们就在膜$p_1$的意义下去做 其实也就是跑个最短路

  记$f[x]$表示到达$x$所需要的和

  即只需要判断$f[n$%$p_1]$是否大于$n$就行了（$f[n$%$p_1]$就代表了和$n$同余的数所需要的，那么剩下的就用$p_1$来补就行了

剩下的就是玄学卡卡卡

```c++
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e6 + 10, M = 31700000;
const ll inf = 1e18;
struct data {
	ll n, k;
	int id;
} a[N];
queue<int> q;
ll f[N];
int vis[N], d[N], b[M];
int pr[N * 3];
ll yz[110];

ll q_pow(ll x, ll y, ll p) {
	ll ans = 1;
	for(; y; y >>= 1) {
		if(y & 1) {
			ans = ans * x % p;
		}
		x = x * x % p;
	}
	return ans;
}

void init() {
	for(int i = 2; i < M; ++i) {
		if(!b[i]) {
			pr[++pr[0]] = i;
		}
		for(int j = 1; j <= pr[0]; ++j) {
			ll pos = i * pr[j];
			if(pos >= M) break;
			b[pos] = 1;
			if(i % pr[j] == 0) break;
		}
	}
}

bool cmp(data A, data B) {
	return A.k < B.k;
}

int main() {
	init();
	int T;
	scanf("%d", &T);
	for(int i = 1; i <= T; ++i) {
		scanf("%lld%lld", &a[i].n, &a[i].k);
		a[i].id = i;
	}
	sort(a + 1, a + 1 + T, cmp);
	for(int o = 1; o <= T; ++o) {
		if(o == 1 || a[o].k != a[o - 1].k) {
			yz[0] = 0;
			ll k = a[o].k;
			for(int i = 1; i <= pr[0]; ++i) {
				if(k % pr[i] == 0) {
					yz[++yz[0]] = pr[i];
					while(k % pr[i] == 0) {
						k /= pr[i];
					}
				}
				if(k == 1) {
					break;
				}
			}
			if(k > 1) {
				yz[++yz[0]] = k;
			}
		}
		// for(int i = 1; i <= yz[0]; ++i) {
		// 	printf("%lld\n", yz[i]);
		// }
		if(yz[0] == 0) {
			d[a[o].id] = 1;
		} else if(yz[0] == 1) {
			d[a[o].id] = (a[o].n % yz[1]);
		} else if(yz[0] == 2) {
			ll pos = (a[o].n % yz[1])* q_pow(yz[2], yz[1] - 2, yz[1]) % yz[1];
			d[a[o].id] = (pos * yz[2] > a[o].n);
		} else {
			if(o == 1 || a[o].k != a[o - 1].k) {
				for(int i = 0; i < N; ++i) {
					f[i] = inf, vis[i] = 0;
				}
				q.push(0);
				f[0] = 0, vis[0] = 1;
				while(!q.empty()) {
					int h = q.front(); q.pop();
					vis[h] = 0;
					for(int i = 1; i <= yz[0]; ++i) {
						int pos = (h + yz[i]) % yz[1];
						if(f[pos] > f[h] + yz[i]) {
							f[pos] = f[h] + yz[i];
							if(!vis[pos]) {
								q.push(pos);
								vis[pos] = 1;
							}
						}
					}
				}
			}
			d[a[o].id] = (f[a[o].n % yz[1]] > a[o].n);
		}
	}
	for(int i = 1; i <= T; ++i) {
		if(!d[i]) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
```



------

### [Codeforces986E. Prince's Problem](https://codeforces.com/contest/986/problem/E)

一道不是很难的题？

大概题解什么的把这道题给写烦了。。或者说我没看懂题解什么意思

##### 题面描述

给你一颗$n(1 \leq n \leq 1e5)$个节点的树 每个节点有一个权值$w_i(1\leq w_i \leq 1e7)$
有$q(1 \leq q \leq 1e5)$次询问 每次询问$x,y,z(1\leq x,y \leq n,1 \leq z \leq 1e7)$ 问$x->y$的最短路径上的每个点和$x$的最大公因数的乘积

##### qwq

我们可以考虑每个质因子对答案的贡献
可以按照质因子而构建很多颗虚树
有一个很显然的性质

- 我们将$x->y$的答案记为$d(x, y)$
  那么$$d(x,y) = d(1,x) * d(1,y) * d(1,lca(x,y))^{-1} * d(1,f[lca(x,y)])^{-1}$$

既然这样
我们就可以离线做了
把所有要求的东西求出来就可以啦！
按照dfs遍历所有点
遍历到一个点 就把这个点的贡献记录上去
那么该点的子树中的所有点都会受到这个点的影响
回溯出去了 就将该点的答案去除即可

如何记录贡献呢？
我们知道 对于一个质因子$p$的贡献
如果两个数可以表示为$p^i*m$,$p^j*t$
那么贡献即为$p^{min(i,j)}$

观察一下下面的代码 感觉还是肥肠巧妙的！（感觉真的是一点数据结构都没有用呢～

```c++
for(int i = w[u]; i > 1; ) {
		for(int t = pr[i], j = t; i % t == 0; i /= t, j *= t) {
			Mul(s[j], t);
		}
	}
	int len = g[u].size();
	for(int k = 0; k < len; ++k) {
		for(int i = val[g[u][k].id]; i > 1; ) {
			for(int t = pr[i], j = t; i % t == 0; i /= t, j *= t) {
				if(g[u][k].v) Mul(d[g[u][k].id], rev(s[j]));
				else Mul(d[g[u][k].id], s[j]);
			}
		}
	}
```

```c++
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e5 + 10, LOG = 18, M = 1e7 + 1;
const int mod = 1e9 + 7;
struct data {
	int nt, to;
} a[N << 1];
struct node {
	int id, v;
};
vector<node> g[N];
int n, q, cnt = 0;
int pr[M], s[M], yz[N * 30];
int head[N], dep[N], f[N][LOG + 1];
int val[N], w[N], d[N];

void adde(int x, int y) {
	a[++cnt].to = y;
	a[cnt].nt = head[x];
	head[x] = cnt;
}

void Add(int &x, ll y) {
	x = (x * 1ll + y) % mod;
}

void Mul(int &x, ll y) {
	x = (x * 1ll * y) % mod;
}

ll add(ll x, ll y) {
	return (x + y) %mod;
}

ll mul(ll x, ll y) {
	return x * y % mod;
}

void init() {
	for(int i = 2; i < M; ++i) {
		if(!pr[i]) {
			pr[i] = i;
			yz[++yz[0]] = i;
		}
		for(int j = 1; j <= yz[0]; ++j) {
			if(i * yz[j] >= M) break;
			if(!pr[i * yz[j]]) {
				pr[i * yz[j]] = yz[j];
			}
			if(i % yz[j] == 0) break;
		}
	}
}

void dfs(int u, int fa) {
	dep[u] = dep[fa] + 1, f[u][0] = fa;
	for(int i = head[u]; i; i = a[i].nt) {
		int to = a[i].to;
		if(to == fa) {
			continue;
		}
		dfs(to, u);
	}
}

void yyqx() {
	for(int j = 1; j <= LOG; ++j) 
		for(int i = 1; i <= n; ++i) {
			f[i][j] = f[f[i][j - 1]][j - 1];
		}
}

int GetLCA(int A, int B) {
	if(dep[A] > dep[B]) swap(A, B);
	for(int i = LOG; i >= 0; --i)
		if(dep[f[B][i]] >= dep[A]) B = f[B][i];
	if(A == B) return A;
	for(int i = LOG; i >= 0; --i) {
		if(f[A][i] != f[B][i]) {
			A = f[A][i], B = f[B][i];
		}
	}
	return f[A][0];
}

int rev(int x) {
	int y = mod - 2;
	int ans = 1;
	for(; y; y >>= 1) {
		if(y & 1) Mul(ans, x);
		Mul(x, x);
	}
	return ans;
}

void work(int u, int fa) {
	for(int i = w[u]; i > 1; ) {
		for(int t = pr[i], j = t; i % t == 0; i /= t, j *= t) {
			Mul(s[j], t);
		}
	}
	int len = g[u].size();
	for(int k = 0; k < len; ++k) {
		for(int i = val[g[u][k].id]; i > 1; ) {
			for(int t = pr[i], j = t; i % t == 0; i /= t, j *= t) {
				if(g[u][k].v) Mul(d[g[u][k].id], rev(s[j]));
				else Mul(d[g[u][k].id], s[j]);
			}
		}
	}
	for(int i = head[u]; i; i = a[i].nt) {
		int to = a[i].to;
		if(to == fa) {
			continue;
		}
		work(to, u);
	}
	for(int i = w[u]; i > 1; ) {
		for(int t = pr[i], j = t; i % t ==0; i /= t, j *= t) {
			Mul(s[j], rev(t));
		}
	}
}

int main() {
	init();
	scanf("%d", &n);
	for(int i = 1, x, y; i < n; ++i) {
		scanf("%d%d", &x, &y);
		adde(x, y), adde(y, x);
	}
	dfs(1, 0), yyqx();
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &w[i]);
	}
	scanf("%d", &q);
	for(int o = 1, x, y; o <= q; ++o) {
		scanf("%d%d%d", &x, &y, &val[o]);
		int z = GetLCA(x, y);
		g[x].push_back((node){o, 0});
		g[y].push_back((node){o, 0});
		g[z].push_back((node){o, 1});
		g[f[z][0]].push_back((node){o, 1});
		d[o] = 1;
	}
	for(int i = 1; i < M; ++i) s[i] = 1;
	work(1, 0);
	for(int i = 1; i <= q; ++i) {
		printf("%d\n", d[i]);
	}
	return 0;
}
```



~~为什么我的代码这么长。~~



------

### [Codeforces986D. Perfect Encoding](https://codeforces.com/problemset/problem/986/D)

##### 题面描述

给出$n$($1 \leq len(n) \leq 1.5e6)$

这个$n$是某个$a[]$的乘积

让你找到这样一个数组$b$ 使得$a[i] \leq b[i]$

输出$b[]$的最小总和

##### qwq

实际上 $b[]$的乘积必定大于$n$

我们考虑要最小化总和$s$

那肯定是将$s$化成一些相同的数字

即$ans = (\dfrac{s}{x})^{x}$

两边取对数

$ln{ans} = ln{(\dfrac{s}{x})^{x}}$

对右边求导得到$ln\dfrac{n}{x} - 1$

当$\dfrac{n}{x}=e$时取到最大值

所以尽量由3组成 少部分用2去补

$3^x= n$ ->$x = log_3n$ ->$log_3n <10^{len}$->$x < len*log_310$

在一定范围内枚举即可

由于涉及到大整数乘法 而且乘方次数比较高

可以采用FFT + 快速幂

可以采取压位减少复杂度

```c++
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const double PI = acos(-1.0);
const int N = 3e6 + 10;
char lx[N];
int base = 10000;
struct C {
	double r, i;
	C() {}
	C(double _r, double _i) { r = _r, i = _i; }
	C operator + (C x) { return C(r + x.r, i + x.i); }
	C operator - (C x) { return C(r - x.r, i - x.i); }
	C operator * (C x) { return C(r * x.r - i * x.i, r * x.i + i * x.r); }
} A[N], B[N], w[N];
int rev[N];
struct Big {
	int len;
	ll a[N];

	void clear() {
		for(int i = 1; i <= len; ++i) {
			a[i] = 0;
		}
		len = 0;
	}

	bool operator >= (Big &A) {
		if(len != A.len) {
			return len > A.len;
		}
		for(int i = len; i >= 1; --i) {
			if(a[i] != A.a[i]) {
				return a[i] > A.a[i];
			}
		}
		return 1;
	}

	void print() {
		printf("len=%d\n", len);
		for(int i = 1; i <= len; ++i) {
			printf("%04d ", a[i]);
		}
		puts("");
	}

	void bit() {
		for(int i = 1; i <= len; ++i) {
			a[i + 1] += a[i] / base;
			a[i] %= base;
		}
		while(a[len + 1]) {
			len++;
			a[len + 1] += a[len] / base;
			a[len] %= base;
		}
	}

	void operator *= (int x) {
		for(int i = 1; i <= len; ++i) {
			a[i] *= x;
		}
		bit();
	}

}n, x, tmp;

void fft(C a[], int n) {
	for(int i = 0; i < n; ++i)
		if(rev[i] > i) 
			swap(a[i], a[rev[i]]);
	for(int t = n >> 1, d = 1; d < n; t >>= 1, d <<= 1) 
		for(int i = 0; i < n; i += (d << 1)) {
			for(int j = 0; j < d; ++j) {
				C tmp = w[t * j] * a[i + j + d];
				a[i + j + d] = a[i + j] - tmp;
				a[i + j] = a[i + j] + tmp;
			}
		}
}

void mult(Big &a, Big &b, Big &c) {
	int n = 1, L = 0;
	for(; n < a.len + b.len; n <<= 1, L++) ;
	for(int i = 0; i < n; ++i) {
		w[i] = C(cos(2.0 * i * PI / n), sin(2.0 * i * PI / n));
		rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (L - 1));
		A[i] = C(0,0), B[i] = C(0, 0);
	}
	for(int i = 1; i <= a.len; ++i) {
		A[i - 1].r = a.a[i];
	}
	for(int i = 1; i <= b.len; ++i) {
		B[i - 1].r = b.a[i];
	}
	fft(A, n), fft(B, n);
	for(int i = 0; i < n; ++i) {
		A[i] = A[i] * B[i];
		w[i].i = -1.0 * w[i].i;
	}
	fft(A, n);
	c.clear();
	c.len = n;
	for(int i = 0; i < n; ++i) {
		c.a[i + 1] = (ll)(A[i].r / n + 0.5);
	}
	while(!c.a[c.len] && c.len > 1) c.len--;
	c.bit();
}

void q_pow(int y) {
	if(!y) {
		x.clear();
		x.len = 1;
		x.a[1] = 1;
		return ;
	}
	q_pow(y >> 1);
	mult(x, x, x);
	if(y & 1) {
		x *= 3;
	}
}

int pw[4] = {1, 10, 100, 1000};

bool check(Big &x, int y) {
	tmp = x;
	tmp *= y;
	if(tmp >= n) {
		return true;
	} else return false;
}

int main() {
	scanf("%s", lx + 1);
	n.len = strlen(lx + 1);
	int pos = max((int)(log(10.0) / log(3.0) * n.len) - 3, 0);
	for(int i = 1; i <= n.len; ++i) {
		n.a[(n.len - i) / 4 + 1] += (lx[i] - '0') * pw[(n.len - i) % 4];
	}
	n.len = (n.len - 1) / 4 + 1;
	if(n.len == 1 && n.a[1] == 1) {
		return printf("1\n"), 0;
	}
	q_pow(pos);
	for(; ; ) {
		for(int i = 2; i <= 4; ++i) {
			if(check(x, i)) {
				// printf("%d %d\n", pos, i);
				return printf("%d\n", pos * 3 + i), 0;
			}
		}
		pos++;
		x *= 3;
	}
	return 0;
}
```

----

常犯错误：

- 算联通块的时候可以直接采用深搜
- 交上去程序之前一定要把空间算好（MLE很伤信心的啊qwq
- 逆FFT 最后转换成值的时候不要忘记／n
- `int` `long long`范围用清