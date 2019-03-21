#include <bits/stdc++.h>
#define fr(i, x, y) for (int i = x; i <= y; ++i)
#define rf(i, x, y) for (int i = x; i >= y; --i)
#define lson (x << 1)
#define rson (x << 1 | 1)
#define LL long long
using namespace std;
const int N = 5e5 + 10, mod = 1e9 + 7;
struct data {
    int fr, to, nt;
} g[N * 100], p[N * 100];
int idx, tot, zz = 0, cnt = 0, res = 0, top = 0, nw = 0, maxn = 0;
int head[N * 20], dfn[N * 20], low[N * 20], dp[N * 20], d[N * 20], nm[N * 20], stk[N * 20], vis[N * 20],
    col[N * 20];
LL s[N], ri[N], all[N * 3];

void Add(LL &x, LL y) { x = (x + y) % mod; }

LL mul(LL x, LL y) { return x * y % mod; }

void add(int x, int y) {
    // printf("%d %d\n",x,y);
    g[++cnt].fr = x, g[cnt].to = y, g[cnt].nt = head[x], head[x] = cnt;
}

void build(int x, int l, int r) {
    maxn = max(maxn, x + idx);
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    build(lson, l, mid), build(rson, mid + 1, r);
    add(x + idx, lson + idx), add(x + idx, rson + idx);
}

int find(LL x) { return lower_bound(all + 1, all + 1 + tot, x) - all; }

void go(int x, int l, int r, int L, int gg) {
    if (l == r) {
        add(x + idx, gg);
        return;
    }
    int mid = (l + r) >> 1;
    if (L <= mid)
        go(lson, l, mid, L, gg);
    else
        go(rson, mid + 1, r, L, gg);
}

void og(int x, int l, int r, int L, int R, int gg) {
    if (L <= l && r <= R) {
        add(gg, idx + x);
        return;
    }
    int mid = (l + r) >> 1;
    if (L <= mid)
        og(lson, l, mid, L, R, gg);
    if (R > mid)
        og(rson, mid + 1, r, L, R, gg);
}

void dfs(int u) {
    dfn[u] = low[u] = ++res;
    vis[u] = 1, stk[++top] = u;
    for (int i = head[u]; i; i = g[i].nt) {
        int to = g[i].to;
        if (!dfn[to])
            dfs(to), low[u] = min(low[u], low[to]);
        else if (vis[to])
            low[u] = min(low[u], low[to]);
    }
    if (dfn[u] == low[u]) {
        col[u] = ++nw, vis[u] = 0;
        while (stk[top] != u) {
            vis[stk[top]] = 0, col[stk[top--]] = nw;
        }
        top--;
    }
}

queue<int> q;

void Get() {
    fr(i, 1, nw) if (!d[i]) q.push(i), vis[i] = 1;
    while (!q.empty()) {
        int h = q.front();
        q.pop();
        vis[h] = 0;
        // printf("just??\n");
        for (int i = head[h]; i; i = p[i].nt) {
            int to = p[i].to;
            // printf("%d %d\n",h,to);
            dp[to] += dp[h];
            if (!vis[to])
                q.push(to), vis[to] = 1;
        }
    }
}

void print(int x, int l, int r) {
    // printf("x=%d l=%d r=%d col=%d\n",x,l,r,col[x]);
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    print(lson, l, mid), print(rson, mid + 1, r);
}

int main() {
    // freopen("in","r",stdin);
    int n;
    scanf("%d", &n);
    int dd = 0;
    idx = n;
    fr(i, 1, n) {
        scanf("%lld%lld", &s[i], &ri[i]);
        all[++dd] = s[i];
        all[++dd] = s[i] - ri[i], all[++dd] = s[i] + ri[i];
    }
    sort(all + 1, all + 1 + dd);
    tot = unique(all + 1, all + 1 + dd) - all - 1;
    build(1, 1, tot);
    // printf("tot=%d\n",tot);
    fr(i, 1, n) {
        int x = find(s[i]);
        go(1, 1, tot, x, i);
        int l = find(s[i] - ri[i]), r = find(s[i] + ri[i]);
        // printf("l=%d r=%d\n",l,r);
        og(1, 1, tot, l, r, i);
    }
    fr(i, 1, maxn) if (!dfn[i]) dfs(i);
    fr(i, 1, n) nm[col[i]]++;
    fr(i, 1, nw) dp[i] = nm[i];
    // fr(i,1,n) printf("%d col=%d\n",i,col[i]);
    memset(head, 0, sizeof head);
    memset(vis, 0, sizeof vis);
    fr(i, 1, cnt) {
        int pos = col[g[i].to], tmp = col[g[i].fr];
        // printf("pos=%d tmp=%d\n",pos,tmp);
        if (pos == tmp)
            continue;
        d[tmp]++;
        p[++zz] = (data){ pos, tmp, head[pos] }, head[pos] = zz;
    }
    Get();
    LL ans = 0;
    fr(i, 1, n) {
        // printf("%d nn%d\n",i,dp[col[i]]);
        Add(ans, mul(i, dp[col[i]]));
    }
    printf("%lld\n", ans);
    return 0;
}
