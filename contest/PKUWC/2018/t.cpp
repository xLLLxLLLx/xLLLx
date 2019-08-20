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
const int maxn = 400005,maxm = 100005,INF = 1000000000;
inline int read(){
    int out = 0,flag = 1; char c = getchar();
    while (c < 48 || c > 57){if (c == '-') flag = -1; c = getchar();}
    while (c >= 48 && c <= 57){out = (out << 3) + (out << 1) + c - 48; c = getchar();}
    return out * flag;
}
const int G = 3,P = 998244353;
inline int qpow(int a,LL b){
    int re = 1;
    for (; b; b >>= 1,a = 1ll * a * a % P)
        if (b & 1) re = 1ll * re * a % P;
    return re;
}
int R[maxn];
inline void NTT(int* a,int n,int f){
    for (int i = 0; i < n; i++) if (i < R[i]) swap(a[i],a[R[i]]);
    for (int i = 1; i < n; i <<= 1){
        int gn = qpow(G,(P - 1) / (i << 1));
        for (int j = 0; j < n; j += (i << 1)){
            int g = 1,x,y;
            for (int k = 0; k < i; k++,g = 1ll * g * gn % P){
                x = a[j + k],y = 1ll * g * a[j + k + i] % P;
                a[j + k] = (x + y) % P,a[j + k + i] = ((x - y) % P + P) % P;
            }
        }
    }
    if (f == 1) return;
    int nv = qpow(n,P - 2); reverse(a + 1,a + n);
    for (int i = 0; i < n; i++) a[i] = 1ll * a[i] * nv % P;
}
int A[30][maxn],deg[maxn],cnt;
int n,w[maxn];
void solve(int l,int r){
    if (l == r){
        ++cnt;
        deg[cnt] = w[l];
        A[cnt][0] = 1; A[cnt][w[l]] = -1;
        for (int i = 1; i < w[l]; i++) A[cnt][i] = 0;
        return;
    }
    int mid = l + r >> 1;
    solve(l,mid); solve(mid + 1,r);
    int n = 1,L = 0,a = cnt - 1,b = cnt,m = deg[a] + deg[b];
    while (n <= m) n <<= 1,L++;
    for (int i = 1; i < n; i++) R[i] = (R[i >> 1] >> 1) | ((i & 1) << (L - 1));
    for (int i = deg[a] + 1; i < n; i++) A[a][i] = 0;
    for (int i = deg[b] + 1; i < n; i++) A[b][i] = 0;
    NTT(A[a],n,1); NTT(A[b],n,1);
    for (int i = 0; i < n; i++) A[a][i] = 1ll * A[a][i] * A[b][i] % P;
    NTT(A[a],n,-1);
    cnt--; deg[cnt] = m;
}
int main(){
    n = read();
    if (n == 1){puts("1"); return 0;}
    int sum = 0,ans = 0;
    REP(i,n) w[i] = read(),sum += w[i]; sum -= w[1];
    solve(2,n);
    for(int i = 0; i <= sum; ++i)
        printf("%d ", A[1][i]);
    for (int i = 0; i <= sum; i++)
        ans = (ans + 1ll * w[1] * A[1][i] % P * qpow(i + w[1],P - 2) % P) % P;
    ans = (ans + P) % P;
    printf("%d\n",ans);
    return 0;
}