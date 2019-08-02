#include <bits/stdc++.h>
#define pa pair<int, int>
#define CLR(a, x) memset(a, x, sizeof(a))
#define MP make_pair
#define fi first
#define se second
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int ui;
typedef long double ld;
const int maxn = 4010, maxm = 4e6 + 10, inf = (1u << 31) - 1;

struct Edge {
    int b, l, c, ne;
} eg[maxm * 2];
int N, M, egh[maxn], ect = 1, S, T;
int dis[maxn], off;
bool flag[maxn];

inline void adeg(int a, int b, int c, int l) { 
    eg[++ect] = Edge{ b, l, c, egh[a] }, egh[a] = ect; 
}

inline void add(int a, int b, int c, int l) {
    adeg(a, b, c, l);
    adeg(a, b, 0, -l);
}

inline bool spfa() {
    static queue<int> q;
    for (int i = 1; i <= N; i++) dis[i] = inf, flag[i] = 0;
    q.push(S);
    dis[S] = 0;
    while (!q.empty()) {
        int p = q.front();
        q.pop();
        flag[p] = 0;
        for (int i = egh[p]; i; i = eg[i].ne) {
            int b = eg[i].b;
            if (!eg[i].l || dis[b] <= dis[p] + eg[i].c)
                continue;
            dis[b] = dis[p] + eg[i].c;
            if (!flag[b])
                q.push(b), flag[b] = 1;
        }
    }
    for (int i = 2; i <= ect; i++) {
        eg[i].c += dis[eg[i ^ 1].b] - dis[eg[i].b];
    }
    off += dis[T] - dis[S];
    return dis[T] < inf;
}

inline bool dijk() {
    static priority_queue<pa, vector<pa>, greater<pa> > q;
    for (int i = 0; i <= N; i++) dis[i] = inf, flag[i] = 0;
    q.push(MP(0, S)), dis[S] = 0;
    while (!q.empty()) {
        int p = q.top().se;
        q.pop();
        if (flag[p])
            continue;
        flag[p] = 1;
        for (int i = egh[p]; i; i = eg[i].ne) {
            int b = eg[i].b;
            if (!eg[i].l || dis[b] <= dis[p] + eg[i].c)
                continue;
            dis[b] = dis[p] + eg[i].c;
            q.push(MP(dis[b], b));
        }
    }
    for (int i = 2; i <= ect; i++) {
        eg[i].c += dis[eg[i ^ 1].b] - dis[eg[i].b];
    }
    off += dis[T] - dis[S];
    return dis[T] < inf;
}

int dinic(int x, int y) {
    if (x == S)
        return y;
    int tmp = y;
    flag[x] = 1;
    for (int i = egh[x]; i; i = eg[i].ne) {
        int b = eg[i].b;
        if (flag[b] || !eg[i ^ 1].l || eg[i ^ 1].c)
            continue;
        int r = dinic(b, min(tmp, eg[i ^ 1].l));
        tmp -= r, eg[i ^ 1].l -= r, eg[i].l += r;
        if (!tmp)
            break;
    }
    return y - tmp;
}

int x[2010];

int main() {
    int cas;scanf("%d", &cas);
    for(int o = 1; o <= cas; ++o) {
        ect = 1;
        int m, k;
        scanf("%d%d", &m, &k);
        for(int i = 1; i <= m; ++i) {
            scanf("%d", &x[i]);
        }
        S = 0, T = m * 2 + 3;
        N = m * 2 + 3；
        add(S, 1, k, 0);
        for (int i=1;i<=m;i++)
        {
            add(1,i<<1,1,0);
            add(i<<1,(i<<1)+1,1,x[i]);
            add((i<<1)+1,T,1,0);
            for (int j=1;j<i;j++)
                if (x[j]<=x[i])
                    add((j<<1)+1,i<<1,1,0);
        }
        int flw = 0, cst = 0;
        spfa();
        while (dijk()) {
            int a = -1;
            while (a) {
                CLR(flag, 0);
                a = dinic(T, inf);
                flw += a, cst += a * off;
            }
        }
        printf("%d\n", cst);
    }
    return 0;
}