#include <bits/stdc++.h>
#define fi first
#define se second
#define pii pair<int,int>
#define mp make_pair
#define pb push_back
#define space putchar(' ')
#define enter putchar('\n')
#define eps 1e-10
#define MAXN 2005
#define ba 47
//#define ivorysi
using namespace std;
typedef long long int64;
typedef unsigned int u32;
typedef double db;
template<class T>
void read(T &res) {
    res = 0;T f = 1;char c = getchar();
    while(c < '0' || c > '9') {
    if(c == '-') f = -1;
    c = getchar();
    }
    while(c >= '0' && c <= '9') {
    res = res * 10 +c - '0';
    c = getchar();
    }
    res *= f;
}
template<class T>
void out(T x) {
    if(x < 0) {x = -x;putchar('-');}
    if(x >= 10) {
    out(x / 10);
    }
    putchar('0' + x % 10);
}
const int MOD = 998244353;
int M,N,nxt[MAXN],to[MAXN][26],mx[MAXN];
int dp[MAXN][MAXN];
char s[MAXN];
int inc(int a,int b) {
    return a + b >= MOD ? a + b - MOD : a + b;
}
int mul(int a,int b) {
    return 1LL * a * b % MOD;
}
void update(int &x,int y) {
    x = inc(x,y);
}
int fpow(int x,int c) {
    int res = 1,t = x;
    while(c) {
    if(c & 1) res = mul(res,t);
    t = mul(t,t);
    c >>= 1;
    }
    return res;
}
void Solve() {
    read(M);
    scanf("%s",s + 1);
    N = strlen(s + 1);
    for(int i = 2 ; i <= N ; ++i) {
    int p = nxt[i - 1];
    while(p && s[i] != s[p + 1]) p = nxt[p];
    if(s[i] == s[p + 1]) nxt[i] = p + 1;
    else nxt[i] = 0;
    }
    for(int i = 0 ; i <= N ; ++i) {
    mx[i] = mx[nxt[i]];
    if(i != N) mx[i] = max(mx[i],s[i + 1] - 'a');
    for(int j = 0 ; j < mx[i] ; ++j) to[i][j] = -1;
    for(int j = mx[i] ; j < 26 ; ++j) {
        if('a' + j == s[i + 1]) to[i][j] = i + 1;
        else {
        int p = nxt[i];
        while(to[p][j] == -1) p = nxt[p];
        to[i][j] = to[p][j];
        }
    }
    }
    int ans = 0;
    dp[0][0] = 1;
    for(int i = 0 ; i < M ; ++i) {
    for(int j = 0 ; j <= N ; ++j) {
        if(!dp[i][j]) continue;
        for(int h = mx[j] ; h < 26 ; ++h) {
        update(dp[i + 1][to[j][h]],dp[i][j]);
        }
    }
    }
    for(int i = 0 ; i <= N ; ++i) {
    int u = i;
    for(int j = 0 ; j < M ; ++j) {
        update(ans,mul(25 - mx[u],dp[M - j - 1][i]));
        u = to[u][mx[u]];
    }
    if(u == i) update(ans,1);
    }
    out(inc(fpow(26,M),MOD - ans));enter;

}

int main() {
#ifdef ivorysi
    freopen("f1.in","r",stdin);
#endif
    Solve();
    return 0;
}