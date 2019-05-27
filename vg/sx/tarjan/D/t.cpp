#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#define inf 0x7fffffff
#define ll long long
using namespace std;
inline ll read()
{
    ll x=0,f=1;char ch=getchar();
    while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int n,m,S,p,tim,scc,top,cnt,ans;
int head[500005],h[500005],f[500005];
int belong[500005],v[500005];
int c[500005],dfn[500005],low[500005],q[500005];
bool inq[500005];
struct data{int to,next;}e[500005];
struct edge{int to,next;}ed[500005];
void insert(int u,int v)
{e[++cnt].to=v;e[cnt].next=head[u];head[u]=cnt;}
void ins(int u,int v)
{ed[++cnt].to=v;ed[cnt].next=h[u];h[u]=cnt;}
void tarjan(int x)
{
    int now=0;
    dfn[x]=low[x]=++tim;
    q[++top]=x;inq[x]=1;
    for(int i=head[x];i;i=e[i].next)
        if(!dfn[e[i].to]){tarjan(e[i].to);low[x]=min(low[x],low[e[i].to]);}
        else if(inq[e[i].to])low[x]=min(low[x],dfn[e[i].to]);
    if(low[x]==dfn[x])
    {
        scc++;
        while(now!=x)
        {
            now=q[top];top--;
            belong[now]=scc; 
            v[scc]+=c[now];
            inq[now]=0;
        }
    }
}
void rebuild()
{
     cnt=0;
     for(int i=1;i<=n;i++)
         for(int j=head[i];j;j=e[j].next)
             if(belong[i]!=belong[e[j].to])
                 ins(belong[i],belong[e[j].to]);
}
void spfa()
{
    int t=0,w=1;
    q[t]=belong[S];inq[belong[S]]=1;
    f[belong[S]]=v[belong[S]];
    while(t!=w)
    {
        int now=q[t];t++;if(t==500000)t=0;
        for(int i=h[now];i;i=ed[i].next)
        {
            if(f[now]+v[ed[i].to]>f[ed[i].to])
            {
                f[ed[i].to]=f[now]+v[ed[i].to];
                if(!inq[ed[i].to])
                {inq[ed[i].to]=1;q[w++]=ed[i].to;if(w==500000)w=0;}
            }
        }
        inq[now]=0;
    }
}
int main()
{
    n=read();m=read();
    for(int i=1;i<=m;i++)
    {
        int u=read(),v=read();
        insert(u,v);
    }
    for(int i=1;i<=n;i++)
        c[i]=read();
    for(int i=1;i<=n;i++)if(!dfn[i])tarjan(i);
    S=read();p=read();
    rebuild();
    spfa();
    for(int i=1;i<=p;i++)
    {
        int x=read();
        if(f[belong[x]]>ans)ans=f[belong[x]];
    }
    printf("%d",ans);
    return 0;
}