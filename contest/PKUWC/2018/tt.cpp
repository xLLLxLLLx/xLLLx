#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<map>
#define Redge(u) for (int k = h[u],to; k; k = ed[k].nxt)
#define REP(i,n) for (int i = 1; i <= (n); i++)
#define mp(a,b) make_pair<int,int>(a,b)
#define cls(s) memset(s,0,sizeof(s))
#define cp pair<int,int>
#define LL long long int
using namespace std;
const int maxn = 19,maxm = (1 << 19),INF = 1000000000,P = 998244353;
inline int read(){
    int out = 0,flag = 1; char c = getchar();
    while (c < 48 || c > 57){if (c == '-') flag = -1; c = getchar();}
    while (c >= 48 && c <= 57){out = (out << 3) + (out << 1) + c - 48; c = getchar();}
    return out * flag;
}
int h[maxn],ne = 1,de[maxn];
struct EDGE{int to,nxt;}ed[maxn << 1];
inline void build(int u,int v){
    ed[++ne] = (EDGE){v,h[u]}; h[u] = ne;
    ed[++ne] = (EDGE){u,h[v]}; h[v] = ne;
    de[u]++; de[v]++;
}
inline int qpow(int a,int b){
    int re = 1;
    for (; b; b >>= 1,a = 1ll * a * a % P)
        if (b & 1) re = 1ll * re * a % P;
    return re;
}
int in[maxn],f[maxn][maxm],nowS,n,Q,rt,maxv;
int A[maxn],B[maxn],fa[maxn];
void dfs(int u){
    if (de[u] == 1 && u != rt){
        if (in[u]){
            A[u] = 0;
            B[u] = (nowS ^ (1 << u - 1)) ? (f[fa[u]][nowS ^ (1 << u - 1)] + 1) % P : 0;
        }
        else A[u] = 1,B[u] = 1;
        return;
    }
    if (in[u]){
        A[u] = 0;
        if (!(nowS ^ (1 << u - 1))) B[u] = 0;
        else{
            B[u] = 0;
            int dv = qpow(de[u],P - 2),e = (nowS ^ (1 << u - 1));
            Redge(u) B[u] = (B[u] + 1ll * dv * (f[to = ed[k].to][e] + 1) % P) % P;
        }
        Redge(u) if ((to = ed[k].to) != fa[u]){
            fa[to] = u; dfs(to);
        }
        return;
    }
    int sa = 0,sb = 0;
    Redge(u) if ((to = ed[k].to) != fa[u]){
        fa[to] = u; dfs(to);
        sa = (sa + A[to]) % P;
        sb = (sb + B[to] + 1) % P;
    }
    int d = qpow(((de[u] - sa) % P + P) % P,P - 2);
    if (u == rt) A[u] = 0,B[u] = 1ll * sb * d % P;
    else A[u] = d,B[u] = 1ll * (sb + 1) % P * d % P;
}
void dfs2(int u){
    if (u == rt) f[u][nowS] = B[u];
    else f[u][nowS] = (1ll * A[u] * f[fa[u]][nowS] % P + B[u]) % P;
    Redge(u) if ((to = ed[k].to) != fa[u]) dfs2(to);
}
int main(){
    n = read(); Q = read(); rt = read(); maxv = (1 << n) - 1;
    for (int i = 1; i < n; i++) build(read(),read());
    REP(i,n) f[i][0] = 0;
    for (nowS = 1; nowS <= maxv; nowS++){
        REP(i,n) in[i] = ((nowS & (1 << i - 1)) > 0);
        dfs(rt); dfs2(rt);
    }
    while (Q--){
        int k = read(),S = 0;
        while (k--) S |= (1 << (read() - 1));
        printf("%d\n",f[rt][S]);
    }
    return 0;
}
