#include<bits/stdc++.h>
#define ll long long 
#define pb push_back
#define mk make_pair
#define fi first
#define se second 
using namespace std;
const int N=200010;
typedef pair<int,ll>pii;
int n,st[N],tot,fg[N];
ll d1[N],d2[N],d3[N],ans,W;
char gc(){
  static char*p1,*p2,s[1000000];
  if(p1==p2)p2=(p1=s)+fread(s,1,1000000,stdin);
  return(p1==p2)?EOF:*p1++;
}
ll rd(){
  ll x=0;char c=gc();
  while(c<'0'||c>'9')c=gc();
  while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+c-'0',c=gc();
  return x;
}
bool upd(ll&x,ll y){
  if(x>=y)return false;
  x=y;return true;
}
namespace T3{
  int o=1,hd[N],idx2,f[N][19],lg[N];
  int dep[N],bin[19],pos[N];
  struct Edge{int v,nt;ll w;}E[N<<1];
  void adde(int u,int v,ll w){
      E[o]=(Edge){v,hd[u],w};hd[u]=o++;
      E[o]=(Edge){u,hd[v],w};hd[v]=o++;
  }
  void dfs(int u,int fa){
      f[++idx2][0]=u;pos[u]=idx2;
      for(int i=hd[u];i;i=E[i].nt){
          int v=E[i].v;ll w=E[i].w;
          if(v==fa)continue;
          dep[v]=dep[u]+1;
          d3[v]=d3[u]+w;
          dfs(v,u);
          f[++idx2][0]=u;
      }
  }
  int Min(int x,int y){return dep[x]<dep[y]?x:y;}
  void init(){
      lg[0]=-1;for(int i=1;i<=idx2;++i)lg[i]=lg[i>>1]+1;
      for(int i=bin[0]=1;i<19;++i)bin[i]=bin[i-1]<<1;
      for(int i=1;i<19;++i)
      for(int j=1;j+bin[i]-1<=idx2;++j){
          f[j][i]=Min(f[j][i-1],f[j+bin[i-1]][i-1]);
      }
  }
  int lca(int u,int v){
      int x=pos[u],y=pos[v];
      if(x>y)swap(x,y);
      int t=lg[y-x+1];
      return Min(f[x][t],f[y-bin[t]+1][t]);
  }
  ll que(int u,int v){return d1[u]+d1[v]+d2[u]+d2[v]+d3[u]+d3[v]-d3[lca(u,v)]*2;}
  void solve(){dfs(1,0);init();}
}
namespace T2{
  int id[N],idx,idx2,sta[N],top,dep[N];
  int o=1,hd[N],f[N][19],bin[19],lg[N],pos[N];
  struct Edge{int v,nt;ll w;}E[N<<1];
  void adde(int u,int v,ll w){
      E[o]=(Edge){v,hd[u],w};hd[u]=o++;
      E[o]=(Edge){u,hd[v],w};hd[v]=o++;
  }
  void Adde(int u,int v){
      E[o]=(Edge){v,hd[u],0};hd[u]=o++;
      E[o]=(Edge){u,hd[v],0};hd[v]=o++;
  }
  int Min(int x,int y){return dep[x]<dep[y]?x:y;}
  void dfs1(int u,int fa){
      id[u]=++idx;
      f[++idx2][0]=u;pos[u]=idx2;
      for(int i=hd[u];i;i=E[i].nt){
          int v=E[i].v;ll w=E[i].w;
          if(v==fa)continue;
          dep[v]=dep[u]+1;
          d2[v]=d2[u]+w;
          dfs1(v,u);
          f[++idx2][0]=u;
      }
  }
  void init(){
      lg[0]=-1;for(int i=1;i<=idx2;++i)lg[i]=lg[i>>1]+1;
      for(int i=bin[0]=1;i<19;++i)bin[i]=bin[i-1]<<1;
      for(int i=1;i<19;++i)
      for(int j=1;j+bin[i]-1<=idx2;++j){
          f[j][i]=Min(f[j][i-1],f[j+bin[i-1]][i-1]);
      }
  }
  int lca(int u,int v){
      int x=pos[u],y=pos[v];
      if(x>y)swap(x,y);
      int t=lg[y-x+1];
      return Min(f[x][t],f[y-bin[t]+1][t]);
  }
  void solve(){
      dfs1(1,0);init();
      sta[++top]=1;
  }
  ll cal(int u,int v){
      return (!u&&!v) ? -2 : (!u||!v) ? -1 : T3::que(u,v);
  }
  struct data{
      int x,y;ll v;
      data(int _x=0,int _y=0,ll _v=0):x(_x),y(_y),v(_v){};
      void init(){x=y=0;v=-2;}
      data operator +(const data&A)const{
          data re=v>A.v?*this:A;
          if(upd(re.v,cal(x,A.x)))re=data(x,A.x,re.v);
          if(upd(re.v,cal(x,A.y)))re=data(x,A.y,re.v);
          if(upd(re.v,cal(y,A.x)))re=data(y,A.x,re.v);
          if(upd(re.v,cal(y,A.y)))re=data(y,A.y,re.v);
          return re;
      }
      ll operator *(const data&A)const{
          ll re=0;
          upd(re,cal(x,A.x));
          upd(re,cal(x,A.y));
          upd(re,cal(y,A.x));
          upd(re,cal(y,A.y));
          return re;
      }
  }L[N],R[N];
  void dfs2(int u,int fa){
      L[u].init();R[u].init();
      if(fg[u]&1)L[u].x=u,L[u].v++;
      else if(fg[u])R[u].x=u,R[u].v++;
      for(int i=hd[u];i;i=E[i].nt){
          int v=E[i].v;
          if(v==fa)continue;
          dfs2(v,u);
          upd(ans,max(L[u]*R[v],R[u]*L[v])-2*d2[u]+W);
          L[u]=L[u]+L[v];R[u]=R[u]+R[v];
      }
  }
  bool cmp(int a,int b){return id[a]<id[b];}
  void query(){
      o=1;sort(st+1,st+tot+1,cmp);
      hd[1]=0;for(int i=1;i<=tot;++i)hd[st[i]]=0;
      for(int i=1;i<=tot;++i){
          if(st[i]==sta[top])continue;
          int u=st[i],w=lca(u,sta[top]);
          if(w==sta[top]){sta[++top]=u;continue;}
          while(top>1&&dep[sta[top-1]]>=dep[w])Adde(sta[top-1],sta[top]),top--;
          if(w!=sta[top])hd[w]=0,Adde(w,sta[top--]),sta[++top]=w;
          sta[++top]=u;
      }
      while(top>1)Adde(sta[top-1],sta[top]),top--;
      dfs2(1,0);
  }
}
namespace T1{
  int o,hd[N],cnt,size,vis[N<<1],rt,mn,sz[N];
  vector<pii>g[N];
  struct Edge{int v,nt;ll w;}E[N<<1];
  void adde(int u,int v,ll w){
      g[u].pb(mk(v,w));
      g[v].pb(mk(u,w));
  }
  void Adde(int u,int v,ll w){
      E[o]=(Edge){v,hd[u],w};hd[u]=o++;
      E[o]=(Edge){u,hd[v],w};hd[v]=o++;
  //  cerr<<u<<" "<<v<<" "<<w<<endl;
  }
  void dfs(int u,int fa){
      for(int i=0,lst=0;i<(int)g[u].size();++i){
          int v=g[u][i].fi;ll w=g[u][i].se;
          if(v==fa)continue;dfs(v,u);
          if(!lst){Adde(u,v,w);lst=u;continue;}
          Adde(lst,++cnt,0);Adde(cnt,v,w);lst=cnt;
      }
  }
  void getrt(int u,int fa){
      sz[u]=1;
      for(int i=hd[u];~i;i=E[i].nt){
          int v=E[i].v;
          if(v==fa||vis[i])continue;
          getrt(v,u);sz[u]+=sz[v];
          int tmp=max(sz[v],size-sz[v]);
          if(!~rt||tmp<mn)mn=tmp,rt=i;
      }
  }
  void cal(int u,int fa,int F){
      if(u<=n)fg[st[++tot]=u]=F;
      for(int i=hd[u];~i;i=E[i].nt){
          int v=E[i].v;ll w=E[i].w;
          if(v==fa||vis[i])continue;
          d1[v]=d1[u]+w;
          cal(v,u,F);
      }
  }
  void divide(int i){
      if(size==1)return;
      vis[i]=vis[i^1]=1;
      int p=E[i].v,q=E[i^1].v;
      tot=0;
      d1[p]=0;cal(p,0,1);
      d1[q]=0;cal(q,0,2);
      W=E[i].w;
      T2::query();
      for(int j=1;j<=tot;++j)fg[st[j]]=0;
      int t1=sz[p]<sz[q]?sz[p]:size-sz[q];
      int t2=size-t1;
      rt=-1;size=t1;
      getrt(p,0);
      divide(rt);
      rt=-1;size=t2;
      getrt(q,0);
      divide(rt);
  }
  void solve(){
      for(int i=1;i<=n<<1;++i)hd[i]=-1;
      cnt=n;dfs(1,0);
      rt=-1;size=cnt;
      getrt(1,0);
      divide(rt);
  }
}
int main(){
  n=rd();int u,v;ll w;
  for(int i=1;i<n;++i){
      u=rd(),v=rd(),w=rd();
      T1::adde(u,v,w);
  }
  for(int i=1;i<n;++i){
      u=rd(),v=rd(),w=rd();
      T2::adde(u,v,w);
  }
  for(int i=1;i<n;++i){
      u=rd(),v=rd(),w=rd();
      T3::adde(u,v,w);
  }
  T3::solve();
  T2::solve();
  T1::solve();
  cout<<ans<<endl;
  return 0;
}