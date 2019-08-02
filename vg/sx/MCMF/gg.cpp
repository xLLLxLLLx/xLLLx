#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
const int maxn = 20000;
const int maxm = 800000;
const int inf = 1e8;
#define MIN INT_MIN
#define MAX 1e6
#define LL long long
#define init(a) memset(a,0,sizeof(a))
#define FOR(i,a,b) for(int i = a;i<b;i++)
#define max(a,b) (a>b)?(a):(b)
#define min(a,b) (a>b)?(b):(a)
using namespace std;
struct node
{
    int u,v,w,cap,next;
} edge[maxm];
int pre[maxn],dis[maxn],head[maxn],cnt;
bool vis[maxn];
int n;
void add(int u,int v,int c,int cap)
{
    edge[cnt].u=u;
    edge[cnt].v=v;
    edge[cnt].w=c;
    edge[cnt].cap=cap;
    edge[cnt].next=head[u];
    head[u]=cnt++;
 
    edge[cnt].u=v;
    edge[cnt].v=u;
    edge[cnt].w=-c;
    edge[cnt].cap=0;
    edge[cnt].next=head[v];
    head[v]=cnt++;
}
int spfa(int s,int t)
{
    queue<int>q;
    while(q.empty()==false) q.pop();
    q.push(s);
    memset(vis,0,sizeof(vis));
    memset(pre,-1,sizeof(pre));
    FOR(i,s,t+1)
    dis[i] = inf;
    dis[s]=0;
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        vis[u] = 0;
        for(int i=head[u]; i!=-1; i=edge[i].next)
        {
            if(edge[i].cap && dis[edge[i].v]>dis[u]+edge[i].w)
            {
                dis[edge[i].v]=dis[u]+edge[i].w;
                pre[edge[i].v] = i;
                if(!vis[edge[i].v])
                {
                    vis[edge[i].v]=1;
                    q.push(edge[i].v);
                }
            }
        }
 
    }
    if(dis[t]  != inf)
        return 1;
    else
        return 0;
}
int MinCostMaxFlow(int s,int t)
{
    int flow=0,cost=0;
    while(spfa(s,t))
    {
        int df = inf;
        for(int i = pre[t]; i!=-1; i=pre[edge[i].u])
        {
            if(edge[i].cap<df)
                df = edge[i].cap;
        }
        flow += df;
        for(int i=pre[t]; i!=-1; i=pre[edge[i].u])
        {
            edge[i].cap -= df;
            edge[i^1].cap += df;
        }
        //printf("df = %d\n",df);
        cost += dis[t] * df;
    }
    return cost;
}
void initt()
{
    cnt=0;
    memset(head,-1,sizeof(head));
}
int ma;
int main()
{
    int s,t,k;
    while(~scanf("%d%d",&n,&k))
    {
        initt();
        s = 0;
        t=2*n*n+1;
        add(s,1,0,k);
        int num = n*n;
        FOR(i,1,n+1)
        {
            FOR(j,1,n+1)
            {
                scanf("%d",&ma);
                add((i-1)*n+j,(i-1)*n+j+num,-ma,1);
                add((i-1)*n+j,(i-1)*n+j+num,0,k-1);
                if(i<=n-1)//向下建图
                {
                    add((i-1)*n+j+num,i*n+j,0,k);
                }
                if(j<=n-1)//向右建图
                {
                     add((i-1)*n+j+num,(i-1)*n+j+1,0,k);
                }
            }
        }
        add(t-1,t,0,k);
        int ans =  MinCostMaxFlow(s,t);
        cout<<abs(ans)<<endl;
    }
    return 0;
}