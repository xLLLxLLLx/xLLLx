#include<bits/stdc++.h>
#define pii pair<int,int>
#define pb push_back
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
const int maxn=400010;
vector<pii>G[maxn],Q[maxn];
vector<int>F[maxn];
int ch[maxn][26],fail[maxn],ans[maxn],tot;
int in[maxn],out[maxn],times; //dfn
char s[maxn]; int sum[maxn];
void add(int x,int val){ while(x<=times) sum[x]+=val,x+=(-x)&x;}
int query(int x){ int res=0; while(x){ res+=sum[x]; x-=(-x)&x; } return res;}
int add()
{
    int now=0,L=strlen(s);
    rep(i,0,L-1) {
        if(!ch[now][s[i]-'a']) ch[now][s[i]-'a']=++tot;
        now=ch[now][s[i]-'a'];
    }  
    // printf("%d\n", now);
    return now;
}
void build()
{
    queue<int>q;
    rep(i,0,25) if(ch[0][i]) q.push(ch[0][i]);
    while(!q.empty()){
        int u=q.front(); q.pop();
        rep(i,0,25) {
            if(ch[u][i]){
                fail[ch[u][i]]=ch[fail[u]][i];
                q.push(ch[u][i]);
            }
            else ch[u][i]=ch[fail[u]][i];
        }
    }
    rep(i,1,tot) F[fail[i]].push_back(i);
}
void dfs(int u)
{
    in[u]=++times;
    for(int i=0;i<F[u].size();i++) dfs(F[u][i]);
    out[u]=times;
}
void dfs(int u,int now) //u是位置，now是id
{
    add(in[u],1);
    for(int i=0;i<Q[now].size();i++){
        pii t=Q[now][i];
        ans[t.second]=query(out[t.first])-query(in[t.first]-1);
    }
    for(int i=0;i<G[now].size();i++){
        pii t=G[now][i];
        dfs(ch[u][t.first],t.second);
    }
    add(in[u],-1);
}
int main()
{
    int N,M,opt,p;
    scanf("%d",&N);
    rep(i,1,N) {
        scanf("%d",&opt);
        if(opt==1) p=0;
        else scanf("%d",&p);
        scanf("%s",s);
        G[p].pb(pii(s[0]-'a',i));
    }
    scanf("%d",&M);
    rep(i,1,M) {
        scanf("%d%s",&p,s);
        Q[p].pb(pii(add(),i));
    }
    build();
    dfs(0);
    dfs(0,0);
    rep(i,1,M) printf("%d\n",ans[i]);
    return 0;
}