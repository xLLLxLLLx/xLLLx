#include<cstdio>
#include<iostream>
#include<algorithm>
#define inf 1000000000
#define ll long long 
using namespace std;
int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int top,q[200005];
int n,m,ans=inf;
int mx[200005],val[200005];
int p[200005],fa[200005],c[200005][2];
bool rev[200005];
struct data{
    int u,v,a,b;       
}e[100005];
int find(int x)
{
    return x==p[x]?x:p[x]=find(p[x]);
}
bool operator<(data a,data b)
{
    return a.a<b.a;
}
bool isroot(int x)
{
     return c[fa[x]][0]!=x&&c[fa[x]][1]!=x;
}
void update(int x)
{
    int l=c[x][0],r=c[x][1];
    mx[x]=x;
    if(val[mx[l]]>val[mx[x]])mx[x]=mx[l];
    if(val[mx[r]]>val[mx[x]])mx[x]=mx[r];
}
void pushdown(int x)
{
     int l=c[x][0],r=c[x][1];
     if(rev[x])
     {
         rev[x]^=1;rev[l]^=1;rev[r]^=1;
         swap(c[x][0],c[x][1]);
     }
}
void rotate(int x)
{
     int y=fa[x],z=fa[y],l,r;
     if(c[y][0]==x)l=0;else l=1;r=l^1;
     if(!isroot(y))
     {
         if(c[z][0]==y)c[z][0]=x;
         else c[z][1]=x;
     }
     fa[x]=z;fa[y]=x;fa[c[x][r]]=y;
     c[y][l]=c[x][r];c[x][r]=y;
     update(y);update(x);
}
void splay(int x)
{
     top=0;q[++top]=x;
     for(int i=x;!isroot(i);i=fa[i])q[++top]=fa[i];
     while(top)pushdown(q[top--]);
     while(!isroot(x))
     {
         int y=fa[x],z=fa[y];
         if(!isroot(y))
         {
             if(c[y][0]==x^c[z][0]==y)rotate(x);
             else rotate(y);
         }
         rotate(x);
     }
}
void access(int x)
{
		int pos=x;
		puts("----");
		while(fa[pos]) printf("%d\n",pos),pos=fa[pos];
		puts("----");
    for(int t=0;x;t=x,x=fa[x])
        splay(x),c[x][1]=t,update(x);
}
void makeroot(int x)
{
     access(x);splay(x);rev[x]^=1;
}
void link(int x,int y)
{
    makeroot(x);fa[x]=y;
}
void cut(int x,int y)
{
    makeroot(x);access(y);splay(y);
    c[y][0]=fa[x]=0;update(y);
}
int query(int x,int y)
{
    makeroot(x);access(y);splay(y);
    return mx[y]; 
}
int main()
{
    n=read();m=read();
    for(int i=1;i<=n;i++)p[i]=i;
    for(int i=1;i<=m;i++)
    {
        e[i].u=read();e[i].v=read();e[i].a=read();e[i].b=read();
    }
    sort(e+1,e+m+1);
    int tot=0;
    for(int i=1;i<=m;i++)
    {
        int u=e[i].u,v=e[i].v,a=e[i].a,b=e[i].b;
        if(find(u)==find(v))
        {
             int t=query(u,v);
             if(val[t]>e[i].b)
             {
                 cut(t,e[t-n].u);
                 cut(t,e[t-n].v);
             }
             else continue;
        }
        else p[find(u)]=find(v);
        val[n+i]=e[i].b;mx[n+i]=n+i;
        link(u,n+i);link(v,n+i);
        if(find(1)==find(n))ans=min(ans,e[i].a+val[query(1,n)]);
    }
    if(ans==inf)puts("-1");
    else printf("%d\n",ans);
    return 0;
}
