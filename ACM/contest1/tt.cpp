#include<bits/stdc++.h>
#define ll long long
#define mp make_pair
#define pii pair<ll,int>
#define F first
#define S second
const int maxn=3010;
const ll inf=1LL<<60;
using namespace std;
vector<pii>G[maxn]; int vis[maxn],N; ll a[maxn],ans,dis[maxn];
void dijs(ll x)
{
    priority_queue<pii,vector<pii>,greater<pii> >q;
    int vis[maxn];
    for(int i=1;i<=N;i++) dis[i]=inf,vis[i]=0;
    q.push(mp(0,1)); dis[1]=0;
    while(!q.empty()){
        pii t=q.top(); q.pop();
        int u=t.S, L=G[u].size();     
        for(int i=0;i<L;i++){
            int v=G[u][i].S; ll c=G[u][i].F-x;
            if(c<0) c=0;
            if(dis[v]>dis[u]+c){
                dis[v]=dis[u]+c;
                if(!vis[v]) vis[v]=1,q.push(mp(dis[v],v));
            }
        }
        vis[u]=0;
    }
}
int main()
{
    int M,K,u,v,i; ll c;
    scanf("%d%d%d",&N,&M,&K);
    for(i=1;i<=M;i++){
        scanf("%d%d%I64d",&u,&v,&c);
        G[u].push_back(mp(c,v));
        G[v].push_back(mp(c,u));
        a[i]=c;
    }
    dijs(0);  ans=dis[N];
    for(i=1;i<=M;i++) {
        dijs(a[i]);
        ll tmp=dis[N]+(ll)K*a[i];
        ans=min(tmp,ans);
    }
    printf("%I64d\n",ans);
    return 0;
}