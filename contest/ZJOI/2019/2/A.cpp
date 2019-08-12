#include <bits/stdc++.h>
#define ll __int128
using namespace std;
ll gcd(ll x, ll y) { return y ? gcd(y, x % y) : x; }
ll sol(ll l, ll m, ll k) {
    ll d = gcd(m, k);
    if (d == 1)
        return l;
    if (l > k / d)
        return m * (k - l) / d + sol((k - m * (k - l)) / d, m, k / d);
    return l;
}
int T;
ll m, k;
signed main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%lld %lld", &m, &k);
        printf("%lld\n", sol(k - 1, m, k) + 1);
    }
    return 0;
}
