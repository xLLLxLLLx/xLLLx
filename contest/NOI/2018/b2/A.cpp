#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e5 + 10;
multiset<ll> s;
multiset<ll> :: iterator it;
ll a[N], p[N], b[N], c[N], atk[N];
int T, n, m;

#define fi first
#define se second
typedef pair<ll, ll> P;

struct node {
	ll x, m;
} d[N];

namespace CRT {
	ll mod;
	ll gcd(ll A, ll B) {
		return B ? gcd(B, A % B) : A;
	}

	ll mul(ll x, ll y) {
		x %= mod, y %= mod;
		ll ans = 0;
		for(; y; y >>= 1) {
			if(y & 1) ans = (ans + x) % mod;
			x = (x + x) % mod;
		}
		return ans;
	}

	void exgcd(ll a, ll b, ll &x, ll &y){
    if(!b) {
    	x = 1ll, y = 0ll;
    	return ;
    }
    exgcd(b, a % b, y, x);
    y -= a / b * x;
  }

  P get_exgcd(ll a, ll b, ll c) {
  	// puts("exgcd");
  	ll g = gcd(a, b);
  	if(c % g) return P(-1ll, -1ll);
  	ll x, y;
  	exgcd(a, b, x, y);
  	// puts("hello");
  	x = (x + mod) % mod, y = (y + mod) % mod;
  	x = mul(x, c / g), y = mul(y, c / g);
  	return P(x, y);
  }

  node merge(node A, node B) {
  	if(A.x > B.x) swap(A, B);
  	ll g = gcd(A.m, B.m);
  	mod = A.m / g * B.m;
  	P now = get_exgcd(A.m, B.m, B.x - A.x);
  	// printf("%lld %lld\n", now.fi, now.se);
  	if(now.fi == -1) return (node){-1ll, -1ll};
  	return (node){(A.x + mul(A.m, now.fi)) % mod, mod};
  }

  node solve(node *A) {
  	// puts("solve");
  	if(n == 1) return A[1];
  	node now = merge(A[1], A[2]);
  	// puts("sov");
  	for(int i = 3; i <= n; now = merge(now, A[i]), ++i) {
  		// printf("%d\n", i);
  		if(now.x == -1 && now.m == -1) return now;
  	}
  	return now;
  }
}

ll get(ll x) {
	ll pos;
	it = s.upper_bound(x);
	if(it != s.begin())
		--it;
	pos = *it;
	return pos;
}

void solve() {
	// printf("IN!!\n");
	for(int i = 1; i <= n; ++i) {
		CRT::mod = p[i];
		P now = CRT::get_exgcd(atk[i], p[i], a[i]);
		if(now.fi == -1) {
			// printf("%lld %lld %lld\n", atk[i], p[i], a[i]);
			puts("-1");
			return ;
		}
		d[i] = (node){now.fi, p[i] / CRT::gcd(atk[i], p[i])};
	}
	node res = CRT::solve(d);
	if(res.x == -1 && res.m == -1) {
		puts("-1");
		return;
	}
	// printf("WA!!\n");
	ll x= res.x, m = res.m;
	x %= m;
	for(int i = 1; i <= n; ++i) {
		ll ned = a[i] / atk[i];
		if(a[i] % atk[i]) ned++;
		if(x < ned) {
			ll tmp = ned - x;
			x += tmp / m;
			if(tmp % m) x ++;
		}
	}
	printf("%lld\n", x);
}

int main() {
	freopen("dragon.in", "r", stdin);
	freopen("dragon.out", "w", stdout);
	scanf("%d", &T);
	for(int o = 1; o <= T; ++o) {
		// printf("q%d\n", o);
		s.clear();
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; ++i) {
			scanf("%lld", &a[i]);	
		}
		for(int i = 1; i <= n; ++i) {
			scanf("%lld", &p[i]);
		}
		for(int i = 1; i <= n; ++i) {
			scanf("%lld", &b[i]);
		}
		for(int i = 1; i <= m; ++i) {
			scanf("%lld", &c[i]);
			s.insert(c[i]);
		}
		for(int i = 1; i <= n; ++i) {
			atk[i] = get(a[i]);
			s.erase(s.find(atk[i]));
			s.insert(b[i]);
		}
		// printf("p%d\n", o);
		// for(int i = 1; i <= n; ++i)
		// 	printf("%lld ", atk[i]);
		// puts("");
		solve();
	}
	return 0;
}  