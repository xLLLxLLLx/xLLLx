#include<stdio.h>
#include<algorithm>
#include<math.h>
#define go(i,a,b) for(int i=a;i<=b;i++)
#define ro(i,a,b) for(int i=a;i>=b;i--)
#define fo(i,a,x) for(int i=a[x],v=e[i].v;i;i=e[i].next,v=e[i].v)
using namespace std;const int N=50009;
struct E{int v,next;}e[N*3];
int k=1,head[N],unit,Be[N],m,st[N],top,fa[N][18],deep[N];
int n,Q,a[N],t[N],op,x,y,p,tim,u=1,v=1,T,ans[N],vis[N];
void ADD(int u,int v){e[k]=(E){v,head[u]};head[u]=k++;}
void dfs(int u){
    
    go(i,1,19)if((1<<i)>deep[u])break;
    else fa[u][i]=fa[fa[u][i-1]][i-1];
        
    int bottom=top;
    fo(i,head,u)if(v!=fa[u][0])
    {
        fa[v][0]=u;deep[v]=deep[u]+1;dfs(v);
        if(top-bottom>=unit){m++;while(top!=bottom)Be[st[top--]]=m;}
    }
    st[++top]=u;
}
int LCA(int x,int y)
{
    if(deep[x]<deep[y])swap(x,y);int Dis=deep[x]-deep[y];
    go(i,0,16)if((1<<i)&Dis)x=fa[x][i];
    if(x==y)return x;
    ro(i,16,0)if(fa[x][i]!=fa[y][i])x=fa[x][i],y=fa[y][i];
    return x==y?x:fa[x][0];
}
struct Change{int u,New,Old;}cq[N];
struct Query{int u,v,tim,id;bool operator <(const Query &a) const{
    return Be[u]==Be[a.u]?(Be[v]==Be[a.v]?tim<a.tim:Be[v]<Be[a.v]):Be[u]<Be[a.u];
}}q[N];
struct Datalock{
    struct _blo{int l,r;}b[350];
    int n,Be[N],m,unit,num[N],sum[350];
    void init()
    {
        unit=sqrt(n);m=(n-1)/unit+1;
        go(i,1,n)Be[i]=(i-1)/unit+1;
        go(i,1,m)b[i].l=(i-1)*unit+1,b[i].r=i*unit;
        b[m].r=n;
    }
    void Add(int v){if(v<=n)sum[Be[v]]+=(++num[v])==1;}
    void Del(int v){if(v<=n)sum[Be[v]]-=(--num[v])==0;}
    int mex()
    {
        go(i,1,m)if(sum[i]!=b[i].r-b[i].l+1)
        go(j,b[i].l,b[i].r)if(!num[j])return j;
        return -1;
    }
}Data;
void revise(int u,int d){if(vis[u])Data.Del(a[u]),Data.Add(d);a[u]=d;}
void Run(int u){if(vis[u])Data.Del(a[u]),vis[u]=0;else Data.Add(a[u]),vis[u]=1;}
void move(int x,int y)
{ 
    if(deep[x]<deep[y])swap(x,y);
    while(deep[x]>deep[y])Run(x),x=fa[x][0];
    while(x!=y)Run(x),Run(y),x=fa[x][0],y=fa[y][0];
}
void Mo()
{
    go(i,1,p)
    {
        while(T<q[i].tim)T++,revise(cq[T].u,cq[T].New);
        while(T>q[i].tim)revise(cq[T].u,cq[T].Old),T--;
        
        if(u!=q[i].u)move(u,q[i].u),u=q[i].u;
        if(v!=q[i].v)move(v,q[i].v),v=q[i].v;
        int anc=LCA(u,v);Run(anc);ans[q[i].id]=Data.mex()-1;Run(anc);
    }
}
int main(){scanf("%d%d",&n,&Q);unit=pow(n,0.45);
    go(i,1,n)scanf("%d",&a[i]),t[i]=++a[i];
    go(i,2,n){int uu,vv;scanf("%d%d",&uu,&vv);ADD(uu,vv);ADD(vv,uu);}
    dfs(1);while(top)Be[st[top--]]=m;
    go(i,1,n) printf("%d B:%d\n",i,Be[i]);
    go(i,1,Q)
    {
        scanf("%d%d%d",&op,&x,&y);
        if( op)p++,q[p]=(Query){x,y,tim,p};
        if(!op)tim++,cq[tim]=(Change){x,y+1,t[x]},t[x]=y+1;
    } 
    Data.n=n+1;Data.init();sort(q+1,q+1+p);Mo();
    go(i,1,p)printf("%d\n",ans[i]);
}//Paul_Guderian
