#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;

const int N=4e6+10,M=1e6+10,inf=10000;
int idx=0,cnt=0,rt=0,top=0;
int q[N],s[N],f[M],ch[M][2],v[M],sz[M],lmx[M],rmx[M],mx[M],sum[M],smx[M],lz[M],fz[M];

#define ls ch[x][0]
#define rs ch[x][1]

void read(int &x){
  char ch=getchar();x=0;int f;
  for(;ch<'0'||ch>'9';ch=getchar()) if(ch=='-') f=1;
  for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
  if(f) x=-x;
}

void up(int x){
  sz[x]=sz[ls]+sz[rs]+1;
  lmx[x]=max(max(lmx[x],lmx[ls]),sum[ls]+v[x]+lmx[rs]);
  rmx[x]=max(max(rmx[x],rmx[rs]),sum[rs]+v[x]+rmx[ls]);
  mx[x]=max(max(max(mx[x],mx[ls]),mx[rs]),rmx[ls]+v[x]+lmx[rs]);
  sum[x]=sum[ls]+sum[rs]+v[x];
  smx[x]=max(smx[x],max(smx[ls],smx[rs]));
}

void del(int x){
  if(!x) return ;
  q[++top]=x;
  del(ls),del(rs);
}

void addnode(int& x,int val,int p){
  if(top) x=q[top--];
  else x=++idx;
  lz[x]=-inf;
  ls=rs=fz[x]=0,f[x]=p,sz[x]=1;
  sum[x]=smx[x]=v[x]=val;
  lmx[x]=rmx[x]=mx[x]=max(val,0);
}

void build(int& x,int l,int r,int p){
  int mid=(l+r)>>1;
  addnode(x,s[mid],p);
  if(l==r) return ;
  build(ls,l,mid-1,x),build(rs,mid+1,r,x);
  up(x,val);
}

void rotate(int x){
  int y=f[x],z=f[y];
  int k=(ch[y][1]==x);
  ch[z][ch[z][1]==y]=x,f[x]=z;
  ch[y][k]=ch[x][k^1];
  f[ch[x][k^1]]=y;
  ch[x][k^1]=y;
  f[y]=x;
}

int find(int x,int k){
  if(k==sz[ls]+1) return x;
  if(sz[ls]>=k) return find(ls,k);
  return find(rs,k-sz[ls]-1);
}

void rev(int x){
  fz[x]^=1;
  swap(ls,rs);
  swap(lmx[x],rmx[x]);
}

void go(int x,int y){
  lz[x]=y;
  sum[x]=sz[x]*lz[x];
  sum[x]=smx[x]=v[x]=lz[x];
  lmx[x]=rmx[x]=mx[x]=max(lz[x],0);
}

void down(int x){
  if(fz[x]){
    fz[x]=0;
    if(ls) rev(ls);
    if(rs) rev(rs);
  }
  if(lz[x]!=-inf){
    if(ls) go(ls,lz[x]);
    if(rs) go(rs,lz[x]);
    lz[x]=-inf;
  }
}

void splay(int x,int goal){
  while(f[x]!=goal){
    int y=f[x],z=f[y];
    if(z!=goal) (ch[z][0]==y)^(ch[y][0]==x) ? rotate(x):rotate(y);
    rotate(x);
  }
}

void init(){
  smx[0]=-inf;
  addnode(rt,-inf,0);
  addnode(ch[rt][1],-inf,rt);
  build(ch[ch[rt][1]][0],1,s[0],ch[rt][1]);
}

void print(int x){
  if(!x) return ;
  print(ls);
  printf("%d ",v[x]);
  print(rs);
}

int main(){
  int n,m;read(n),read(m);
  fr(i,1,n) scanf("%d",&s[++s[0]]);
  init();
  fr(o,1,m){
    cin>>s;
    int posi,tot,c;
    if(s=="INSERT"){
      s[0]=0;
      read(posi),read(tot);
      fr(i,1,tot) read(s[++s[0]]);
      int pos=find(posi);
      splay(pos,0);
    }
    if(s=="DELETE"){
      
    }
    if(s=="MAKE-SAME"){
      
    }
    if(s=="REVERSE"){
      
    }
    if(s=="GET-SUM"){
      
    }
    if(s=="MAX-SUM"){
      
    }
  }
  return 0;
}
