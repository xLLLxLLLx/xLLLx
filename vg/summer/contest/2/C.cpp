#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 5e5 + 10, mod = 1e9 + 7;
struct data {
	int x, y;
	ll w;
} a[N];
map<ll, int> mp;
int f[N];
ll v[N], pw[N] = {1};

bool cmp(data A, data B) {
	return A.w < B.w;
}

int find(int k) {
	return f[k] == k ? k : f[k] = find(f[k]);
}

int main() {
	int n, m, k, tot = 0;
	scanf("%d%d%d", &n, &m, &k);
	for(int i = 1; i <= n; ++i) {
		pw[i] = pw[i - 1] * 2ll % mod;
		f[i] = i;
	}
	for(int i = 1; i <= n; ++i) {
		scanf("%lld", &v[i]);
	}
	for(int i = 1; i <= m; ++i) {
		scanf("%d%d", &a[i].x, &a[i].y);
		a[i].w = v[a[i].x] ^ v[a[i].y];
		if(!mp.count(a[i].w)) {
			mp[a[i].w] = 1;
			tot++;
		}
	}
	sort(a + 1, a + 1 + m, cmp);
	ll ans = ((1ll << k) - tot + mod) % mod * pw[n] % mod;
	for(int i = 1; i <= m; ++i) {
		int cnt = n, r = m;
		for(int j = i; j <= m; ++j) {
			if(j == i || a[j].w == a[j - 1].w) {
				int fx = find(a[j].x), fy = find(a[j].y);
				if(fx != fy) {
					cnt--;
					f[fx] = fy;
				}
			} else {
				r = j - 1;
				break;
			}
		}
		ans = (ans + pw[cnt]) % mod;
		for(int j = i; j <= r; ++j) {
			f[a[j].x] = a[j].x, f[a[j].y] = a[j].y;
		}
		i = r;
	}
	printf("%lld\n", ans);
	return 0;
}