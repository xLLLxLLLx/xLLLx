#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<set>
#include<map>
#include<vector>
#include<queue>
using namespace std;
#define ll long long
#define RG register
#define MAX 444444
#define lson (now<<1)
#define rson (now<<1|1)
inline int read()
{
    RG int x=0,t=1;RG char ch=getchar();
    while((ch<'0'||ch>'9')&&ch!='-')ch=getchar();
    if(ch=='-')t=-1,ch=getchar();
    while(ch<='9'&&ch>='0')x=x*10+ch-48,ch=getchar();
    return x*t;
}
struct Line{int v,next;};
struct Link
{
    Line e[MAX<<1];
    int h[MAX],cnt;
    void Add(int u,int v)
    {
        e[++cnt]=(Line){v,h[u]};h[u]=cnt++;
        e[++cnt]=(Line){u,h[v]};h[v]=cnt++;
    }
}Gr,Tr;
multiset<int> MS[MAX];
int W[MAX];
int n,m,Q,Tot;
struct Graph
{
    int dfn[MAX],low[MAX],S[MAX],tim,top;
    void Tarjan(int u)
    {
        dfn[u]=low[u]=++tim;S[++top]=u;
        for(int i=Gr.h[u];i;i=Gr.e[i].next)
        {
            int v=Gr.e[i].v;
            if(!dfn[v])
            {
                Tarjan(v);low[u]=min(low[u],low[v]);
                if(low[v]>=dfn[u])
                {
                    Tr.Add(++Tot,u);int x;
                    do{x=S[top--];Tr.Add(Tot,x);}while(v!=x);
                }
            }
            else low[u]=min(low[u],dfn[v]);
        }
    }
}G;
struct SegMentTree
{
    int t[MAX<<2];
    void Modify(int now,int l,int r,int p,int w)
    {
        if(l==r){t[now]=w;return;}
        int mid=(l+r)>>1;
        if(p<=mid)Modify(lson,l,mid,p,w);
        else Modify(rson,mid+1,r,p,w);
        t[now]=min(t[lson],t[rson]);
    }
    int Query(int now,int l,int r,int L,int R)
    {
        if(L<=l&&r<=R)return t[now];
        int ret=1e9,mid=(l+r)>>1;
        if(L<=mid)ret=min(ret,Query(lson,l,mid,L,R));
        if(R>mid)ret=min(ret,Query(rson,mid+1,r,L,R));
        return ret;
    }
}SMT;
int fa[MAX],tim,dfn[MAX],low[MAX];
int size[MAX],hson[MAX],top[MAX],dep[MAX];
void dfs1(int u,int ff)
{
    fa[u]=ff;dep[u]=dep[ff]+1;size[u]=1;
    if(u<=n&&ff)MS[ff].insert(W[u]);
    for(int i=Tr.h[u];i;i=Tr.e[i].next)
    {
        int v=Tr.e[i].v;if(v==ff)continue;
        dfs1(v,u);size[u]+=size[v];
        if(size[v]>size[hson[u]])hson[u]=v;
    }
}
void dfs2(int u,int tp)
{
    top[u]=tp;dfn[u]=++tim;low[tim]=u;
    if(hson[u])dfs2(hson[u],tp);
    for(int i=Tr.h[u];i;i=Tr.e[i].next)
        if(Tr.e[i].v!=fa[u]&&Tr.e[i].v!=hson[u])
            dfs2(Tr.e[i].v,Tr.e[i].v);
}
int Query(int u,int v)
{
    int ret=1e9;
    while(top[u]^top[v])
    {
        if(dep[top[u]]<dep[top[v]])swap(u,v);
        ret=min(ret,SMT.Query(1,1,Tot,dfn[top[u]],dfn[u]));
        u=fa[top[u]];
    }
    if(dep[u]>dep[v])swap(u,v);
    ret=min(ret,SMT.Query(1,1,Tot,dfn[u],dfn[v]));
    if(u<=n)return ret;
    else return min(ret,W[fa[u]]);
}
void Modify(int u,int w)
{
    if(fa[u])
    {
        MS[fa[u]].erase(MS[fa[u]].find(W[u]));
        MS[fa[u]].insert(w);
        SMT.Modify(1,1,Tot,dfn[fa[u]],*MS[fa[u]].begin());
    }
    W[u]=w;SMT.Modify(1,1,Tot,dfn[u],w);
}
int main()
{
    Tot=n=read();m=read();Q=read();W[0]=1e9;
    for(int i=1;i<=n;++i)W[i]=read();
    for(int i=1;i<=m;++i)Gr.Add(read(),read());
    G.Tarjan(1);dfs1(1,0);dfs2(1,1);
    for(int i=1;i<=n;++i)SMT.Modify(1,1,Tot,dfn[i],W[i]);
    for(int i=n+1;i<=Tot;++i)SMT.Modify(1,1,Tot,dfn[i],*MS[i].begin());
    char ch[2];
    while(Q--)
    {
        scanf("%s",ch);
        int a=read(),b=read();
        if(ch[0]=='C')Modify(a,b);
        else printf("%d\n",Query(a,b));
    }
    return 0;
}