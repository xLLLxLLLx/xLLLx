#include <bits/stdc++.h>
#define lc ch[0][u]
#define rc ch[1][u]
using namespace std;
typedef long long ll;
const int N= 1010, M = 200010;
const int dir[4][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};
int n, m, lb = 1, rb = 1;
int a[N][N], idx[M], idy[M];
int fa[M], ch[2][M], sta[M], top; bool rv[M];
int tr[M * 4], sum[M * 4], lz[M * 4], fst, snd;
ll ans = 1;

inline int Min(const int &x, const int &y) { return x < y ? x : y; }
inline bool nroot(int u) { return ch[0][fa[u]] == u || ch[1][fa[u]] == u; }
inline void Rev(int u) { rv[u] ^= 1, swap(lc, rc); }
inline void pd(int u) { if(rv[u]) Rev(lc), Rev(rc), rv[u] = 0; }
void rotate(int u) {
    int y = fa[u], z = fa[y], k = ch[1][y] == u, w = ch[k ^ 1][u];
    if(nroot(y)) ch[ch[1][z] == y][z] = u; ch[k][y] = w, ch[k ^ 1][u] = y;
    if(w) fa[w] = y; fa[u] = z, fa[y] = u;
}
void splay(int u) {
    int y = u, z; for(sta[top = 1] = y; nroot(y); sta[++top] = y = fa[y]);
    for(; top; pd(sta[top--]));
    for(; nroot(u); rotate(u)) {
        y = fa[u], z = fa[y];
        if(nroot(y)) rotate((ch[0][y] == u) ^ (ch[0][z] == y) ? u : y);
    }
}
inline void access(int u) {
    for(int y = 0; u; u = fa[y = u]) splay(u), rc = y;
}
inline void makeroot(int u) { access(u), splay(u), Rev(u); }
inline int findroot(int u) {
    access(u), splay(u); for(; lc; pd(u), u = lc); splay(u); return u;
}
inline void split(int x, int y) { 
    makeroot(x);
        access(y);
        splay(y);
}
inline void lnk(int x, int y) { makeroot(x), fa[x] = y; }
inline void cut(int x, int y) { split(x, y), fa[x] = ch[0][y] = 0; }
void pushup(int u) {
    sum[u] = 0, tr[u] = Min(tr[u * 2], tr[u * 2 + 1]);
    if(tr[u] == tr[u * 2]) sum[u] += sum[u * 2];
    if(tr[u] == tr[u * 2 + 1]) sum[u] += sum[u * 2 + 1];
}
void pushdown(int u) {
    if(!lz[u]) return ;
    lz[u * 2] += lz[u], lz[u * 2 + 1] += lz[u];
    tr[u * 2] += lz[u], tr[u * 2 + 1] += lz[u];
    lz[u] = 0;
}
void build(int u, int l, int r) {
    tr[u] = 0, sum[u] = r - l + 1; if(l >= r) return ;
    int mid = (l + r) >> 1;
    build(u * 2, l, mid), build(u * 2 + 1, mid + 1, r);
}
void mdy(int u, int l, int r, int L, int R, int w) {
    if(L <= l && r <= R) { tr[u] += w, lz[u] += w; return ; }
    int mid = (l + r) >> 1; pushdown(u);
    if(L <= mid) mdy(u * 2, l, mid, L, R, w);
    if(R > mid) mdy(u * 2 + 1, mid + 1, r, L, R, w);
    pushup(u);
}
void ask(int u, int l, int r, int L, int R) {
    if(L <= l && r <= R) {
        if(fst > tr[u]) fst = tr[u], snd = 0; if(fst == tr[u]) snd += sum[u];
        return ;
    }
    int mid = (l + r) >> 1; pushdown(u);
    if(L <= mid) ask(u * 2, l, mid, L, R);
    if(R > mid) ask(u * 2 + 1, mid + 1, r, L, R);
}
bool check() {
    static int tmp[5]; int len = 0;
    for(int i = 0; i < 4; i++) {
        int x = idx[rb + 1] + dir[i][0], y = idy[rb + 1] + dir[i][1];
        if(!x || !y || x > n || y > m || a[x][y] < lb || a[x][y] > rb)
            continue;
        tmp[++len] = findroot(a[x][y]);
    }
    sort(tmp + 1, tmp + len + 1);
    for(int i = 1; i < len; i++) if(tmp[i] == tmp[i + 1]) return 0;
    return 1;
}
int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++)
        scanf("%d", &a[i][j]), idx[a[i][j]] = i, idy[a[i][j]] = j;
    build(1, 1, n * m), mdy(1, 1, n * m, 1, 1, 1);
    for(; rb < n * m;) {
        for(; lb < rb && !check(); ++lb) for(int i = 0; i < 4; i++) {
            int x = idx[lb] + dir[i][0], y = idy[lb] + dir[i][1];
            if(!x || !y || x > n || y > m || a[x][y] < lb || a[x][y] > rb)
                continue;
            cut(lb, a[x][y]);
        }
        ++rb, mdy(1, 1, n * m, lb, rb, 1);
        printf("a%d %d\n", lb, rb);
        for(int i = 0; i < 4; i++) {
            int x = idx[rb] + dir[i][0], y = idy[rb] + dir[i][1];
            if(!x || !y || x > n || y > m || a[x][y] < lb || a[x][y] > rb)
                continue;
            printf("c%d %d\n", lb, a[x][y]);
            lnk(rb, a[x][y]), mdy(1, 1, n * m, lb, a[x][y], -1);
        }
        printf("%d %d\n", lb, rb);
        fst = M, snd = 0, ask(1, 1, n * m, lb, rb); if(fst == 1) ans += snd;
        printf("snd=%d\n", snd);
    }
    printf("%lld\n", ans);
    return 0;
}