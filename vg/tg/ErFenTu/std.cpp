#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
#define RG register
#define il inline
#define iter iterator
#define Max(a,b) ((a)>(b)?(a):(b))
#define Min(a,b) ((a)<(b)?(a):(b))
using namespace std;
const int N=2005,M=1000005;
int head[N],to[M<<1],nxt[M<<1],n,m,k,bel[N],num=0;bool vis[N],v[N];
void link(int x,int y){
    nxt[++num]=head[x];to[num]=y;head[x]=num;
}
int gi(){
    int str=0;char ch=getchar();
    while(ch>'9' || ch<'0')ch=getchar();
    while(ch>='0' && ch<='9')str=(str<<1)+(str<<3)+ch-48,ch=getchar();
    return str;
}
bool dfs(int x){
    int u;v[x]=true;
    for(int i=head[x];i;i=nxt[i]){
        u=to[i];if(vis[u])continue;
        vis[u]=true;
        if(!bel[u] || dfs(bel[u])){
            bel[u]=x;bel[x]=u;
            return true;
        }
    }
    return false;
}
void Clear(){
    memset(head,0,sizeof(head));num=0;
    memset(bel,0,sizeof(bel));
}
void work()
{
    Clear();
    int x,y;
    for(int i=1;i<=k;i++){
        x=gi();y=gi();
        link(x,y+n);link(y+n,x);
    }
    int ans=0;
    for(int i=1;i<=n+m;i++){
        if(!bel[i]){
            memset(vis,0,sizeof(vis));
            ans+=dfs(i);
        }
    }
    printf("%d",ans);
    memset(vis,0,sizeof(vis));
    memset(v,0,sizeof(v));
    for(int i=1;i<=n;i++)
        if(!bel[i])dfs(i);
    for(int i=1;i<=n;i++)
        if(!v[i])printf(" r%d",i);
    for(int i=1;i<=n;i++){
        if(vis[i+n])printf(" c%d",i);
    }
    puts("");
}

int main()
{
    while(~scanf("%d%d%d",&n,&m,&k)){
        if(n+m+k==0)break;
        work();
    }
    return 0;
}