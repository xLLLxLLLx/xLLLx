#include <bitset>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;
#define pb(a) push_back(a);
#define maxn 2100
vector<int>g[maxn],tree[maxn];
bitset<2100> to[2100];
int n,m,ans,vis[maxn];
void dfs(int now,int last)
{
    vis[now]=1;
    int v;
    to[now].reset();
    for(int i=0;i<g[now].size();i++)
    {
        v=g[now][i];
        if(vis[v])
        {
            to[now].set(v);
        }
    }
    for(int i=0;i<tree[now].size();i++)
    {
        v=tree[now][i];
        if(v!=last)
        {
            dfs(v,now);
        }
    }
    if(last==-1)
    {
        return ;
    }
    if(to[now].test(last))
    {
        ans++;
    }
    else
    {
        to[last]|=to[now];
    }
}
int main()
{
    int u,v;
    while(scanf("%d%d",&n,&m))
    {
        ans=0;
        memset(vis,0,sizeof(vis));
        if(n+m==0)
        {
            break;
        }
        for(int i=1;i<=n;i++)
        {
            tree[i].clear();
            g[i].clear();
        }
        for(int i=1;i<n;i++)
        {
            scanf("%d%d",&u,&v);
            tree[u].pb(v);
            tree[v].pb(u);
        }
        for(int i=n;i<=m;i++)
        {
            scanf("%d%d",&u,&v);
            g[u].pb(v);
            g[v].pb(u);
        }
        dfs(1,-1);
        printf("%d\n",ans);
    }
    return 0;
}

