#include <cstdio>
#include <cstring>
#include <stack>
#include <algorithm>
using namespace std;
#define maxn 11000
struct node{
    int u , v ;
    int next ;
} edge[210000] ;
int head[maxn] , cnt , vis[210000] ;
int dnf[maxn] , low[maxn] , time ;
int p[maxn] , ans ;
stack <int> sta;
void add(int u,int v)
{
    edge[cnt].u = u ; edge[cnt].v = v ;
    edge[cnt].next = head[u] ; head[u] = cnt++ ;
    edge[cnt].u = v ; edge[cnt].v = u ;
    edge[cnt].next = head[v] ; head[v] = cnt++ ;
}
void tarjan(int u)
{
    dnf[u] = low[u] = ++time ;
    int v , i , j ;
    for(i = head[u] ; i != -1 ; i = edge[i].next)
    {
        if( vis[i] ) continue ;
        vis[i] = vis[i^1] = 1 ;
        v = edge[i].v ;
        if( !dnf[v] )
        {
            sta.push(i) ;
            tarjan(v) ;
            low[u] = min( low[u],low[v] );
            if( low[v] > dnf[u] )
            {
                p[ans++] = i/2+1 ;
            }
        }
        else if( dnf[v] < dnf[u] )
        {
            sta.push(i) ;
            low[u] = min( low[u],dnf[v] ) ;
        }
    }
 
}
int main()
{
    int t , n , m , i , u , v ;
    scanf("%d", &t);
    while(t--)
    {
        memset(head,-1,sizeof(head));
        memset(vis,0,sizeof(vis));
        memset(dnf,0,sizeof(dnf));
        memset(low,0,sizeof(low));
        cnt = ans = time = 0 ;
        scanf("%d %d", &n, &m);
        while(m--)
        {
            scanf("%d %d", &u, &v);
            add(u,v);
        }
        while( !sta.empty() )
            sta.pop();
        tarjan(1);
        printf("%d\n", ans);
        sort(p,p+ans);
        for(i = 0 ; i < ans ; i++)
        {
            if(i == ans-1)
                printf("%d\n", p[i]);
            else
                printf("%d ", p[i]);
        }
        if(t)
            printf("\n");
    }
    return 0;
}