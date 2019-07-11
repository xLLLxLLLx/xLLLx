#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e6 + 10, M = 3e7 + 10;
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