/*
 * Author: RainAir
 * Time: 2019-09-14 15:43:27
 */
#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <numeric>
#include <cstdio>
#include <bitset>
#include <vector>
#include <cmath>
#include <ctime>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define fi first
#define se second
#define U unsigned
#define P std::pair<int,int>
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 2e5 + 5;
const int ha = 1e9 + 7;
#define TYPE1 (19260817)
#define TYPE2 (19491001)

struct Edge{
    int to,w,nxt;
}e[MAXN<<2];
int head[MAXN],du[MAXN],cnt;

inline void add(int u,int v,int w){
    du[u]++;du[v]++;
    e[++cnt] = (Edge){v,w,head[u]};head[u] = cnt;
    e[++cnt] = (Edge){u,w,head[v]};head[v] = cnt;
}

int len = 0;
bool vis[MAXN];

inline void dfs(int v){
    len++;vis[v] = true;
    for(int i = head[v];i;i = e[i].nxt){
        if(vis[e[i].to]) continue;
        dfs(e[i].to);
    }
}

inline bool cmp(int a,int b){
    return du[a] == du[b] ? a < b : du[a] < du[b];
}

int n,m1,m2;
int p[MAXN];
int circle[MAXN],chain[MAXN][2],fac[MAXN],pw2[MAXN];

inline int qpow(int a,int n){
    int res = 1;
    while(n){
        if(n & 1) res = 1ll*res*a%ha;
        a = 1ll*a*a%ha;
        n >>= 1;
    }
    return res;
}

P a[MAXN];

int main(){
    scanf("%*d%d%d%d",&n,&m1,&m2);
    pw2[0] = fac[0] = 1;
    FOR(i,1,n) pw2[i] = 2ll*pw2[i-1]%ha,fac[i] = 1ll*fac[i-1]*i%ha;
    FOR(i,1,m1){
        int u,v;scanf("%d%d",&u,&v);
        add(u,v,TYPE1);
    }
    FOR(i,1,m2){
        int u,v;scanf("%d%d",&u,&v);
        add(u,v,TYPE2);
    }
    std::iota(p+1,p+n+1,1);
    std::sort(p+1,p+n+1,cmp);
    FOR(i,1,n){
        printf("%d\n", p[i]);
        if(vis[p[i]]) continue;len = 0;
        dfs(p[i]);
        du[p[i]] == 2 ? circle[len]++ : chain[len][e[head[p[i]]].w == TYPE1]++;
    }
    int ans = 1;
    FOR(i,1,n){
        printf("%d %d %d\n", circle[i], chain[i][0], chain[i][1]);
        if(i > 1) ans = 1ll*ans*qpow(i,circle[i])%ha*fac[circle[i]]%ha;
        if(i & 1) ans = 1ll*ans*fac[chain[i][0]+chain[i][1]]%ha;
        else ans = 1ll*ans*pw2[chain[i][0]]%ha*fac[chain[i][0]]%ha*pw2[chain[i][1]]%ha*fac[chain[i][1]]%ha;
    }
    printf("%d\n",(fac[n]+ha-ans)%ha);
    return 0;
}