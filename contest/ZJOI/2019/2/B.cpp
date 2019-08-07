#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
#define go(u) for(int i = head[u], v = e[i].to; i; i = e[i].lst, v = e[i].to)
#define rep(i, a, b) for(int i = a; i <= b; ++i)
#define pb push_back
inline int gi() {
    int x = 0,f = 1;
    char ch = getchar();
    while(!isdigit(ch)) { if(ch == '-') f = -1; ch = getchar();}
    while(isdigit(ch)) { x = (x << 3) + (x << 1) + ch - 48; ch = getchar();}
    return x * f;
}
template <typename T> inline bool Max(T &a, T b){return a < b ? a = b, 1 : 0;}
template <typename T> inline bool Min(T &a, T b){return a > b ? a = b, 1 : 0;}
const int N = 1e5 + 7;
LL ans;
int n, m, edc, elc, ndc, tim;
int head[N], fa[N], in[N], out[N], fie[N], Log[N << 1], dep[N];
typedef pair<int, int> pii;
pii mi[N << 1][20];
struct edge {
    int lst, to;
    edge(){}edge(int lst, int to):lst(lst), to(to){}
}e[N << 1];
void Add(int a, int b) {
    e[++edc] = edge(head[a], b), head[a] = edc;
    e[++edc] = edge(head[b], a), head[b] = edc;
}
void dfs1(int u) {
    in[u] = ++tim;
    mi[++elc][0] = make_pair(in[u], u);
    fie[u] = elc;
    go(u)if(v ^ fa[u]) {
        fa[v] = u;
        dep[v] = dep[u] + 1;
        dfs1(v);
        mi[++elc][0] = make_pair(in[u], u);
    }
    out[u] = tim;
}
int Lca(int l, int r) {
    l = fie[l], r = fie[r];
    if(l > r) swap(l, r);
    int k = Log[r - l + 1];
    return min(mi[l][k], mi[r - (1 << k) + 1][k]).second;
}
int rt[N];
vector<int>G[N];
struct node {int l, r, A, B, cnt, s;}t[N * 150];
#define Ls t[o].l
#define Rs t[o].r
void pushup(int o) {
    t[o].A = t[Ls].A ? t[Ls].A : t[Rs].A;
    t[o].B = t[Rs].B ? t[Rs].B : t[Ls].B;
    t[o].s = t[Ls].s + t[Rs].s;
    if(t[Ls].B && t[Rs].A) t[o].s -= dep[Lca(t[Ls].B, t[Rs].A)];
}
void modify(int p, int l, int r, int &o, int v) {
    if(!o) o = ++ndc;
    if(l == r) {
        t[o].cnt += v;
        if(t[o].cnt) t[o].A = t[o].B = p, t[o].s = dep[p];
        else t[o].A = t[o].B = t[o].s = 0;
        return;
    }int mid = l + r >> 1;
    if(in[p] <= mid) modify(p, l, mid, Ls, v);
    else modify(p, mid + 1, r, Rs, v);
    pushup(o);
}
int merge(int l, int r, int x, int y) {
    if(!x || !y) return x + y;
    if(l == r) {
        t[x].cnt += t[y].cnt;
        if(t[x].cnt) t[x].A = t[x].B = max(t[x].A, t[y].A), t[x].s = dep[t[x].A];
        else t[x].A = t[x].B = t[x].s = 0;
        return x;
    }int mid = l + r >> 1;
    t[x].l = merge(l, mid, t[x].l, t[y].l);
    t[x].r = merge(mid + 1, r, t[x].r, t[y].r);
    return pushup(x), x;
}
void dfs2(int u) {
    go(u)if(v ^ fa[u]) {
        dfs2(v);
        rt[u] = merge(1, n, rt[u], rt[v]);
    }
    for(auto v:G[u]) modify(v, 1, n, rt[u], -2);
    if(t[rt[u]].A && t[rt[u]].B)
        ans += t[rt[u]].s - dep[fa[Lca(t[rt[u]].A, t[rt[u]].B)]] - 1;
}
int main() {
    n = gi(), m = gi();
    rep(i, 1, n - 1)
        Add(gi(), gi());
    dep[1] = 1, dfs1(1);
    for(int k = 1; 1 << k <= elc; ++k)
    for(int i = 1; i + (1 << k) - 1 <= elc; ++i)
        mi[i][k] = min(mi[i][k - 1], mi[i + (1 << k - 1)][k - 1]);
    for(int i = 2; i <= elc; ++i)
        Log[i] = Log[i >> 1] + 1;
    rep(i, 1, m) {
        int x = gi(), y = gi(), lca = Lca(x, y);
        modify(x, 1, n, rt[x], 1);
        modify(y, 1, n, rt[x], 1);
        modify(x, 1, n, rt[y], 1);
        modify(y, 1, n, rt[y], 1);
        if(fa[lca]) G[fa[lca]].pb(x), G[fa[lca]].pb(y);
    }
    dfs2(1);
    // printf("%d\n", ndc);
    printf("%lld\n", ans / 2);
    return 0;
}