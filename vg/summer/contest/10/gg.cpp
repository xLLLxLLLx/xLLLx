#include<bits/stdc++.h>
#define LL long long
#define LD long double
#define ull unsigned long long
#define fi first
#define se second
#define mk make_pair
#define PLL pair<LL, LL>
#define PLI pair<LL, int>
#define PII pair<int, int>
#define SZ(x) ((int)x.size())
#define ALL(x) (x).begin(), (x).end()
#define fio ios::sync_with_stdio(false); cin.tie(0);

using namespace std;

const int N = 4e5 + 7;
const int inf = 0x3f3f3f3f;
const LL INF = 0x3f3f3f3f3f3f3f3f;
const int mod = 998244353;
const double eps = 1e-8;
const double PI = acos(-1);

template<class T, class S> inline void add(T& a, S b) {a += b; if(a >= mod) a -= mod;}
template<class T, class S> inline void sub(T& a, S b) {a -= b; if(a < 0) a += mod;}
template<class T, class S> inline bool chkmax(T& a, S b) {return a < b ? a = b, true : false;}
template<class T, class S> inline bool chkmin(T& a, S b) {return a > b ? a = b, true : false;}

const int B = 200001;

int n;
vector<PII> v[2];

int upL[N], dnL[N];
int upR[N], dnR[N];

LL solve(vector<PII> &v) {
    memset(upL, 0xc0, sizeof(upL));
    memset(dnL, 0x3f, sizeof(dnL));
    memset(upR, 0xc0, sizeof(upR));
    memset(dnR, 0x3f, sizeof(dnR));
    for(auto& t : v) {
        chkmax(upL[t.fi], t.se);
        chkmin(dnL[t.fi], t.se);
        chkmax(upR[t.fi], t.se);
        chkmin(dnR[t.fi], t.se);
    }
    for(int i = 1; i < N; i++) {
        chkmax(upL[i], upL[i - 1]);
        chkmin(dnL[i], dnL[i - 1]);
    }
    for(int i = N - 2; i >= 1; i--) {
        chkmax(upR[i], upR[i + 1]);
        chkmin(dnR[i], dnR[i + 1]);
    }
    LL ans = 0;
    for(int i = 1; i < N - 1; i += 2) {
        int up = min(upL[i], upR[i]);
        int dn = max(dnL[i], dnR[i]);
        if(up > dn) ans += (up - dn) / 2;
    }
    return ans;
}

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        int x, y; scanf("%d%d", &x, &y);
        int z = (x + y + B) & 1;
        v[z].push_back(mk(x + y + B + z, x - y + B + z));
    }
    LL ans = 0;
    ans += solve(v[0]);
    printf("%lld\n", ans);
    ans += solve(v[1]);
    printf("%lld\n", ans);
    return 0;
}

/*
*/