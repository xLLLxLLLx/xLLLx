### Contest12

[Codeforces Round #462 (Div. 1)](https://codeforces.com/contest/933)

[官方题解来袭](https://codeforces.com/blog/entry/57763)

-------------

#### C - A Colourful Prospect

>  [欧拉公式～V-E+R=C+1]([https://baike.baidu.com/item/%E6%AC%A7%E6%8B%89%E5%85%AC%E5%BC%8F/92066?fr=aladdin](https://baike.baidu.com/item/欧拉公式/92066?fr=aladdin))
>
> 点的个数我们可以求出每个圆之间的交点 然后去重就行了
>
> 边的个数我们只要将每个圆的交点个数累加即可
>
> C就是有多少个联通块啦（相交的用并查集合并即可）

总之欧拉公式是一个很奇妙的东西。。（小时候大概是通过几道题目（类似于数点数边数之类的）发现了这个规律。。（证明？？不存在的）感觉推理证明还是很浅显易懂的（~~我们也没有必要去了解严谨证明对吧。。。qwq~~）

![smg](http://chuantu.xyz/t6/702/1563540020x2073530529.png)

这种数据是smg啊。。出题人有心了。。

#### D - A Creative Cutout

~~一道肥肠厉害的数学题~~

> 啧啧啧...你看看这个$m$这个是这么的大...肯定是用点来记贡献的咯
>
> 那么我们对于一个点$(x,y)$我们设$L=x^2+y^2$ 那么这个贡献就是$ans = \sum_{k=L}^n\sum_{j=L}^kj$
>
> $\Longrightarrow$ $ans=\sum_{k=L}^nC_{k+1}^2-C_L^2$
>
> 又有一个肥肠重要的等式$\sum_{i=L}^RC_i^x=C_{R+1}^{x+1}-C_{L}^{x+1}$(这个可以有杨辉三角显然可得～)
>
> 我们把它带入
>
> $ans = C_{n+1}^3-C_{L+1}^3-(n-L+1)*C_L^2$
>
> 最后暴力展开+$L$用$x^2+y^2$替换就行了。。
>
> 之后枚举$x$的取值 然后$y$的取值是一个区间 这个处理一个前缀和即可

#### E - A Preponderant Reunion

[神仙yyb](https://www.cnblogs.com/cjyyb/p/11158816.html)

 > 直接做并不好搞 我们考虑把条件放宽一些 每次可以选择相邻两个数减少任意值

 我们假定只处理$[l,r]$这段区间里面的数($c_l=p_l,c_i=max(p_i-c_{i-1},0)$) 那么我们肯定是可以构造出一种方案 使得处理的这段区间的代价为$\sumc_i$
 那么
 $$f[l][r]=f[l][r-2]+c_{r-1}+c_r=f[l][r-2]+c_{r-1}+max(p_r-c_{r-1},0)=f[l][r-2]+max(p_r,c_{r-1}$$
$f[l][r]>=f[k][r-2]+p_2=f[l][r-2]+f[r][r]$

------

Code

##### A

```c++
#include <bits/stdc++.h>
using namespace std;
const int N = 2010;
int a[N], qz[N][3], mx[N];

int main() {
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
		qz[i][1] = qz[i - 1][1];
		qz[i][2] = qz[i - 1][2];
		qz[i][a[i]]++;
	}
	int ans = 0;
	for(int i = 0; i <= n; ++i) {
		ans = max(ans, qz[i][1] + qz[n][2] - qz[i][2]);
		if(i) mx[i] = max(mx[i - 1], qz[i][1] - qz[i][2]);
	}
	// printf("%d\n", ans);
	for(int i = 1; i <= n; ++i) {
		int now = 0;
		for(int j = i; j >= 1; --j) {
			now += (a[j] == 1);
			ans = max(ans, now + mx[j - 1] + qz[j - 1][2] + qz[n][2] - qz[i][2]);
		}
	}
	printf("%d\n", ans);
	return 0;
}
```

##### B

```c++
#include <bits/stdc++.h>
#define ll long long
using namespace std;
map<ll, int> v;
vector<int> g;
int kk;
ll p, k;

void fail() {
	printf("-1\n");
	exit(0);
}

ll cal(ll x, ll y) {
	return x * k + y;
}

ll get(ll x) {
	kk = 0;
	ll l = -(p / k) - 10, r =(p / k) + 10, ans = 0, flg = 0;
	for(int o = 1; o <= 64; ++o) {
		ll mid = (l + r) >> 1;
		ll val = cal(mid, x);
		if(val < 0) l = mid + 1;
		else if(val >= k) r = mid - 1;
		else {
			if(mid >= 0 && mid < k) {
				ans = mid, flg = 1;
				kk = 1;
				break;
			} else if(mid < 0) l = mid + 1;
			else r = mid - 1;
			if(!flg && !v.count(mid)) {
				kk = 1, ans = mid;
			}
		}
	}
	v[ans] = 1;
	return ans;
}

int main() {
	scanf("%lld%lld", &p, &k);
	ll pre = p;
	int cnt = 0;
	for(;;) {
		ll pos = get(pre);
		if(!kk) fail();
		g.push_back(pos * k + pre);
		pre = pos;
		if(0 <= pos && pos < k) {
			if(pos) g.push_back(pos);
			break;
		}
	}
	printf("%d\n", (int)g.size());
	for(int i = 0; i < g.size(); ++i) {
		printf("%d ", g[i]);
	}
	puts("");
	return 0;
}
```

##### C

```c++
#include <bits/stdc++.h>
using namespace std;
const double eps = 1e-3;
int f[20], sz[20];
double R[20];

int sgn(double x) {
	return x < -eps ? -1 : x > eps;
}
int find(int k) {
	return f[k] == k ? f[k] : f[k] = find(f[k]);
}
struct Point;
typedef Point Vector;
struct Point {
	double x, y;
	Point() {x = 0, y = 0; }
	Point(double _x, double _y) { x = _x, y = _y; }
	double dot(const Vector &a) {
		return x * a.x + y * a.y;
	}
	Vector operator + (const Vector &a) const {
		return Vector(x + a.x, y + a.y);
	}
	Vector operator - (const Vector &a) const {
		return Vector(x - a.x, y - a.y);
	}
	double operator * (const Vector &a) const {
		return x * a.y - y * a.x;
	}
	Vector operator * (double t) const {
		return Vector(x * t, y * t);
	}
	bool operator == (const Point &a) const {
		return sgn(x - a.x) == 0 && sgn(y - a.y) == 0;
	}
	bool operator < (const Point &a) const {
		return sgn(x - a.x) < 0 || sgn(x - a.x) == 0 && sgn(y - a.y) < 0;
	}
} z[20], a[20], jiao[10][10];

double cross(Point a, Point b, Point c) {
	return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}

double ppdis(Point a, Point b) {
	return sqrt((a - b).dot(a - b));
}

double pldis(Point p, Point l1, Point l2) {
	return fabs(cross(p, l1, l2)) / ppdis(l1, l2);
}

bool cir_line(Point ct, double r, Point l1, Point l2, Point& p1, Point& p2) {
  if ( sgn (pldis(ct, l1, l2) - r ) > 0)
    return false;
  double a1, a2, b1, b2, A, B, C, t1, t2;
  a1 = l2.x - l1.x; a2 = l2.y - l1.y;
  b1 = l1.x - ct.x; b2 = l1.y - ct.y;
  A = a1 * a1 + a2 * a2;
  B = (a1 * b1 + a2 * b2) * 2;
  C = b1 * b1 + b2 * b2 - r * r;
  double delta = fabs(B * B - 4.0 * A * C);
  t1 = (-B - sqrt(delta)) / 2.0 / A;
  t2 = (-B + sqrt(delta)) / 2.0 / A;
  p1.x = l1.x + a1 * t1; p1.y = l1.y + a2 * t1;
  p2.x = l1.x + a1 * t2; p2.y = l1.y + a2 * t2;
  return true;
}

bool cir_cir(Point c1, double r1, Point c2, double r2, Point& p1, Point& p2) {
  double d = ppdis(c1, c2);
  if ( sgn(d - r1 - r2) > 0|| sgn (d - fabs(r1 - r2) ) < 0 )
    return false;
  Point u, v;
  double t = (1 + (r1 * r1 - r2 * r2) / ppdis(c1, c2) / ppdis(c1, c2)) / 2;
  u.x = c1.x + (c2.x - c1.x) * t;
  u.y = c1.y + (c2.y - c1.y) * t;
  v.x = u.x + c1.y - c2.y;
  v.y = u.y + c2.x - c1.x;
  cir_line(c1, r1, u, v, p1, p2);
  return true;
}

int main() {
	int n, cnt = 0;
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		f[i] = i;
		scanf("%lf%lf%lf", &a[i].x, &a[i].y, &R[i]);
	}
	int edge = 0;
	for(int i = 1; i <= n; ++i) {
		for(int j = i + 1; j <= n; ++j) {
			Point p1, p2;
			if(cir_cir(a[i], R[i], a[j], R[j], p1, p2)) {
				int fx = find(i), fy = find(j);
				f[fx] = fy;
				z[++cnt] = p1, z[++cnt] = p2;
				jiao[i][++sz[i]] = p1, jiao[i][++sz[i]] = p2;
				jiao[j][++sz[j]] = p1, jiao[j][++sz[j]] = p2;
			}
		}
	}
	for(int i = 1; i <= n; ++i) {
		sort(jiao[i] + 1, jiao[i] + 1 + sz[i]);
		edge += (sz[i] > 1);
		for(int j = 2; j <= sz[i]; ++j) {
			if(jiao[i][j] == jiao[i][j - 1]) {
				continue;
			}
			edge++;
		}
	}
	sort(z + 1, z + 1 + cnt);
	int num = (cnt >= 1);
	// printf("%.2f %.2f\n", z[1].x, z[1].y);
	for(int i = 2; i <= cnt; ++i) {
		// printf("%.2f %.2f\n", z[i].x, z[i].y);
		if(z[i] == z[i - 1]) {
			continue;
		}
		num++;
	}
	int block = 0;
	for(int i = 1; i <= n; ++i) {
		block += (f[i] == i);
	}
	// printf("%d %d %d\n", block, num, edge);
	printf("%d\n", block + 1 - num + edge);
	return 0;
}
```

##### D

```c++
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int mod = 1e9 + 7, N = 1e6 + 10;
ll b[N], a[N], c[N];

int main() {
	ll n;
	scanf("%lld", &n);
	for(int i = 1; i < N; ++i) {
		a[i] = (a[i - 1] + 1ll * i * i % mod) % mod;
		b[i] = (b[i - 1] + 1ll * i * i * i % mod * i % mod) % mod;
		c[i] = (c[i - 1] + 1ll * i * i * i % mod * i % mod * i % mod * i % mod) % mod;
	}
	ll ans = 0, m = sqrt(n);
	ll M = n % mod;
	for(ll i = 1, j = m; i <= m; ++i) {
		for(; i * i + j * j > n; --j);
		ll k = i * i % mod;
		ans = (ans + (1 + M - k) * (2 + M - k) % mod * (M + 2ll * k) % mod * (j + 1)) % mod;
		ans = (ans + (4 + M * 3 - k * 12 % mod - 6ll * M * k % mod + 6ll * k * k + 2ll * mod) % mod * a[j]) % mod;
		ans = (ans + (k * 6 - 3 * M % mod - 6ll + 2ll * mod) % mod * b[j] + 2ll * c[j]) % mod;
	}
  ans = ans * 2 % mod * (mod + 1) / 3 % mod;
  ans = (ans + M * (M + 1) % mod * (M + 2) % mod * (mod + 1) / 6) % mod;
  cout << ans << endl;
	return 0;
}
```

##### E

```c++
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 3e5 + 10;
ll f[N];
vector<int> g;
int p[N], t[N];

void go(int x) {
	int gg = min(p[x], p[x + 1]);
	if(!gg) return ;
	g.push_back(x);
	p[x] -= gg, p[x + 1] -= gg;
}

int main() {
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &p[i]);
	}
	memset(f, 0x3f, sizeof f);
	f[0] = 0;
	for(int i = 1; i <= n; ++i) {
		f[i] = min(f[max(i - 2, 0)] + p[i], f[max(i - 3, 0)] + max(p[i], p[i - 1]));
		if(f[i] == f[max(i - 3, 0)] + max(p[i], p[i - 1])) t[i] = 1;
	}
	ll ans = min(f[n], f[n - 1]);
	for(int i = n - (ans == f[n - 1]); i >= 1; i -= 2 + t[i]) {
		go(i - 1);
		if(t[i]) go(i - 2);
		go(i);
	}
	printf("%d\n", (int)g.size());
	for(int i = 0; i < g.size(); ++i) {
		printf("%d\n", g[i]);
	}
	return 0;
}
```

