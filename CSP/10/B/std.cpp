#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const ll N=100000;
const ll L=40000;
struct node
{
  ll u,v,w;
};
struct edge
{
  ll to;
  ll cost;
};
vector<node> E;
stack<ll> s;
ll n,m,Time,low[N+5],dfn[N+5],color[N+5];
vector<edge> g[N+5],h[N+5];
bool vis[N+5];
ll numx[N+5],numy[N+5],f[N+5];
bool flag[N+5];
ll sz[N+5];
ll calc(ll x)
{
  ll pos=upper_bound(numx,numx+L+1,x)-numx;
  pos--;
  return x*(pos+1)-numy[pos]; 
}
void dfs(ll u)
{
  Time++;
  dfn[u]=low[u]=Time;
  vis[u]=1;
  s.push(u);
  for(ll i=0;i<g[u].size();i++)
  {
    ll v=g[u][i].to;
    if(!dfn[v])
    {
      dfs(v);
      low[u]=min(low[u],low[v]);
    } 
    else if(vis[v]) low[u]=min(low[u],dfn[v]);
  }
  if(low[u]==dfn[u])
  {
    while(s.top()!=u)
    {
      vis[s.top()]=0;
      color[s.top()]=u;
      s.pop();
    }
    color[s.top()]=u;
    vis[s.top()]=0;
    s.pop();
  }
  return;
} 
void DP(ll u)
{
  flag[u]=1;
  ll res=0;
  for(ll i=0;i<h[u].size();i++)
  {
    ll v=h[u][i].to;
    if(!flag[v]) DP(v);
    res=max(res,f[v]+h[u][i].cost);
  }
  f[u]=res+sz[u];
  return;
}
int main()
{
  for(ll i=0;i<=40000;i++) numx[i]=numx[i-1]+i;
  for(ll i=0;i<=40000;i++) numy[i]=numy[i-1]+numx[i];
  scanf("%lld%lld",&n,&m);
  ll u,v,w;
  for(ll i=1;i<=m;i++)
  {
    scanf("%lld%lld%lld",&u,&v,&w);
    g[u].push_back((edge){v,w});
    E.push_back((node){u,v,w});
  } 
  ll ss;
  scanf("%lld",&ss);
  dfs(ss);
  for(ll i=0;i<m;i++)
  {
    if(dfn[E[i].u]==0||dfn[E[i].v]==0) continue;
    if(color[E[i].u]==color[E[i].v]) sz[color[E[i].u]]+=calc(E[i].w);
    else h[color[E[i].u]].push_back((edge){color[E[i].v],E[i].w});
  }
  DP(color[ss]);
  printf("%lld\n",f[color[ss]]);
  return 0;
} 