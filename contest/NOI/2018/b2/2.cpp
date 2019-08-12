#include <bits/stdc++.h>
using namespace std;

template <typename T>
void chmax(T &x, const T &y) {
    if (x < y)
        x = y;
}
const int ch_top = 1e8;
char ch[ch_top], *now_r = ch - 1;
#define c (*now_r)
#define gc (*++now_r)
template <typename T>
void read(T &x) {
    while (gc < '0')
        ;
    x = c - '0';
    while (gc >= '0') x = x * 10 + c - '0';
}
#undef gc
#undef c

typedef long long s64;
#define rep(i, l, r) for (int i = l; i <= r; ++i)
#define per(i, r, l) for (int i = r; i >= l; --i)
struct Edge {
    int to, w;
};
struct Query {
    int x, y;
    s64 v;
};
const int N = 5e4 + 5, M = 1e5 + 5;
const s64 inf = 1e18;
int n, m;
s64 ans;
int fa[N], to_fa[N], sz[N], son[N], top[N], dfn[N], tot;
s64 deep[N];
vector<int> lk[N];

#define fx top[x]
#define fy top[y]
int get_lca(int x, int y) {
    while (fx != fy)
        if (fx > fy)
            x = fa[fx];
        else
            y = fa[fy];
    return x < y ? x : y;
}
#undef fx
#undef fy
void dfs(int x) {
    dfn[x] = ++tot;
    sz[x] = 1;
    son[x] = 0;
    for (auto y : lk[x]) {
        deep[y] = deep[x] + to_fa[y];
        dfs(y);
        sz[x] += sz[y];
        if (sz[y] > sz[son[x]])
            son[x] = y;
    }
}
Query query[M];
namespace S1 {
const int T = M * 20;
int c[T][2];
s64 mx[T][2];
int tot;
#define mid (l + r) / 2
void add(int x, int i, s64 v0, s64 v1) {
    int k = x;
    chmax(mx[k][0], v0);
    chmax(mx[k][1], v1);
    int l = 1, r = n;
    while (l != r)
        if (i <= mid) {
            chmax(ans, v0 + mx[c[k][1]][1] - deep[x]);
            r = mid;
            if (c[k][0]) {
                k = c[k][0];
                chmax(mx[k][0], v0);
                chmax(mx[k][1], v1);
            } else {
                k = (c[k][0] = ++tot);
                mx[k][0] = v0;
                mx[k][1] = v1;
            }
        } else {
            chmax(ans, v1 + mx[c[k][0]][0] - deep[x]);
            l = mid + 1;
            if (c[k][1]) {
                k = c[k][1];
                chmax(mx[k][0], v0);
                chmax(mx[k][1], v1);
            } else {
                k = (c[k][1] = ++tot);
                mx[k][0] = v0;
                mx[k][1] = v1;
            }
        }
}
void del(int k, int x, int l, int r) {
    if (l == r) {
        mx[k][0] = mx[k][1] = -2 * inf;
        return;
    }
    if (x <= mid)
        del(c[k][0], x, l, mid);
    else
        del(c[k][1], x, mid + 1, r);
    rep(i, 0, 1) mx[k][i] = max(mx[c[k][0]][i], mx[c[k][1]][i]);
}
int now;
void merge(int &x, int y) {
    if (!y)
        return;
    if (!x) {
        x = y;
        return;
    }
    chmax(ans, max(mx[c[x][0]][0] + mx[c[y][1]][1], mx[c[y][0]][0] + mx[c[x][1]][1]) - deep[now]);
    rep(i, 0, 1) chmax(mx[x][i], mx[y][i]);
    merge(c[x][0], c[y][0]);
    merge(c[x][1], c[y][1]);
}
#undef mid
void work() {
    rep(i, 0, 1) mx[0][i] = -inf * 2;
    for (; tot; --tot) rep(i, 0, 1) c[tot][i] = 0;
    tot = n;
    rep(i, 1, m) {
        int x = query[i].x, y = query[i].y, lca = get_lca(x, y);
        s64 v = deep[x] + deep[y] - 2 * deep[lca] - query[i].v, v1 = v + deep[lca];
        if (x != lca)
            add(x, lca, v, v1);
        if (y != lca)
            add(y, lca, v, v1);
    }
    per(x, n, 2) {
        now = fa[x];
        del(x, fa[x], 1, n);
        merge(fa[x], x);
    }
}
};  // namespace S1
namespace S2 {
struct Pr {
    int x;
    s64 v;
};
s64 dis(const Pr &a, const Pr &b) {
    if (!a.x || !b.x)
        return -2 * inf;
    return a.v + b.v - deep[get_lca(a.x, b.x)];
}
vector<int> lkq[N];
Pr mx[N][2];
pair<int, Pr> q[M * 2];
int tail;
int st[N], top;
void merge(int x, int y) {
    if (x == st[1])
        return;
    Pr a0 = mx[x][0], a1 = mx[x][1];
    s64 ad = dis(a0, a1);
    rep(i, 0, 1) rep(j, 0, 1) {
        s64 now;
        chmax(ans, (now = dis(mx[x][i], mx[y][j])) - deep[x] - 2 * deep[st[1]]);
        if (now > ad) {
            a0 = mx[x][i];
            a1 = mx[y][j];
            ad = now;
        }
    }
    if (dis(mx[y][0], mx[y][1]) > ad) {
        rep(i, 0, 1) mx[x][i] = mx[y][i];
    } else {
        mx[x][0] = a0;
        mx[x][1] = a1;
    }
}
void work() {
    rep(i, 1, n) lkq[i].clear();
    rep(i, 1, m) lkq[get_lca(query[i].x, query[i].y)].push_back(i);
    rep(lca, 1, n) {
        tail = 0;
        for (auto i : lkq[lca]) {
            int x = query[i].x, y = query[i].y;
            s64 v = deep[x] + deep[y] - query[i].v;
            q[++tail] = pair<int, Pr>(x, (Pr){ y, v });
            q[++tail] = pair<int, Pr>(y, (Pr){ x, v });
        }
        sort(q + 1, q + tail + 1,
             [&](const pair<int, Pr> &a, const pair<int, Pr> &b) { return dfn[a.first] < dfn[b.first]; });
        st[top = 1] = lca;
        rep(head, 1, tail) {
            int x = q[head].first;
            if (x == st[top]) {
                mx[0][0] = q[head].second;
                merge(st[top], 0);
                continue;
            }
            int lca = get_lca(x, st[top]);
            while (top > 1 && dfn[st[top - 1]] >= dfn[lca]) {
                merge(st[top - 1], st[top]);
                --top;
            }
            if (st[top] != lca) {
                rep(i, 0, 1) mx[lca][i] = mx[st[top]][i];
                st[top] = lca;
            }
            st[++top] = x;
            mx[x][0] = q[head].second;
            mx[x][1].x = 0;
        }
        while (top > 1) {
            merge(st[top - 1], st[top]);
            --top;
        }
    }
}
};  // namespace S2

int main() {
    freopen("center.in", "r", stdin);
    freopen("center.out", "w", stdout);
    ch[fread(ch, 1, ch_top, stdin)] = 0;
    int tt;
    read(tt);
    while (tt--) {
        read(n);
        rep(i, 1, n) lk[i].clear();
        rep(i, 1, n - 1) {
            int x, y;
            read(x);
            read(y);
            read(to_fa[y]);
            fa[y] = x;
            lk[x].push_back(y);
        }
        tot = 0;
        dfs(1);
        rep(x, 1, n) if (x != son[fa[x]]) for (int y = x; y; y = son[y]) top[y] = x;
        ans = -inf;
        read(m);
        rep(i, 1, m) {
            read(query[i].x);
            read(query[i].y);
            read(query[i].v);
        }
        S1::work();
        S2::work();
        if (ans == -inf)
            puts("F");
        else
            printf("%lld\n", ans);
    }
}