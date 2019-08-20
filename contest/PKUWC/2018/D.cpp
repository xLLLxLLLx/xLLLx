#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 22, M = (1 << 22) + 1, mod = 998244353;
ll f[M][N], jc[N], ny[N];
int mk[N], cnt[M];

ll mul(ll x, ll y) {
	return x * y % mod;
}

void Add(ll &x, ll y) {
	x = (x + y) % mod;
}

ll q_pow(ll x, int y) {
	ll ans = 1;
	for(; y; y >>= 1) {
		if(y & 1) ans = mul(ans, x);
		x = mul(x, x);
	}
	return ans;
}

void init() {
	jc[0] = ny[0] = 1;
	for(int i = 1; i < N; ++i)
		jc[i] = mul(jc[i - 1], i);
	ny[N - 1] = q_pow(jc[N - 1], mod - 2);
	for(int i = N - 1; i >= 1; --i)
		ny[i - 1] = mul(ny[i], i);
}

ll A(int x, int y) {
	return mul(jc[x], ny[x - y]);
}

int get(int x) {
	int res = 0;
	for(; x; x &= (x - 1))
		res++;
	return res;
}

int main() {
	init();
	int n, m;
	scanf("%d%d", &n, &m);
	int tot = (1 << n) - 1;
	for(int i = 0; i < n; ++i)
		mk[i] |= (1 << i);
	for(int i = 1, x, y; i <= m; ++i) {
		scanf("%d%d", &x, &y);
		x--, y--;
		mk[x] |= (1 << y), mk[y] |= (1 << x);
	}
	for(int i = 0; i <= tot; ++i) {
		cnt[i] = get(i);
	}
	f[0][0] = 1;
	for(int i=0;i<=tot;i++)
    for(int k=0;k<n;k++)
    if(((1<<k)&i)==0){
    		// printf("%d %d\n", i, k);
        int v=i|mk[k];
        int x=cnt[mk[k]]-cnt[i&mk[k]]-1;
        int t=n-cnt[i]-1;
        for(int j=0;j<=n;j++) {
        	// printf("%d\n", j);
        	if(f[i][j]) {
        		f[v][j + 1]=(f[v][j + 1]+f[i][j]*A(t,x)%mod)%mod;
        	}
       	}
    }
	for(int i = n; i >= 0; --i) {
		if(f[tot][i]) {
			return printf("%lld\n", mul(f[tot][i], ny[n])), 0;
		}
	}
	return 0;
}
