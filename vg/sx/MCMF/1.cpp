#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
struct Edge{
    int x,y,c,nxt,cap;
    Edge(){}
    Edge(int a,int b,int _c,int d,int e){
        x=a,y=b,c=_c,cap=d,nxt=e;
    }
};
struct Network{
    static const int N=405,M=15005*2,INF=0x7FFFFFFF;
    Edge e[M];
    int n,S,T,fst[N],cur[N],cnt;
    int q[N],vis[N],head,tail;
    int MaxFlow,MinCost,dis[N];
    void clear(int _n){
        n=_n,cnt=1;
        memset(fst,0,sizeof fst);
    }
    void add(int a,int b,int c,int d){
        e[++cnt]=Edge(a,b,d,c,fst[a]),fst[a]=cnt;
        e[++cnt]=Edge(b,a,-d,0,fst[b]),fst[b]=cnt;
    }
    void init(){
        for (int i=1;i<=n;i++)
            cur[i]=fst[i];
    }
    void init(int _S,int _T){
        S=_S,T=_T,MaxFlow=MinCost=0,init();
    }
    int SPFA(){
        for (int i=1;i<=n;i++)
            dis[i]=INF;
        memset(vis,0,sizeof vis);
        head=tail=0;
        dis[q[++tail]=T]=0;
        while (head!=tail){
            if ((++head)>=n)
                head-=n;
            int x=q[head];
            vis[x]=0;
            for (int i=fst[x];i;i=e[i].nxt){
                int y=e[i].y;
                if (e[i^1].cap&&dis[x]-e[i].c<dis[y]){
                    dis[y]=dis[x]-e[i].c;
                    if (!vis[y]){
                        if ((++tail)>=n)
                            tail-=n;
                        vis[q[tail]=y]=1;
                    }
                }
            }
        }
        memset(vis,0,sizeof vis);
        return dis[S]<INF;
    }
    int dfs(int x,int Flow){
        if (x==T||!Flow)
            return Flow;
        vis[x]=1;
        int now=Flow;
        for (int &i=cur[x];i;i=e[i].nxt){
            int y=e[i].y;
            if (!vis[y]&&e[i].cap&&dis[x]-e[i].c==dis[y]){
                int d=dfs(y,min(now,e[i].cap));
                e[i].cap-=d,e[i^1].cap+=d;
                if (!(now-=d))
                    break;
            }
        }
        vis[x]=0;
        return Flow-now;
    }
    void Dinic(){
        while (SPFA()){
            init();
            int now=dfs(S,INF);
            MaxFlow+=now,MinCost+=now*dis[S];
        }
    }
    void MCMF(int &_MinCost,int &_MaxFlow){
        Dinic(),_MinCost=MinCost,_MaxFlow=MaxFlow;
    }
    void Auto(int _S,int _T,int &_MinCost,int &_MaxFlow){
        init(_S,_T),MCMF(_MinCost,_MaxFlow);
    }
}g;
int read(){
    int x=0;
    char ch=getchar();
    while (!isdigit(ch))
        ch=getchar();
    while (isdigit(ch))
        x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    return x;
}
int n,m,S,T;
int main(){
    n=read(),m=read(),S=1,T=n;
    g.clear(n);
    while (m--){
        int a=read(),b=read(),c=read(),cap=read();
        g.add(a,b,c,cap);
    }
    int MinCost,MaxFlow;
    g.Auto(S,T,MinCost,MaxFlow);
    printf("%d %d\n",MaxFlow,MinCost);
    return 0;
}