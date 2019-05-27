#include<iostream>
#include<cstdio>
#include<cstring>

using namespace std;

const int N=110;

int dfn[N],low[N],head[N],vis[N];
bool cut[N];
int k,n,cnt,root;

struct Edge{
    int to,nxt;
}edge[N<<1];

void addedge(int cu,int cv){
    edge[cnt].to=cv;
    edge[cnt].nxt=head[cu];
    head[cu]=cnt++;
}

void Tarjan(int u,int fa){
    int son=0;
    vis[u]=1;
    dfn[u]=low[u]=++k;
    for(int i=head[u];i!=-1;i=edge[i].nxt){
        int v=edge[i].to;
        if(vis[v]==1 && v!=fa)
            low[u]=min(low[u],dfn[v]);
        if(vis[v]==0){
            Tarjan(v,u);
            son++;
            low[u]=min(low[u],low[v]);
            if((u==root && son>1) || (u!=root && dfn[u]<=low[v]))
                cut[u]=1;
        }
    }
    vis[u]=2;
}

int main(){
    while(~scanf("%d",&n) && n){
        memset(head,-1,sizeof(head));
        memset(dfn,0,sizeof(dfn));
        memset(low,0,sizeof(low));
        memset(vis,0,sizeof(vis));
        memset(cut,0,sizeof(cut));
        cnt=0;
        int u,v;
        while(scanf("%d",&u) && u){
            while(getchar()!='\n'){
                scanf("%d",&v);
                addedge(u,v);
                addedge(v,u);
            }
        }
        root=1;
        Tarjan(root,-1);
        int ans=0;
        for(int i=1;i<=n;i++)
            if(cut[i])
                ans++;
        printf("%d\n",ans);
    }
    return 0;
}