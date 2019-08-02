### Contest15

##### 总结

$A$题水到爆..

$B$题看到题面一脸mengbier...面对博弈题只会乱搞瞎猜结论诶...

$C$题怎么又是博弈！！！！那我就只能瞎猜猜如果两步之内无法分出胜负..那就平局了...

$D$题也太水了吧..几乎是看完题目就会做的~~普及组题??~~

$E$题满满的套路还有很多的坑点...真是一道很厉害的题..其实区间上能做的东西 环上也可以做..把长度扩大两倍是很常规的操作...但是区间就是圆上的..是首尾相连的...所以在处理的时候你应该保证相交的区间不会错过..首先一个角度加2pi和减2pi都是同一个角度....我们要保证我们的端点范围中不存在这种映射关系..所以两个区间就都在$[0,2pi)$最佳…注意精度于TLE的关系..~~人傻自带大常数吧..~~

E题还运用了一个常规贪心..但是我发现我对贪心一窍不通...最少点覆盖所有区间

按照左端点从大到小排序 或者 按照右端点从小到大排序..都可以避免线段包含的bug...



~~这场太水..题解就免了吧...~~



-------------------------

~~代码放一下~~

##### A

```c++
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e5 + 10;
ll a[N];
ll n, k;
int m;

ll put(ll x) {
	return (x - 1)/ k + 1;
}

int main() {
	cin >> n >> m >> k;
	for(int i = 1; i <= m; ++i) {
		scanf("%lld", &a[i]);
	}
	int ans = 0, last = 0, num = 0;
	for(; last < m;) {
		num = last;
		last++, ans++;
		int i = last;
		for(; i <= m && put(a[i] - num) == put(a[last] - num); ++i);
		// printf("%d %d\n", last, i - 1);
		last = i - 1;
	}
	printf("%d\n", ans);	
	return 0;
}
```



##### B

```c++
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int a[N], all[N], num[N];

int main() {
	int n, now = 0;
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
		now += (a[i] == 0);
		all[i] = a[i];
	}
	sort(a + 1, a + 1 + n), sort(all + 1, all + 1 + n);
	int m = unique(all + 1, all + 1 + n) - all - 1;
	for(int i = 1; i <= n; ++i) {
		int pos = lower_bound(all + 1, all + 1 + m, a[i]) - all;
		num[pos]++;
	}
	int res = 0, tot = 0, be = 0;
	for(int i = 1; i <= m; ++i) {
		if(num[i] >= 2) {
			res++;
			tot += num[i];
			be = i;
		}
	}
	int pos = 0;
	if(now >= 2 || res >= 2 || res * 2 < tot) return printf("cslnb\n"), 0;
	else if(res){
		if(be > 1 && all[be - 1] == all[be] - 1) return printf("cslnb\n"), 0;
		else {
			for(int i = 1; i <= n; ++i) {
				if(a[i] == all[be]) {
					a[i]--, pos = 1;
					break;
				}
			}
		}
	}
	for(int i = 1; i <= n; ++i) {
		pos ^= ((a[i] - i + 1) & 1);
	}
	if(pos & 1) printf("sjfnb\n");
	else printf("cslnb\n");
	return 0;
}
```

##### C

```c++
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int a[N];

void even() {
	printf("once again\n");
	exit(0);
}

void xs() {
	printf("tokitsukaze\n");
	exit(0);
}

void hs() {
	printf("quailty\n");
	exit(0);
}

int main() {
	int n, k;
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= n; ++i) {
		scanf("%1d", &a[i]);
	}
	if(k + 1 >= n) xs();
	else {
		int l = 1, r = n;
		for(int i = 2; i <= n; ++i) {
			if(a[i] != a[1]) break;
			l = i;
		}
		for(int i = n; i >= 1; --i) {
			if(a[i] != a[n]) break;
			r = i;
		}
		if(a[1] == a[n] && (r - l - 1) <= k) xs();
		else if(max(l, n - r + 1) + k >= n) xs();
	} 
	if(a[1] != a[n]) {
		int l = 1, r = n;
		for(int i = 2; i <= n; ++i) {
			if(a[i] != a[1]) break;
			l = i;
		}
		for(int i = n; i >= 1; --i) {
			if(a[i] != a[n]) break;
			r = i;
		}
		// printf("%d %d\n", l, r);
		if(k * 2 >= n && 1 + k >= r - 1 && n - k <= l + 1) hs();
	}
	even();
	return 0;
}
```

##### D

```c++
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 2e5 + 10;
struct data {
	int x, y;
} a[N];
int tr[N], all[N], vis[N], d[N];

bool cmp(data A, data B) {
	if(A.y != B.y) return A.y > B.y;
	else return A.x < B.x;
}

int lower(int x) {
	return x & (-x);
}

void upd(int x) {
	for(; x < N; x += lower(x)) tr[x]++;
}

int get(int x) {
	int ans = 0;
	for(; x; x -= lower(x)) ans += tr[x];
	return ans;
}

int main() {
	int n;
	scanf("%d", &n);
	int cnt = 0;
	for(int i = 1; i <= n; ++i) {
		scanf("%d%d", &a[i].x, &a[i].y);
		all[++cnt] = a[i].x;
	}
	sort(all + 1, all + 1 + cnt);
	int m = unique(all + 1, all + 1 + cnt) - all - 1;
	for(int i = 1; i <= n; ++i) {
		a[i].x = lower_bound(all + 1, all + 1 + m, a[i].x) - all;
	}
	ll ans = 0, pos = 0;
	sort(a + 1, a + 1 + n, cmp);
	for(int i = 1; i <= n; ++i) {
		int now = i;
		d[0] = 0;
		for(; now <= n && a[now].y == a[i].y; now++) {
			d[++d[0]] = a[now].x;
			if(!vis[a[now].x]) {
				pos++, vis[a[now].x] = 1;
				upd(a[now].x);
			}
		}
		int last = 0;
		for(int i = 1; i <= d[0]; ++i) {
			int tmp = get(d[i]);
			ans += 1ll * (tmp - last) * (pos - tmp + 1);
			last = get(d[i]);
		}
		now--;
		i = now;
	}
	printf("%lld\n", ans);
	return 0;
}
```

##### E

```c++
#include <bits/stdc++.h>
using namespace std;
const int N = 3e5 + 10, LOG = 20;
const double Cir = acos(-1.0) * 2.0, eps = 1e-10;
struct data {
	double l, r;
} a[N];
double dis[N], kk[N];
int n, k, f[N][LOG + 1];

bool cmp(data A, data B) {
	return A.r < B.r;
}

bool check(double len) {
	for(int i = 1; i <= n; ++i) {
		double gg = acos(len / dis[i]);
		a[i].l = kk[i] - gg, a[i].r = kk[i] + gg;
		while(a[i].r < 0) a[i].l += Cir, a[i].r += Cir;
		while(a[i].r >= Cir) a[i].l -= Cir, a[i].r -= Cir;
		// cout<<a[i].l << " "<< a[i].r <<" "<<gg<<endl;
	}
	int tot = n;
	sort(a + 1, a + 1 + tot, cmp);
	for(int i = 1; i <= tot; ++i) a[i + tot] = (data){a[i].l + Cir, a[i].r + Cir};
	tot <<= 1;
	int last = 0;
	for(int i = 1; i <= tot; ++i) {
		last = max(last, i);
		for(; last <= tot && a[last].l <= a[i].r; last++);
		f[i][0] = last;
	}
	for(int j = 1; j <= LOG; ++j)
		for(int i = 1; i <= tot; ++i)
			f[i][j] = f[f[i][j - 1]][j - 1];
	// for(int i = 1; i <= tot; ++i)
	// 	for(int j = 0; j <= LOG; ++j) {
	// 		if(f[i][j]) {
	// 			printf("f[%d][%d]=%d\n", i, j, f[i][j]);
	// 		}
	// 	}
	for(int be = 1; be <= n; ++be) {
		int pos = 0, now = be;
		for(int t = k; t; t >>= 1, pos++) {
			if(t & 1) now = f[now][pos];
		}
		if(!now || now > be + n - 1) return true;
	}
	return false;
}

int main() {
	scanf("%d%d", &n, &k);
	double l = 0, r = 3e5;
	for(int i = 1; i <= n; ++i) {
		double x, y;
		scanf("%lf%lf", &x, &y);
		dis[i] = sqrt(x * x + y * y), kk[i] = atan2(y, x);
		r = min(r, dis[i]);
	}
	while(r - l > eps) {
		double mid = (l + r) / 2.0;
		if(check(mid)) l = mid;
		else r = mid;
	}
	printf("%.10f\n", l);
	return 0;
}
```

