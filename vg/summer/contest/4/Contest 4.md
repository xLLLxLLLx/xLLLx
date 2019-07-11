[TOC]



## Contest 4

[Codeforces-297-Round180Div1](https://codeforces.com/contest/297)

[官方题解](https://codeforces.com/blog/entry/7437)

想到自闭。。

被A题给d没了呀。。:sob:

看到T1就感觉还挺简单的。。然后几乎每码完一点就可以发现自己题目没看清楚。。

高高兴兴过了样例 交上去wawawa~~听取🐸声一片..~~ <font color="red">wrong answer on test 49</font> ????

自闭了。。看B题 发现还是不会。。

C题还是不会。。D题还是不会。。E题是个smg？？

----------------

还是写题(~~瞎讲~~)解(~~报告~~）比较好玩TAT

感觉代码贴上来不太好看啊qwq 所以在最后贴了下代码。。

------------------

#### A

##### Description

给出2个01串$s$,$t$ 问你能否通过下面两个操作把$s$串变成$t$串

- 删除$s$串首字符
- 在$s$后添加$g(s)$ [$g(s)$表示$s$中1的个数的奇偶性

$1 \leq len \leq 1000$

##### Solution

**当$g(s)$是偶数的时候那么可以在$s$后面添加任意多个0，当你要加1的话，通过删除前面一个1来得到，所以1的个数只会变小**

当然要注意的是如果一开始$g(s)$是奇数的话 那泥当然要现在后面加个1啊～

所以只要$s$的1个数大于等于$t$的1个数 那么就yes否则是no

---------------------------

#### B

##### Description

两个人分别拥有$n$,$m$条鱼

给你这些鱼的类型 且$w_1 \leq w_2 \leq w_3 \leq … \leq w_k$

问你第一个人的重量总和是否可以大于第二个人

$1 \leq n,m \leq 1e5, 1 \leq k \leq 1e9$

##### Solution

**如果目前来说第一个人的最大类型比第二个大的话 那么第一个人肯定就可以了**

设第一个人的最大类型为$m1$,第二个人的最大类型$m2$

- $m1 \leq m2$ 那么我们强行让$w_{m1}=w_{m2}$
- $m1 > m2$ 赢了

--------------

#### C

##### Description

给你$s[]$数组

让你构造$a[],b[]$ 满足一下条件

- $a[i]+b[i] = s[i]$
- $a[],b[]$ 中重复的数字不超过$\dfrac{n}{3}$(向上取整)

$1 \leq n \leq 1e5, 0 \leq s[] \leq 1e9$

##### Solution

这巧妙的构造 不知道该说啥了

搬图。。

![](https://assets.codeforces.com/images/297/problemC.png)

由于$s[]$是不重复的 所以$i \leq s[i](0 \leq i \leq n -1)$

看！你把前三分之一让$a[i] = i$,中间三分之一让$b[i] = i$,最后三分之一让$b[i] = n - i$

你会发现 不重复的是不会超过三分之一的！QwQ

------

##### D

##### Description

不想描述了看图吧～

![](https://codeforces.com/predownloaded/ec/e7/ece78ea07e5545ac9441cc8d0ae0a47199cf6874.png)

##### solution

**神奇的1/4**

假设横的限制多一点

那么我们用两种颜色肯定就可以满足横的所有条件

然后我们发现 一行的条件如果满足的话 那么这一行颜色都进行翻转的时候 那么显然也是满足的

所以说我们检验竖直的条件的时候 如果当前满足的条件小于1/2时 我们就翻转这一行的颜色 那么这一行与上一行满足的竖直的条件就会大于1/2了

------

#### E

拉篇博客过来～

[\CF 297E\]Mystic Carvings解题报告-cstdio](https://www.cnblogs.com/wmdcstdio/p/7554241.html)

我**莫队**又来啦！

其实那篇博客写的很详细啦～



其实要满足题设条件 就只剩下了两种情况

- 距离都为2
- 不相交

我们再把这个问题转换为图

- 如果两对洞穴相交的话 给这两个点连一条红边
- 不相交则连蓝边

一组满足条件的组合 事实上就是一个纯色三角形！

求纯色三角形实在是太rui了

所以我们求异色三角形吧

可以很显然地知道

- 一个异色三角形是有2个异色角的

那么异色角我们怎么求呢

首先所有组合是$C_n^3$

我们设对于第$i$个点 连出去的红边有$q_i$个 那么蓝边就有$n - 1 - q_i$个

那么异色三角形不就是有$\dfrac{\sum_{i=1}^nq_i*(n-1-q_i)}{2}$个嘛！

蛋四。。你发现这个答案好像不对啊！

聪明的x发现有种错误情况没有算到！

![](http://chuantu.xyz/t6/702/1562748535x2728278750.png)

我们再设与$i$不相交的有$p_i$个（包括自己）

这部分的答案就是$(p_i-1)*(n-p_i-q_i)$

如何快速地求这个相交不相交呢

事实上这个相交啊 可以看作是线段的相交

如果我们知道了$[l,r]$这个线段的答案 我们就可以$O(1)$求出$[l,r+1]$,$[l-1,r]$,$[l+1,r]$,$[l,r-1]$的答案！

分块暴力就行了

---------------

#### Code：

##### A

```c++
#include<bits/stdc++.h>
using namespace std;
const int N = 1010;
int lenx, lenl, tot = 0;
char lx[N], ll[N];

void ok() {
	printf("YES\n");
	exit(0);
}

bool check(int x) {
	for(int i = x; i <= lenx; ++i) {
		if(lx[i] != ll[i - x + 1]) return false;
	}
	return true;
}

bool get(int x, int y) {
	int pos = tot, l = 1;
	if(x == lenx) {
		if((tot & 1) && ll[1] == '0') {
			pos++;
			lx[++x] = char(49);
		}
	}
	for(int i = y; i <= lenl; ++i) {
		int tmp = ll[i] - '0';
		if(tmp != (pos & 1)) {
			int flg = 0;
			while(l <= x) {
				int gg = lx[l] - '0';
				pos -= gg;
				l++;
				if(gg) {
					flg = 1;
					break;
				}
			}
			if(!flg) {
				return false;
			}
		}
		pos += tmp;
	}
	return true;
}

int main() {
	scanf("%s%s", lx + 1, ll + 1);
	lenx = strlen(lx + 1);
	lenl = strlen(ll + 1);
	tot = 0;
	for(int i = 1; i <= lenx; ++i) {
		tot += (lx[i] == '1');
	}
	get(lenx, 1);
	for(int i = 1; i <= lenx + 1; ++i) {
		int pos = lenx - i + 1;
		if(pos > lenl) continue;
		if(check(i)) {
			pos++;
			if(pos > lenl) ok();
			if(get(i - 1, pos)) ok();
		}
	}
	printf("NO\n");
	return 0;
}
```

```c++
#include <bits/stdc++.h>
using namespace std;
const int N = 1010;
char lx[N], ll[N];

int main() {
	scanf("%s%s", lx + 1, ll + 1);
	int lenx = strlen(lx + 1);
	int lenl = strlen(ll + 1);
	int pos = 0, tmp = 0;
	for(int i = 1; i <= lenx; ++i) {
		pos += (lx[i] == '1');
	}
	for(int i = 1; i <= lenl; ++i) {
		tmp += (ll[i] == '1');
	}
	if(pos & 1) pos++;
	if(pos >= tmp) {
		printf("YES\n"); 
	} else {
		printf("NO\n");
	}
	return 0;
}
```

##### B

```c++
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int a[N], b[N], na[N], all[N];

void ok() {
	printf("YES\n");
	exit(0);
}

void fail() {
	printf("NO\n");
	exit(0);
}

int main() {
	int n, m, k, res = 0;
	scanf("%d%d%d", &n, &m, &k);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
		all[++res] = a[i];
	}
	for(int i = 1; i <= m; ++i) {
		scanf("%d", &b[i]);
		all[++res] = b[i];
	}
	sort(all + 1, all + 1 + res);
	int tot = unique(all + 1, all + 1 + res) - all - 1;
	for(int i = 1; i <= n; ++i) {
		a[i] = lower_bound(all + 1, all + 1 + tot, a[i]) - all;
		na[a[i]]++;
	}
	for(int i = 1; i <= m; ++i) {
		b[i] = lower_bound(all + 1, all + 1 + tot, b[i]) - all;
		na[b[i]]--;
	}
	for(int i = tot; i >= 1; --i) {
		na[i] += na[i + 1];
		if(na[i] > 0) {
			// printf("%d\n", i);
			ok();
		}
	}
	fail();
	return 0;
}
```

-----

##### C

```c++
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
struct data {
	int w, id;
} a[N], b[N], s[N];

bool cmp(data A, data B) {
	return A.w < B.w;
}

bool comp(data A, data B) {
	return A.id < B.id;
}

int main() {
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &s[i].w);
		s[i].id = i;
	}
	sort(s + 1, s + 1 + n, cmp);
	int pos = (n + 2) / 3;
	for(int i = 1; i <= pos; ++i) {
		a[i].w = i - 1;
		b[i].w = s[i]. w - a[i].w;
	}
	for(int i = pos + 1; i <= 2 * pos; ++i) {
		b[i].w = i - 1;
		a[i].w = s[i].w - b[i].w;
	}
	for(int i = 2 * pos + 1; i <= n; ++i) {
		b[i].w = n - i;
		a[i].w = s[i].w - b[i].w;
	}
	for(int i = 1; i <= n; ++i) {
		a[i].id = b[i].id = s[i].id;
	}
	sort(a + 1, a + 1 + n, comp);
	sort(b + 1, b + 1 + n, comp);
	printf("YES\n");
	for(int i = 1; i <= n; ++i) {
		printf("%d ", a[i].w);
	}
	puts("");
	for(int i = 1; i <= n; ++i) {
		printf("%d ", b[i].w);
	}
	return 0;
}
```

##### D

```c++
#include<bits/stdc++.h>
using namespace std;
const int N = 1010;
char lx[N];
int h[N][N], s[N][N], a[N][N];
int n, m, k;

void fail() {
	printf("NO\n");
	exit(0);
}

void out() {
	printf("YES\n");
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= m; ++j) {
			printf("%d ", a[i][j] + 1);
		}
		puts("");
	}
	exit(0);
}

void revh(int x) {
	for(int i = 1; i <= m; ++i) a[x][i] = 1 - a[x][i];
}

void revs(int x) {
	for(int i = 1; i <= n; ++i) a[i][x] = 1 - a[i][x];
}

int main() {
	scanf("%d%d%d", &n, &m, &k);
	int H = 0, S = 0;
	for(int o = 1; o < n * 2; ++o) {
		scanf("%s", lx + 1);
		int len = strlen(lx + 1);
		if(o & 1) {
			++H;
			for(int i = 1; i <= len; ++i) {
				h[H][i] = (lx[i] == 'E');
			}
		} else {
			++S;
			for(int i = 1; i <= len; ++i) {
				s[S][i] = (lx[i] == 'E');
			}
		}
	}
	if(k == 1) {
		int pos = 0, tot = 2 * m * n - m - n;
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j < m; ++j) {
				int tmp = (a[i][j] == a[i][j + 1]);
				pos += (tmp != h[i][j]);
			}
		for(int i = 1; i < n; ++i)
			for(int j = 1; j <= m; ++j) {
				int tmp = (a[i][j] == a[i + 1][j]);
				pos += (tmp != s[i][j]);
			}
		if(pos * 4 > tot) fail();
		else out();
	} else if(n <= m) {
		for(int i = 1; i <= n; ++i) {
			for(int j = 2; j <= m; ++j) {
				if(!h[i][j - 1]) {
					a[i][j] = 1 - a[i][j - 1];
				} else {
					a[i][j] = a[i][j - 1];
				}
			}
			if(i > 1) {
				int pos = 0;
				for(int j = 1; j <= m; ++j) {
					int tmp = (a[i][j] == a[i - 1][j]);
					pos += (tmp != s[i - 1][j]);
				}
				// printf("%d %d\n",i ,pos);
				if(pos > m / 2) revh(i);
			}
		}
		out();
	} else {
		for(int j = 1; j <= m; ++j) {
			for(int i = 2; i <= n; ++i) {
				if(!s[i - 1][j]) {
					a[i][j] = 1 - a[i - 1][j];
				} else {
					a[i][j] = a[i - 1][j];
				}
			}
			if(j > 1) {
				int pos = 0;
				for(int i = 1; i <= n; ++i) {
					int tmp = (a[i][j] == a[i][j - 1]);
					pos += (tmp != h[i][j - 1]);
				}
				if(pos > n / 2) revs(j);
			}
		}
		out();
	}
	return 0;
}
```

##### E

```c++
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 2e5 + 10;
struct data {
	int l, r;
} a[N];
int mx[N], bsz, nl = 1, nr = 0, jx = 0, px = 0, n;

bool cmp(data A, data B) {
	return (A.l / bsz == B.l / bsz) ? A.r < B.r : A.l / bsz < B.l / bsz;
}

void add(int x) {
	if(nl <= mx[x] && mx[x] <= nr) px++, jx--;
	else jx++;
}

void del(int x) {
	if(nl <= mx[x] && mx[x] <= nr) px--, jx++;
	else jx--;
}

int main() {
	scanf("%d", &n);
	bsz = sqrt(n * 2.0);
	for(int i = 1, x, y; i <= n; ++i) {
		scanf("%d%d", &a[i].l, &a[i].r);
		mx[a[i].l] = a[i].r, mx[a[i].r] = a[i].l;
		if(a[i].l > a[i].r) swap(a[i].l, a[i].r);
	}
	sort(a + 1, a + 1 + n, cmp);
	ll ans = 1ll * n * (n - 1) * (n - 2) / 6, pos = 0, tmp = 0;
	for(int i = 1; i <= n; ++i) {
		// printf("qwq%d %d\n", a[i].l, a[i].r);
		while(nl > a[i].l) add(--nl);
		while(nr < a[i].r) add(++nr);
		while(nl < a[i].l) del(nl++);
		while(nr > a[i].r) del(nr--);
		// printf("%lld %lld\n", jx, px);
		pos += 1ll * jx * (n - 1 - jx);
		tmp += 1ll * (px - 1) * (n - px - jx);
	}
	ans -= pos / 2 + tmp;
	printf("%lld\n", ans);
	return 0;
}
```

