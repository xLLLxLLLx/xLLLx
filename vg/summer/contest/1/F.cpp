#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e5 + 10;
const ll inf = 1e18;
queue<int> q;
ll f[N];
int vis[N], d[N];
ll yz[N];

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

int main() {
	int T;
	scanf("%d", &T);
	for(int i = 0; i < N; ++i) {
		f[i] = inf;
	}
	for(int o = 1; o <= T; ++o) {
		ll n, k;
		scanf("%lld%lld", &n, &k);
		if(k == 1) {
			printf("YES\n");
			continue;
		}
		yz[0] = 0;
		int len = sqrt(k);
		for(int i = 2; i <= len; ++i) {
			if(k % i == 0) {
				yz[++yz[0]] = i;
				while(k % i == 0) {
					k /= i;
				}
			}
			if(k == 1) break;
		}
		if(k > 1) yz[++yz[0]] = k;
		for(int i = 1; i <= yz[0]; ++i) {
			cout<<yz[i]<< " ";
		}
		if(yz[0] == 1) {
			if(n % yz[1]) {
				printf("NO\n");
			} else {
				printf("YES\n");
			}
		} else if(yz[0] == 2) {
			ll pos = q_pow(yz[2], yz[1] - 2, yz[1]);
			// printf("qwq%lld\n", pos);
			pos = pos * n % yz[1];
			if(pos * yz[2] > n) printf("NO\n");
			else printf("YES\n");
		} else {
			q.push(0);
			f[0] = 0;
			while(!q.empty()) {
				int h = q.front(); q.pop();
				// printf("%d %lld\n", h, f[h]);
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
			if(f[n % yz[1]] <= n) printf("YES\n");
			else printf("NO\n");
			for(int i = 0; i < yz[1]; ++i) {
				f[i] = inf, vis[i] = 0;
			}
		}
	}
	return 0;
}