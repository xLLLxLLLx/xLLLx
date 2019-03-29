#include <bits/stdc++.h>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>

using namespace std;

#pragma comment(linxer, "/STACK:102400000,102400000")
#define LL long long 
#define pii pair<int, int>
#define MP make_pair
#define ls i << 1
#define rs ls | 1
#define md (ll + rr >> 1)
#define lson ll, md, ls
#define rson md + 1, rr, rs
#define mod 1000000007
#define inf 0x3f3f3f3f
#define N 10010
#define M 20020

int fst[N], vv[M], nxt[M], cost[M], e;
int ch[N][2], pre[N], val[N], sum[N], sz[N];
bool rt[N];
int n;
void init(){
    memset(fst, -1, sizeof fst);
    for(int i = 0; i <= n; ++i)
        ch[i][0] = ch[i][1] = pre[i] = 0;
    memset(rt, 1, sizeof rt);
    e = 0;
}
void add(int u, int v, int c){
    vv[e] = v, nxt[e] = fst[u], cost[e] = c, fst[u] = e++;
}
void dfs(int u, int p){
    pre[u] = p;
    for(int i = fst[u]; ~i; i = nxt[i]){
        int v = vv[i], c = cost[i];
        if(v == p) continue;
        val[v] = sum[v] = c;
        sz[v] = 1;
        dfs(v, u);
    }
}
bool judge(int u, int v){
    while(pre[u]) u = pre[u];
    while(pre[v]) v = pre[v];
    return u == v;
}
void push_up(int x){
    sz[x] = sz[ch[x][0]] + sz[ch[x][1]] + 1;
    sum[x] = sum[ch[x][0]] + sum[ch[x][1]] + val[x];
}
void push_down(int x){
}
void P(int x){
    while(!rt[x])
        P(pre[x]);
    push_down(x);
}
void rot(int x){
    int y = pre[x], d = ch[y][1] == x;
    ch[y][d] = ch[x][!d];
    if(ch[x][!d]) pre[ch[x][!d]] = y;
    ch[x][!d] = y;
    pre[x] = pre[y];
    pre[y] = x;
    if(rt[y])
        rt[y] = 0, rt[x] = 1;
    else
        ch[pre[x]][ch[pre[x]][1] == y] = x;
    push_up(y);
}
void splay(int x){
    //P(x);
    while(!rt[x]){
        int f = pre[x], ff = pre[f];
        if(rt[f])
            rot(x);
        else if((ch[ff][1] == f) == (ch[f][1] == x))
            rot(f), rot(x);
        else rot(x), rot(x);
    }
    push_up(x);
}
int Access(int x){
    int y = 0;
    for(; x; y = x, x = pre[x]){
        splay(x);
        rt[ch[x][1]] = 1;
        ch[x][1] = y;
        rt[y] = 0;
        push_up(x);
    }
    return y;
}
void lca(int &u, int &v){
    Access(v), v = 0;
    for(splay(u); pre[u]; v = u, u = pre[u], splay(u)){
        rt[ch[u][1]] = 1;
        ch[u][1] = v;
        rt[v] = 0;
        push_up(u);
    }
}
int Kth(int x, int k){
    if(sz[ch[x][0]] >= k)
        return Kth(ch[x][0], k);
    else if(sz[ch[x][0]] + 1 == k)
        return x;
    else return Kth(ch[x][1], k - sz[ch[x][0]] - 1);
}
int _Kth(int x, int k){
    if(sz[ch[x][1]] >= k)
        return _Kth(ch[x][1], k);
    else if(sz[ch[x][1]] + 1 == k)
        return x;
    else return _Kth(ch[x][0], k - sz[ch[x][1]] - 1);
}
int main(){
  //freopen("out","r",stdin);
    int cas;
    scanf("%d", &cas);
    while(cas--){
        scanf("%d", &n);
        init();
        for(int i = 1; i < n; ++i){
            int u, v, c;
            scanf("%d%d%d", &u, &v, &c);
            add(u, v, c);
            add(v, u, c);
        }
        dfs(1, 0);
        char s[20];
        while(1){
            scanf("%s", s);
            if(s[1] == 'O') break;
            if(s[0] == 'D'){
                int u, v;
                scanf("%d%d", &u, &v);
                lca(u, v);
                printf("%d\n", sum[v] + sum[ch[u][1]]);
            }
            else if(s[0] == 'K'){
                int u, v, k;
                scanf("%d%d%d", &u, &v, &k);
                lca(u, v);
                if(sz[v] >= k)
                    printf("%d\n", _Kth(v, k));
                else if(sz[v] + 1 == k)
                    printf("%d\n", u);
                else
                    printf("%d\n", Kth(ch[u][1], k - sz[v] - 1));
            }   
        }
    }
    return 0;
}
