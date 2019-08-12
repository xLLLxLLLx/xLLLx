#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 5e6 + 10, mod = 998244353;
ll jc[N], ny[N];

ll mul(ll x, ll y) { return x * y % mod; }

ll add(ll x, ll y) { return (x + y) % mod; }

ll sub(ll x, ll y) { return ((x - y) % mod + mod) % mod; }

ll q_pow(ll x, int y) {
    ll ans = 1;
    for (; y; y >>= 1) {
        if (y & 1)
            ans = mul(ans, x);
        x = mul(x, x);
    }
    return ans;
}

ll C(int x, int y) {
    if (x < y)
        return 0;
    return mul(jc[x], mul(ny[y], ny[x - y]));
}

void init() {
    jc[0] = ny[0] = 1;
    for (int i = 1; i < N; ++i) jc[i] = mul(jc[i - 1], i);
    ny[N - 1] = q_pow(jc[N - 1], mod - 2);
    for (int i = N - 2; i >= 1; --i) ny[i] = mul(ny[i + 1], i + 1);
}

int n, m, l, k;
ll tot;
ll js(int x) { return mul(n - x, mul(m - x, l - x)); }

ll g(int x) { return sub(tot, mul(n - x, mul(m - x, l - x))); }

int main() {
    init();
    int T;
    scanf("%d", &T);
    for (int o = 1; o <= T; ++o) {
        scanf("%d%d%d%d", &n, &m, &l, &k);
        tot = 1ll * n * m * l % mod;
        int mi = min(n, min(m, l));
        ll ans = 0, opt = -1, tmp = 1, res = 1;
        if (k & 1)
            opt = 1;
        for (int i = 1; i <= mi; ++i) {
            ll pos = opt * C(i, k);
            // printf("%lld\n", pos);
            tmp = mul(tmp, q_pow(g(i), mod - 2));
            res = mul(res, js(i - 1));
            pos = mul(pos, mul(res, tmp));
            // printf("%lld %lld %lld\n", pos, tmp, res);
            ans = add(ans, pos);
            opt = -opt;
        }
        printf("%lld\n", (ans + mod) % mod);
    }
    return 0;
}