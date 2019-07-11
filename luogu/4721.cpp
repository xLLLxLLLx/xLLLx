#include <bits/stdc++.h>
#define ll long long
using namespace std;
const double PI = acos(-1.0);
const int N = (1 << 20), mod = 998244353;
int n = 1, L = 0;
int rev[N];
ll a[N], b[N], c[N], g[N], f[N], k[N];

ll q_pow(ll x, int y) {
    ll ans = 1;
    for(; y; y >>= 1) {
        if(y & 1) ans = ans * x % mod;
        x = x * x % mod;
    }
    return ans;
}

void ntt(ll a[N], int n) {
    for(int i = 0; i < n; ++i) 
        if(rev[i] > i)
            swap(a[i], a[rev[i]]);
    for(int t = n >> 1, d = 1; d < n; t >>= 1, d <<= 1)
        for(int i = 0; i < n; i += (d << 1))
            for(int j = 0; j < d; ++j) {
                ll tmp = g[t * j] * a[i + j + d] % mod;
                a[i + j + d] = (a[i + j] - tmp + mod) % mod;
                a[i + j] = (a[i + j] + tmp) % mod;
            }
}

void goNTT(ll a[N], ll b[N], ll c[N]) {
    for(int i = 0; i < n; ++i) {
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (L - 1));
    }
    g[0] = 1, g[1] = q_pow(3, (mod - 1) / n);
    for(int i = 2; i < n; ++i) {
        g[i] = g[i - 1] * g[1] % mod;
    }
    ntt(a, n), ntt(b, n);
    for(int i = 0; i < n; ++i) {
        a[i] = a[i] * b[i] % mod;
    }
    g[1] = q_pow(g[1], mod - 2);
    for(int i = 2; i < n; ++i) {
        g[i] = g[i - 1] * g[1] % mod;
    }
    ntt(a, n);
    ll pos = q_pow(n, mod - 2);
    for(int i = 0; i < n; ++i) {
        c[i] = a[i] * pos % mod;
        a[i] = b[i] = 0;
    }
}

void work(int l, int r) {
    if(l == r) {
        return ;
    }
    int mid = (l + r) >> 1;
    work(l, mid);
    for(int i = l; i <= mid; ++i) a[i - l] = f[i];
    for(int i = 1; i <= r - l; ++i) b[i] = k[i];
    int len = r + mid - 2 * l + 2;
    n = 1, L = 0;
    for(; n < len; n <<= 1, L++) ;
    goNTT(a, b, c);
    for(int i = mid + 1 - l; i <= r - l; ++i) f[i + l] = (f[i + l] + c[i]) % mod;
    work(mid + 1, r);
}

int main() {
    int m;
    scanf("%d", &m);
    for(int i = 1; i < m; ++i) {
        scanf("%lld", &k[i]);
    }
    f[0] = 1, work(0, m - 1);
    for(int i = 0; i < m; ++i) {
        printf("%lld ", f[i]);
    }
    return 0;
}