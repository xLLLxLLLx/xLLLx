#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 2e5 + 10;
int n, m;
int ans[N], id[N];

struct num {
	ll a, b, c;
	num() {
		a = b = 0;
		c = 1;
	}
	num(ll x, ll y) {
		if(y < 0) x = -x, y = -y;
		a = x / y;
		b = x % y;
		c = y;
		if(b < 0)
			b += c, a--;
	}
	ll floor() { return a; }
	ll ceil() { return a + (b > 0); }
	bool operator < (const num &C) const {
		return a == C.a ? b * C.c < C.b * c : a < C.a;
	}
	bool operator <= (const num &C) const {
		return a == C.a ? b * C.c <= C.b * c : a < C.a;
	}
};

ll a[N], b[N];
num cross(int x, int y) {
	return num(b[x] - b[y], a[y] - a[x]);
}

int s[N];
num p[N];
pair<ll, int> S[N];

void work(int k) {
	int top, tot;
	p[top = tot = 0] = num(0, 1);
	for(int i = 1; i <= n; ++i) {
		if(ans[id[i]] == -1 && a[id[i]] > a[s[top]]) {
			for(; top && cross(id[i], s[top]).floor() < p[top].ceil(); --top) ;
			s[++top] = id[i];
			if(top > 1)
				p[top] = cross(s[top - 1], id[i]);
		}
	}
	p[top + 1] = num(1ll << 60, 1);
	for(int i = 1; i <= n; ++i) {
		if(ans[i] > 0) {
			int l = 1, r = top - 1, tt = top;
			while(l <= r) {
				int mid = (l + r) >> 1;
				if(a[s[mid]] >= a[i] || cross(s[mid], i) <= p[mid + 1])
					tt = mid, r = mid - 1;
				else 
					l = mid + 1;
			}
			S[++tot] = make_pair(a[s[tt]] >= a[i] ? 0ll : cross(s[tt], i).floor() + 1, 1);
			l = 2, r = top, tt = 1;
			while(l <= r) {
				int mid = (l + r) >> 1;
				if(a[s[mid]] <= a[i] || p[mid] <= cross(s[mid], i))
					tt = mid, l = mid + 1;
				else
					r = mid - 1;
			}
			if(a[s[tt]] > a[i])
				S[++tot] = make_pair(cross(s[tt], i).ceil(), -1);
		}
	}
	sort(S + 1, S + 1 + tot);
	int now = 0;
	for(int i = 1, j = 1; i <= top; ++i) {
		while(j <= tot && S[j].first <= p[i].ceil())
			now += S[j++].second;
		if(now < k) 
			ans[s[i]] = k;
		while(j <= tot && S[j].first <= p[i + 1].floor()) {
			int l = j;
			while(l <= tot && S[l].first == S[j].first) 
				now += S[l++].second;
			if(now < k)
				ans[s[i]] = k;
			j = l;
		}
	}
}

bool cmp(int x, int y) {
	return a[x] == a[y] ? b[x] > b[y] : a[x] < a[y];
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i) {
		scanf("%lld%lld", &a[i], &b[i]);
		id[i] = i;
	}
	sort(id + 1, id + 1 + n, cmp);
	memset(ans, -1, sizeof ans);
	for(int i = 1; i <= m; ++i) 
		work(i);
	for(int i = 1; i <= n; ++i)
		printf("%d ", ans[i]);
	return 0;
}