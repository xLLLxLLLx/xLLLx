#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=5e4+10;
struct Query{ int id,u,v,T; }q[N];
struct Change{ int x,od,nw; }c[N];
int tp=0,Q[N],col=0;
int n,m,sz,gg,bk,cnt=0,res=0;
int B[N],b[N],L[N],R[N],sum[N],nm[N],a[N],pre[N],vis[N],d[N];/*B:tree  b:w*/
int eu[N<<1],to[N<<1],nt[N<<1],mk[N],st[N<<1][20],head[N],dep[N],f[N];

void add(int x,int y){
    to[++cnt]=y,nt[cnt]=head[x],head[x]=cnt;
    to[++cnt]=x,nt[cnt]=head[y],head[y]=cnt;
}

void dfs(int u,int fa){
    f[u]=fa,dep[u]=dep[fa]+1;
    eu[++res]=u;
    int lt=tp;
    for(int i=head[u];i;i=nt[i]){
        if(to[i]==fa) continue;
        dfs(to[i],u);
        if(tp-lt>=sz){
            ++col;
            while(tp!=lt) B[Q[tp--]]=col;
        }
        eu[++res]=u;
    }
    Q[++tp]=u;
}

void Gao(){
    while(tp) B[Q[tp--]]=col;
    memset(mk,-1,sizeof mk);
    fr(i,1,res){
        if(mk[eu[i]]==-1) mk[eu[i]]=i;
        st[i][0]=eu[i];
    }
    fr(i,1,19) fr(j,1,res){
        if(j+(1<<i)+1>=res) continue;
        int pos=st[j][i-1],tmp=st[j+(1<<(i-1))][i-1];
        if(dep[pos]<dep[tmp]) st[j][i]=pos;
        else st[j][i]=tmp;
    }
}

int GetLCA(int l,int r){
    if(l>r) swap(l,r);
    int kk=log(double(r-l+1))/log(2.0);
    int pos=st[l][kk],tmp=st[r-(1<<kk)+1][kk];
    if(dep[pos]<dep[tmp]) return pos;
    else return tmp;
}

bool cmp(Query xx,Query yy){
    if(B[xx.u]==B[yy.u]){
        if(B[xx.v]==B[yy.v]) return xx.T<yy.T;
        else return xx.v<yy.v;
    } else return xx.u<yy.u;
}

void Gai(int sit,int x,int flg){
    if(x>n) return ;
    if(nm[x]) sum[b[x]]--;
    nm[x]+=flg;
    if(nm[x]) sum[b[x]]++;
}

void Upd(int sit,int x,int y){
    if(vis[sit]){
        Gai(sit,x,-1),Gai(sit,y,1);
    }
    a[sit]=y;
}

int Get(){
    fr(i,1,gg){
        if(sum[i]==R[i]-L[i]+1) continue;
        else fr(j,L[i],R[i]) if(!nm[j]) {
            return j;
        }
    }
}

void init(){
    bk=sqrt(n);sz=pow(n,0.45);
    fr(i,0,n) b[i]=i/bk+1;
    gg=n/bk+1;
    fr(i,1,gg) L[i]=(i-1)*bk,R[i]=min(n,i*bk);
}

void fz(int x){
    if(vis[x]) Gai(x,a[x],-1);
    else Gai(x,a[x],1);
    vis[x]^=1;
}

void Go(int x,int y){
    if(dep[x]>dep[y]) swap(x,y);
    while(dep[y]>dep[x]) fz(y),y=f[y];
    while(x!=y) fz(x),fz(y),x=f[x],y=f[y];
}

int main(){
    scanf("%d%d",&n,&m);
    init();
    fr(i,1,n) scanf("%d",&a[i]),pre[i]=a[i];
    for(int i=1,x,y;i<n;++i){
        scanf("%d%d",&x,&y);
        add(x,y);
    }
    dfs(1,0),Gao();
    int T=0,tot=0;
    fr(i,1,m){
        int x,y,z;scanf("%d%d%d",&x,&y,&z);
        if(x) q[++tot]=(Query){tot,y,z,T};
        else c[++T]=(Change){y,pre[y],z},pre[y]=z;
    }
    T=0;
    int nu=1,nv=1;
    sort(q+1,q+1+tot,cmp);
    fr(i,1,tot){
        while(q[i].T>T) T++,Upd(c[T].x,c[T].od,c[T].nw);
        while(q[i].T<T) Upd(c[T].x,c[T].nw,c[T].od),T--;
        if(q[i].v!=nv) Go(q[i].v,nv),nv=q[i].v;
        if(q[i].u!=nu) Go(q[i].u,nu),nu=q[i].u;
        int lca=GetLCA(mk[q[i].u],mk[q[i].v]);
        fz(lca);
        d[q[i].id]=Get();
        fz(lca);
    }
    fr(i,1,tot) printf("%d\n",d[i]);
    return 0;
}
