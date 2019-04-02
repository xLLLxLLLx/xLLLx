#include <cstdio>

typedef long long LL;

const int N = 500005;

int n, m;
int L[N], R[N], P[N], hs[N];
LL Ans, A[N], sum[N], tag[N], va[N];

int yun, las[N], pre[N<<1], to[N<<1];
inline void Add(int a, int b) {
    to[++yun]=b; pre[yun]=las[a]; las[a]=yun;
}

inline int Isroot(int x) {
    return L[P[x]]!=x && R[P[x]]!=x;
}

inline int Order(int x) {
    return x==R[P[x]];
}

inline void Pushdown(int x) {
    if (!tag[x] || !x) return;
    sum[x]+=tag[x]; tag[L[x]]+=tag[x]; tag[R[x]]+=tag[x]; tag[x]=0;
}

inline void Pushall(int x) {
    if (!Isroot(x)) Pushall(P[x]); Pushdown(x);
}

inline void Rotate(int x) {
    int Fa=P[x], Gr=P[Fa], d=Order(x), so=d? L[x]:R[x];
    if (!Isroot(Fa)) (Order(Fa)? R[Gr]:L[Gr])=x; P[x]=Gr;
    (d? R[Fa]:L[Fa])=so; P[so]=Fa;
    (d? L[x]:R[x])=Fa; P[Fa]=x;
}

inline void Splay(int x) {
    Pushall(x);
    for (; !Isroot(x); Rotate(x))
        if (!Isroot(P[x])) Rotate(Order(P[x])==Order(x)? P[x]:x);
}

inline int Get_root(int x) {
    while (L[x]) Pushdown(x), x=L[x];
    Pushdown(x);
    return x;
}

inline void Recalc(int x) {
    Ans-=A[x];
    A[x]=(hs[x])? (2*(sum[x]-sum[hs[x]])):(sum[x]-1);
    if (va[x]*2>sum[x]+1) A[x]=2*(sum[x]-va[x]);
    Ans+=A[x];
}

inline void Access(int x, int y) {
    va[x]+=y;
    for (int t=0; x; t=x, x=P[x]) {
        Splay(x);
        sum[x]+=y; tag[L[x]]+=y; Pushdown(L[x]);
        if (hs[x]) {
            Pushall(hs[x]);
            if (sum[hs[x]]*2<=sum[x]+1) hs[x]=R[x]=0;
        }
        int son=Get_root(t);
        if (sum[son]*2>sum[x]+1) hs[x]=son, R[x]=t;
        Recalc(x);
    }
}

void Dfs_pre(int x, int Fa) {
    P[x]=Fa; sum[x]=va[x];
    for (int i=las[x]; i; i=pre[i]) if (to[i]!=Fa) {
        Dfs_pre(to[i], x);
        sum[x]+=sum[to[i]];
        if (sum[hs[x]]<sum[to[i]]) hs[x]=to[i];
    }
    if (sum[hs[x]]*2<=sum[x]+1) hs[x]=0;
    R[x]=hs[x];Recalc(x);
}

int main() {
    freopen("history2.in","r",stdin);
    scanf("%d%d", &n, &m);
    for (int i=1; i<=n; ++i) scanf("%lld", &va[i]);
    for (int i=1, x, y; i<n; ++i) scanf("%d%d", &x, &y), Add(x, y), Add(y, x);
    Dfs_pre(1, 0);
    printf("%lld\n", Ans);
    for (int x, y; m; --m) scanf("%d%d", &x, &y), Access(x, y), printf("%lld\n", Ans);
    
    return 0;
}