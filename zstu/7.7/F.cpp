#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 5e6 + 10;
int pr[N], flg[N];
int yz[N], a[N];
 
void init() {
    for(int i = 1; i < N; ++i) a[i] = i;
    for(int i = 2; i < N; ++i) {
        if(!flg[i]) pr[++pr[0]] = i;
        for(int j = 1; j <= pr[0]; ++j) {
            if(i * pr[j] >= N) break;
            flg[i * pr[j]] = 1;
            if(i % pr[j] == 0) break;
        }
    }
}
 
int main() {
    init();
    int n, m;
    scanf("%d%d", &n, &m);
    if(n == m) {
        return printf("8\n"), 0;
    }
    int res = 0, l = n, r = 0;
    ll ans = 0;
    for(int i = 1; i <= n; ++i) {
        if(n / i != m) continue;
        l = min(l, i), r = max(r, i);
    }
    for(int i = 1; i <= pr[0]; ++i) {
        int L = l / pr[i], R = r / pr[i] + 1;
        for(int j = L; j <= R; ++j) {
            int pos = j * pr[i];
            if(pos >= N) continue;
            a[pos] /= pr[i];
            a[pos] *= (pr[i] - 1);
        }
    }
    for(int i = l; i <= r; ++i) {
        ans += a[i];
    }
    ans *= 8 * 1ll;
    cout<<ans<<endl;
    return 0;
}