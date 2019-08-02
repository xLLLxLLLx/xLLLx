#include <bits/stdc++.h>
using namespace std;
const int N = 502;
const int M = 10002;
const int inf = 1000000000;
int dx[2] = {1, 0};
int dy[2] = {0, 1};
struct Edge
{
    int u, v, cap, cost;
    int next;
}edge[M<<2];
int NE, sumFlow;
int head[N], dist[N], pp[N];
bool vis[N];
void init()
{
    NE = 0;
    memset(head, -1, sizeof(head));
}
void add(int u, int v, int cap, int cost)
{
    edge[NE].u = u; edge[NE].v = v; edge[NE].cap = cap; edge[NE].cost = cost;
    edge[NE].next = head[u]; head[u] = NE++;
    edge[NE].u = v; edge[NE].v = u; edge[NE].cap = 0; edge[NE].cost = -cost;
    edge[NE].next = head[v]; head[v] = NE++;
}
bool SPFA(int s, int t, int n)
{
    int i, u, v;
    queue <int> qu;
    memset(vis,false,sizeof(vis));
    memset(pp,-1,sizeof(pp));
    for(i = 0; i <= n; i++) dist[i] = inf;
    vis[s] = true; dist[s] = 0;
    qu.push(s);
    while(!qu.empty())
    {
        u = qu.front(); qu.pop(); vis[u] = false;
        for(i = head[u]; i != -1; i = edge[i].next)
        {
            v = edge[i].v;
            if(edge[i].cap && dist[v] > dist[u] + edge[i].cost)
            {
                dist[v] = dist[u] + edge[i].cost;
                pp[v] = i;
                if(!vis[v])
                {
                    qu.push(v);
                    vis[v] = true;
                }
            }
        }
    }
    if(dist[t] == inf) return false;
    return true;
}
int MCMF(int s, int t, int n) // minCostMaxFlow
{
    int flow = 0; // 总流量
    int i, minflow, mincost;
    mincost = 0;
    while(SPFA(s, t, n))
    {
        minflow = inf + 1;
        for(i = pp[t]; i != -1; i = pp[edge[i].u])
            if(edge[i].cap < minflow)
                minflow = edge[i].cap;
        flow += minflow;
        for(i = pp[t]; i != -1; i = pp[edge[i].u])
        {
            edge[i].cap -= minflow;
            edge[i^1].cap += minflow;
        }
        mincost += dist[t] * minflow;
    }
    sumFlow = flow; // 题目需要流量，用于判断
    return mincost;
}

int val[N][N];

int js(int x, int y, int n) {
    return (x - 1) * n + y;
}

int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= n; ++j) {
            scanf("%d", &val[i][j]);
        }
    }
    int S = 0, T = 2 * n * n + 1;
    add(S, 1, k, 0);
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= n; ++j) {
            add(js(i, j, n), js(i, j, n) + n * n, 1, -val[i][j]);
            add(js(i, j, n), js(i, j, n) + n * n, inf, 0);
            for(int k = 0; k < 2; ++k) {
                int xx = i + dx[k], yy = j + dy[k];
                if(xx <= 0 || yy <= 0 || xx > n || yy > n) continue;
                add(js(i, j, n) + n * n, js(xx, yy, n), inf, 0);
            }
        }
    }
    add(T - 1, T, k, 0);
    printf("%d\n", -MCMF(S, T, 2 * n * n + 1));
    return 0;
}