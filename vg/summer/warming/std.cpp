#include <iostream>
#include <algorithm>
#include <cstdio>
#include <queue>
#include <map>
#define REP(i,a,n) for(int i=a;i<=n;++i)
#define pb push_back
using namespace std;
typedef pair<int,int> pii;
const int N = 1e6+10;
int n, q, cnt, x[N], y[N], c[N];
int L[N], R[N], ans[N];
struct _ {int l,r;} b[N];
vector<int> g[N];
pii a[N];
map<pii,int> pre;
 
int gcd(int a,int b) {return b?gcd(b,a%b):a;}
pii reduce(int x, int y) {
    int g = gcd(abs(x),abs(y));
    if (g) x/=g,y/=g;
    return pii(x,y);
}
void add(int x, int v) {
    for (; x<=cnt; x+=x&-x) c[x]+=v;
}
int query(int x) {
    int r = 0;
    for (; x; x^=x&-x) r+=c[x];
    return r;
}
 
int main() {
    scanf("%d", &n);
    REP(i,1,n) {
        int k;
        scanf("%d", &k);
        REP(j,0,k-1) scanf("%d%d",x+j,y+j);
        L[i] = cnt+1;
        REP(j,0,k-1) a[++cnt] = reduce(x[j]-x[(j+1)%k],y[j]-y[(j+1)%k]);
        R[i] = cnt;
    }
    scanf("%d", &q);
    REP(i,1,q) {
        int l, r;
        scanf("%d%d", &l, &r);
        b[i].l = L[l];
        b[i].r = R[r];
        g[b[i].r].pb(i);
    }
    int now = 1;
    REP(i,1,cnt) {
        if (pre[a[i]]) add(pre[a[i]],-1);
        pre[a[i]] = i;
        add(i,1);
        for (int j:g[i]) ans[j] = query(b[j].r)-query(b[j].l-1);
    }
    REP(i,1,q) printf("%d\n", ans[i]);
}
