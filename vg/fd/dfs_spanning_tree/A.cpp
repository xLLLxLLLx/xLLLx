#include <cstdio>
#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;

const int MAXN = 2010;
const int MAXE = 20010;

int dep[MAXN];

struct Edge {
    int x, y, id;
    void read(int i) {
        id = i;
        scanf("%d%d", &x, &y);
    }
    void adjust() {
        if(dep[x] > dep[y]) swap(x, y);
    }
    bool operator < (const Edge &rhs) const {
        return dep[x] > dep[rhs.x];
    }
} e[MAXE];

int n, m;
int head[MAXN], fa[MAXN];
int to[MAXN * 2], next[MAXN * 2];
int ecnt;

void init() {
    memset(head, 0, sizeof(head));
    ecnt = 1;
}

void add_edge2(int u, int v) {
    to[ecnt] = v; next[ecnt] = head[u]; head[u] = ecnt++;
    to[ecnt] = u; next[ecnt] = head[v]; head[v] = ecnt++;
}

void bfs() {
    memset(dep, -1, sizeof(dep));
    queue<int> que; que.push(1);
    dep[1] = 0;
    while(!que.empty()) {
        int u = que.front(); que.pop();
        for(int p = head[u]; p; p = next[p]) {
            int &v = to[p];
            if(dep[v] == -1) {
                fa[v] = u;
                dep[v] = dep[u] + 1;
                que.push(v);
            }
        }
    }
}

bool vis[MAXN];

bool check(Edge &p) {
    int now = p.y;
    while(fa[now] != p.x) {
        if(vis[now]) break;
        now = fa[now];
    }
    if(!vis[now]) {
        vis[now] = true;
        return false;
    }
    else return true;
}

int main() {
    while(scanf("%d%d", &n, &m) != EOF) {
        if(n == 0 && m == 0) break;
        for(int i = 1; i <= m; ++i) e[i].read(i);
        init();
        for(int i = 1; i < n; ++i) add_edge2(e[i].x, e[i].y);
        bfs();
        for(int i = n; i <= m; ++i) e[i].adjust();
        sort(e + 1, e + m + 1);
        memset(vis, 0, sizeof(vis));
        int ans = 0;
        for(int i = 1; i <= m; ++i)
            if(e[i].id >= n && !check(e[i])) ++ans;
        printf("%d\n", ans);
    }
}
