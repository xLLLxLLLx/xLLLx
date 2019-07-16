### Contest 3

[Codeforces1103-Round#534Div1](https://codeforces.com/contest/1103)

[官方题解](https://codeforces.com/blog/entry/64685)

-----我是vp分割线-----

A题实在是太水了 不知道该说啥。。

B题膜来膜去的 单调性咋找啊？？？

C题真的好神仙啊！这个限制是smg

D题有点可写。。。qwq

E题smg



> - Y::solved in the contest
> - A::solved after the contest
> - S::solving ::sob:
> - X::tan90

| #        | A    | B    | C    | D    | E    | F    |
| -------- | ---- | ---- | ---- | ---- | ---- | ---- |
| Contest3 | Y    | A    | A    | A    | S    | X    |



-------还是写题(~~瞎~~)解(~~讲~~)报告比较好玩-------

#### A

~~好水呀！qwq~~

#### B

一个套路💨

<font color="blue">交互题要考虑二分（有时候还有个什么二进制逼近？？）</font>

我们发现啊这个膜 单调区间有很多

总有一些肥肠神仙的人可以想到这种性质

- $a$%$2*a$





-----Code-----

##### A

```c++
#include <bits/stdc++.h>
using namespace std;
const int N = 1010;
char lx[N];

int main() {
	scanf("%s", lx + 1);
	int len = strlen(lx + 1), pos = 0, tmp = 0;
	for(int i = 1; i <= len; ++i) {
		if(lx[i] == '0') {
			printf("1 %d\n", pos + 1);
			pos = (pos + 1) % 4;
		} else {
			printf("3 %d\n", tmp * 2 + 1);
			tmp = (tmp + 1) % 2;
		}
	}
	return 0;
}
```

##### B

```c++
#include <bits/stdc++.h>
using namespace std;
char lx[2], ll[10];

bool ask(int x, int y) {
	printf("? %d %d\n", x, y);
	fflush(stdout);
	scanf("%s", lx + 1);
	return lx[1] == 'x';
}

void print(int x) {
	printf("! %d\n", x);
	fflush(stdout);
}

int main() {
	while(scanf("%s", ll + 1)) {
		if(ll[1] == 'e') {
			break;
		}
		int l, r;
		for(int i = 0; ; ++i) {
			if(ask(1 << i, 1 << (i + 1))) {
				l = (1 << i) - 1, r = 1 << (i + 1);
				break;
			}
		}
		while(l + 1 < r) {
			int mid = (l + r) >> 1;
			if(ask(l, mid)) {
				r = mid;
			} else {
				l = mid;
			}
		}
		print(l + 1);
	}
	return 0;
}
```

##### C

```c++
#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 10;
struct data {
	int nt, to;
} a[N << 1];
vector<int> g[N];
int maxn = 0, be = 0;
int head[N], d[N], s[N], vis[N], f[N], dep[N], cnt = 0;

void add(int x, int y) {
	a[++cnt].to = y;
	a[cnt].nt = head[x];
	head[x] = cnt;
}

void dfs(int x, int y) {
	vis[x] = 1;
	dep[x] = dep[y] + 1, f[x] = y;
	if(dep[x] > maxn) {
		maxn = dep[x], be = x;
	}
	int son = 0;
	for(int i = head[x]; i; i = a[i].nt) {
		int to = a[i].to;
		if(vis[to]) {
			if(to != f[x]) 
				g[x].push_back(to);
			continue;
		}
		++son;
		dfs(to, x);
	}
	if(!son) s[++s[0]] = x;
}

void print() {
	printf("%d\n", d[0]);
	for(int i = 1; i <= d[0]; ++i) {
		printf("%d ", d[i]);
	}
	puts("");
}

void path() {
	printf("PATH\n");
	for(; be; ) {
		d[++d[0]] = be;
		be = f[be];
	}
	print();
}

void get(int x, int y) {
	d[0] = 0;
	if(dep[x] < dep[y]) {
		swap(x, y);
	}
	for(; x != y; x = f[x]) {
		d[++d[0]] = x;
	}
	d[++d[0]] = x;
	print();
}

void cycle(int k) {
	printf("CYCLES\n");
	for(int i = 1; i <= k; ++i) {
		int x = s[i], y = g[s[i]][0], z = g[s[i]][1];
		d[0] = 0;
		if((dep[x] - dep[y] + 1) % 3) {
			get(x, y);
		} else if((dep[x] - dep[z] + 1) % 3) {
			get(x, z);
		} else {
			get(z, y);
		}
	}
}

int main() {
	int n, m, k;
	scanf("%d%d%d", &n, &m, &k);
	for(int i = 1, x, y; i <= m; ++i) {
		scanf("%d%d", &x, &y);
		add(x, y), add(y, x);
	}
	dfs(1, 0);
	int pos = n / k;
	if(n % k) pos++;
	if(maxn >= pos) {
		path();
	} else {
		cycle(k);
	}
	return 0;
}
```

##### D

```c++
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e6 + 10, MASK = 3010;
struct data {
	ll w, val;
} a[N];
int vis[N], b[MASK], dp[MASK];
ll v[20];

ll gcd(ll A, ll B) {
	return B ? gcd(B, A % B) : A;
}

bool cmp(data A, data B) {
	return A.val < B.val;
}

bool comp(ll x, ll y) {
	return x > y;
}

void Min(int &x, int y) {
	if(x == -1) {
		x = y;
	} else {
		x = min(x, y);
	}
}

int main() {
	int n;
	ll k;
	scanf("%d%lld", &n, &k);
	for(int i = 1; i <= n; ++i) {
		scanf("%lld", &a[i].w);
	}
	for(int i = 1; i <= n; ++i) {
		scanf("%lld", &a[i].val);
	}
	sort(a + 1, a + 1 + n, cmp);
	ll now = a[1].w;
	for(int i = 2; i <= n; ++i) {
		now = gcd(a[i].w, now);
	}
	int len = sqrt(now), res = 0;
	ll pos = now;
	for(int i = 2; i <= len; ++i) {
		if(pos % i == 0) {
			v[res] = 1;
			while(pos % i == 0) {
				pos /= i;
				v[res] *= 1ll * i;
			}
			res++;
		}
	}
	if(pos > 1) {
		v[res++] = pos;
	}
	for(int i = 0; i < res; ++i) {
		if(v[i] > k) {
			return printf("-1\n"), 0;
		}
	}
	int tot = (1 << res) - 1;
	for(int i = 0; i <= tot; ++i) {
		int num = 0;
		ll tmp = 1;
		for(int j = 0; j < res; ++j) {
			if((i >> j) & 1) {
				num++;
				tmp *= v[j];
			}
		}
		b[i] = (tmp <= k);
	}
	memset(dp, -1, sizeof dp);
	dp[0] = 0;
	for(int i = 0; i <= tot; ++i) {
		if(dp[i] == -1) {
			continue;
		}
		int s = (tot ^ i);
		for(int t = s; t; t = (t - 1) & s) {
			if(b[t]) {
				Min(dp[i|t], dp[i] + b[t]);
			}
		}
	}
	if(dp[tot] > n) {
		printf("-1\n");
	} else {
		ll ans = 0;
		printf("%d\n", dp[tot]);
		for(int i = 1; i <= n; ++i) {
			printf("%lld\n", a[i].val);
		}
		for(int i = 1; i <= dp[tot]; ++i) {
			ans += a[i].val;
		}
		printf("%lld\n", ans);
		ans *= (ll)dp[tot];
		printf("%lld\n", ans);
	}
	return 0;
}
```

