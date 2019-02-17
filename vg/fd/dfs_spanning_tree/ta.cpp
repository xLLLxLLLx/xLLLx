#include <cstdio>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <climits>
#include <cmath>
#include <queue>
#include <vector>
#include <stack>
#include <set>
#include <map>
#define INF 0x3f3f3f3f
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define eps 1e-8
using namespace std;
 
const int MAXN = 2100;
vector<int> mm[MAXN];
int dep[MAXN], lim[MAXN];
int d[MAXN][MAXN];
 
void dfs(int u, int p)
{
    for (int i = 0; i < mm[u].size(); i ++)
    {
        int v = mm[u][i];
        if (v == p)
        {
            continue;
        }
        dep[v] = dep[u] + 1;
        dfs(v, u);
    }
}
 
void dp(int u, int p)
{
    for (int i = lim[u]; i <= dep[u]; i ++)
    {
        d[u][i] = 0;
    }
    for (int i = 0; i < mm[u].size(); i ++)
    {
        int v = mm[u][i];
        if (v == p)
        {
            continue;
        }
        dp(v, u);
        int tmp = d[v][dep[v]];
        for (int k = 0; k <= dep[u]; k ++)
        {
            if (d[v][k] != -1)
            {
                tmp = (tmp == -1) ? d[v][k] : min(tmp, d[v][k]);
            }
            if (k >= lim[u])
            {
                d[u][k] += tmp;
            }
        }
    }
    if (p != -1)
    {
        d[u][dep[u]] ++;
    }
}
 
int main()
{
    int n, m;
    while (scanf("%d %d", &n, &m), n || m)
    {
        memset(d, -1, sizeof(d));
        memset(lim, 0, sizeof(lim));
        memset(dep, -1, sizeof(dep));
        for (int i = 0; i < n; i ++)
        {
            mm[i].clear();
        }
        for (int i = 1; i < n; i ++)
        {
            int u, v;
            scanf("%d %d", &u, &v);
            u --;
            v --;
            mm[u].push_back(v);
            mm[v].push_back(u);
        }
        dep[0] = 0;
        dfs(0, -1);
        for (int i = n; i <= m; i ++)
        {
            int u, v;
            scanf("%d %d", &u, &v);
            u --;
            v --;
            if (dep[u] < dep[v])
            {
                swap(u, v);
            }
            lim[u] = max(lim[u], dep[v] + 1);
        }
        dp(0, -1);
        fr(i,0,n-1) fr(j,0,n-1) printf("d[%d][%d]=%d\n",i,j,d[i][j]);
        printf("%d\n", d[0][0]);
    }
    return 0;
}

