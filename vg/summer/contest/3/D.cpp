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