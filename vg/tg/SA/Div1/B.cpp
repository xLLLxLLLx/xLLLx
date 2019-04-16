#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 400004
#define mid (l+r>>1)
using namespace std;
struct seg {
    int L[N*20],R[N*20],tot;
    void init() {
        tot=0;
        }
    void insert(int &now,int l,int r,int pos) {
        if(!now)now=++tot;
        if(l==r)return;
        if(pos<=mid)insert(L[now],l,mid,pos);
        else insert(R[now],mid+1,r,pos);
        }
    int merge(int A,int B) {
        if(!A||!B)return A+B;
        int it=++tot;
        L[it]=merge(L[A],L[B]);
        R[it]=merge(R[A],R[B]);
        return it;
        }
    int query(int now,int l,int r,int nl,int nr) {
        if(!now)return 0;
        if(nl<=l&&r<=nr)return 1;
        if(nl<=mid&&query(L[now],l,mid,nl,nr))return 1;
        if(mid<nr&&query(R[now],mid+1,r,nl,nr))return 1;
        return 0;
        }
    } aux;

int rt[N];

struct SAM {
    int cnt,las;
    int len[N],fa[N],ch[N][26],pos[N];
    void init() {
        cnt=las=1;
        }
    void add(int c,int pi) {
        int p=las,it=las=++cnt;
        len[it]=len[p]+1,pos[it]=pi;
        for(; p&&!ch[p][c]; p=fa[p])ch[p][c]=it;
        if(!p)fa[it]=1;
        else {
            int q=ch[p][c];
            if(len[q]==len[p]+1)fa[it]=q;
            else {
                int np=++cnt;
                for(int i=0; i<26; i++)ch[np][i]=ch[q][i];
                len[np]=len[p]+1,pos[np]=pos[q];
                fa[np]=fa[q],fa[q]=fa[it]=np;
                for(; p&&ch[p][c]==q; p=fa[p])ch[p][c]=np;
                }
            }
        }
    } sett;

void init() {
    sett.init(),aux.init();
    }

int n,tax[N],poi[N];
int dp[N],top[N];
char op[N];
int ans=1;

int main() {
    init();
    scanf("%d",&n);
    scanf("%s",op+1);
    for(int i=1; i<=n; i++) sett.add(op[i]-'a',i),aux.insert(rt[sett.las],1,n,i);
    for(int i=1; i<=sett.cnt; i++)tax[sett.len[i]]++;
    for(int i=1; i<=n; i++)tax[i]+=tax[i-1];
    for(int i=sett.cnt; i>=1; i--)poi[tax[sett.len[i]]--]=i;
    for(int i=sett.cnt; i>1; i--)
      rt[sett.fa[poi[i]]]=aux.merge(rt[sett.fa[poi[i]]],rt[poi[i]]);
    for(int i=2; i<=sett.cnt; i++) {
        int u=poi[i],ff=sett.fa[u];
        if(ff==1)dp[u]=1,top[u]=u;
        else {
            if(aux.query(rt[top[ff]],1,n,sett.pos[u]-sett.len[u]+sett.len[top[ff]],sett.pos[u]-1))
                dp[u]=dp[ff]+1,top[u]=u,ans=max(ans,dp[u]);
            else dp[u]=dp[ff],top[u]=top[ff];
            }
        }
    printf("%d\n",ans);
    }