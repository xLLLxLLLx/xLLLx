#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1e5+10,M=4e6+10,LOG=21;
struct data{
    int nt,to;
}a[N<<1];
int cnt=0,sz=0,n,m,tot;
int sum[M],lson[M],rson[M],rt[M];
int head[N],f[N][LOG],dep[N],w[N],all[N],ys[N];

void add(int x,int y){
    a[++cnt].to=y,a[cnt].nt=head[x],head[x]=cnt;
    a[++cnt].to=x,a[cnt].nt=head[y],head[y]=cnt;
}

void build(int &nw,int l,int r){
    nw=++sz;
    if(l==r) return ;
    int mid=(l+r)>>1;
    build(lson[nw],l,mid),build(rson[nw],mid+1,r);
}

void Change(int old,int &nw,int L,int l,int r,int k){
    nw=++sz,sum[nw]=sum[old]+k,lson[nw]=lson[old],rson[nw]=rson[old];
   // printf("??%d\n",sum[nw]);
    if(l==r) return ;
    int mid=(l+r)>>1;
    if(L<=mid) Change(lson[nw],lson[nw],L,l,mid,k);
    else Change(rson[nw],rson[nw],L,mid+1,r,k);
}

void dfs(int u,int fa){
    f[u][0]=fa,dep[u]=dep[fa]+1;
   // printf("----%d %d----\n",u,fa);
    Change(rt[fa],rt[u],w[u],1,tot,1);
    fr(i,1,LOG-1) f[u][i]=f[f[u][i-1]][i-1];
    for(int i=head[u];i;i=a[i].nt)
        if(a[i].to!=fa) dfs(a[i].to,u);
}

int GetLCA(int A,int B){
    if(dep[A]>dep[B]) swap(A,B);
    rf(i,LOG-1,0) if(dep[f[B][i]]>=dep[A]) B=f[B][i];
    if(A==B) return A;
    rf(i,LOG-1,0)
        if(f[A][i]!=f[B][i]) A=f[A][i],B=f[B][i];
    return f[A][0];
}

int Ask(int u,int v,int lca,int fca,int l,int r,int k){
    if(l==r) return ys[l];
    int mid=(l+r)>>1;
    int nm=sum[lson[u]]+sum[lson[v]]-sum[lson[lca]]-sum[lson[fca]];
    if(nm>=k) Ask(lson[u],lson[v],lson[lca],lson[fca],l,mid,k);
    else Ask(rson[u],rson[v],rson[lca],rson[fca],mid+1,r,k-nm);
}

int main(){
    scanf("%d%d",&n,&m);    
    fr(i,1,n) scanf("%d",&w[i]),all[i]=w[i];
    sort(all+1,all+1+n);
    tot=unique(all+1,all+1+n)-all-1;
    fr(i,1,n){
        int x=w[i];
        w[i]=lower_bound(all+1,all+1+tot,w[i])-all;
        ys[w[i]]=x;
    }
    for(int i=1,x,y;i<n;++i) scanf("%d%d",&x,&y),add(x,y);
    build(rt[0],1,tot);
    dfs(1,0);
    fr(i,1,m){
        int u,v,k;scanf("%d%d%d",&u,&v,&k);
        int LCA=GetLCA(u,v);
     //   printf("u=%d v=%d lca=%d fca=%d\n",u,v,LCA,f[LCA][0]);
        printf("%d\n",Ask(rt[u],rt[v],rt[LCA],rt[f[LCA][0]],1,tot,k));
    }
    return 0;
}
